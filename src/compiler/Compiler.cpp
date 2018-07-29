// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <jit/jit-dump.h>
#include <util/sqlhelper.h>
#include "Compiler.h"

jitdb::Compiler::Compiler(const jitdb::Environment &environment) : environment(environment) {
    jitContext = jit_context_create();
}

jitdb::Compiler::~Compiler() {
    jit_context_destroy(jitContext);
}

bool jitdb::Compiler::Execute(const hsql::SQLStatement *statement, const char **errorMessage) {
    if (statement->is(hsql::StatementType::kStmtSelect)) {
        return ExecuteSelect((const hsql::SelectStatement *) statement, errorMessage);
    }

    *errorMessage = "unsupported statement type. Only SELECT is supported.";
    return false;
}

bool jitdb::Compiler::ExecuteSelect(const hsql::SelectStatement *statement, const char **errorMessage) {
    // Ensure that the user has specified a table.
    if (statement->fromTable == nullptr) {
        *errorMessage = "no table was specified for `select` statement.";
        return false;
    }

    // TODO: Return an empty set immediately if the collection is empty.

    // Lock the builder.
    jit_context_build_start(jitContext);

    // This function will take in:
    // * A pointer to an unsigned long, the total number of rows.
    //
    // And return:
    // * A pointer to allocated data that holds the row indices (all unsigned longs) that match the predicate.
    auto ulongPointerType = jit_type_create_pointer(jit_type_ulong, 0);
    auto returnType = jit_type_create_signature(jit_abi_cdecl, ulongPointerType, &ulongPointerType, 1, 0);
    auto function = jit_function_create(jitContext, returnType);

    // Create a continuation struct.
    SelectContinuation continuation{};
    continuation.function = function;
    continuation.currentLength = jit_value_create_nint_constant(function, jit_type_ulong, 0);
    continuation.currentReturnValue = jit_value_create_nint_constant(function, jit_type_ulong, 0);
    continuation.dataPointer = jit_value_get_param(function, 0);

    // Next, compile the predicate into a single function.
    // This will be called for each item in the data.

    // Dump it...
    jit_dump_function(stdout, function, "query");

    // Compile the function.
    jit_function_compile(function);

    // Release the builder.
    jit_context_build_end(jitContext);
    return true;
}
