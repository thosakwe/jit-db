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
    auto signature = jit_type_create_signature(jit_abi_cdecl, ulongPointerType, &ulongPointerType, 1, 0);
    auto function = jit_function_create(jitContext, signature);

    // Create a continuation struct.
    SelectContinuation continuation{};
    continuation.statement = statement;
    continuation.errorMessage = errorMessage;
    continuation.entryPoint = function;
    continuation.currentLength = jit_value_create_nint_constant(function, jit_type_ulong, 0);
    continuation.currentReturnValue = jit_value_create_nint_constant(function, jit_type_ulong, 0);
    continuation.dataPointer = jit_value_get_param(function, 0);

    // Next, compile the predicate into a single function.
    // This will be called for each item in the data.
    auto predicate = CompileSelectPredicate(continuation);

    if (continuation.errored) {
        jit_function_abandon(function);
        jit_context_build_end(jitContext);
        return false;
    }

    // TODO: Actual loop
    auto predicateSignature = jit_function_get_signature(predicate);
    continuation.currentReturnValue = jit_insn_call(function, "where", predicate, predicateSignature,
                                                    &continuation.dataPointer, 1, 0);

    // Return the value.
    jit_insn_return(function, continuation.currentReturnValue);

    // Dump it...
    jit_dump_function(stdout, predicate, "where");
    jit_dump_function(stdout, function, "query");

    // Compile the function.
    jit_function_compile(function);

    // Release the builder.
    jit_context_build_end(jitContext);
    return true;
}

jit_function_t jitdb::Compiler::CompileSelectPredicate(SelectContinuation &continuation) {
    // This function takes:
    // * A pointer to an unsigned long
    //
    // And returns
    // * A char, either 0 or 1
    auto ulongPointerType = jit_type_create_pointer(jit_type_ulong, 0);
    auto signature = jit_type_create_signature(jit_abi_cdecl, jit_type_sys_char, &ulongPointerType, 1, 0);
    auto function = jit_function_create(jitContext, signature);

    // If there is no predicate, return true for every item.
    // TODO: Optimize this by not compiling it at all.
    if (continuation.statement->whereClause == nullptr) {
        auto jitTrue = jit_value_create_nint_constant(function, jit_type_sys_char, 1);
        jit_insn_return(function, jitTrue);
    } else {
        // Otherwise, we need to compile the expression into a jit_value.
        auto param = jit_value_get_param(function, 0);
        auto condition = CompilePredicateExpression(continuation.statement->whereClause, continuation, function, param);
        jit_insn_return(function, condition);
    }

    return function;
}

jit_value_t
jitdb::Compiler::CompilePredicateExpression(hsql::Expr *expr, SelectContinuation &continuation,
                                            jit_function_t function,
                                            jit_value_t value) {
    if (expr->isType(hsql::ExprType::kExprLiteralInt)) {
        if (expr->ival == 1) {
            return jit_value_create_nint_constant(function, jit_type_sys_char, 1);
        } else {
            return jit_value_create_nint_constant(function, jit_type_sys_char, 0);
        }
    } else {
        // TODO: Handle other types.
        continuation.errored = true;
        *continuation.errorMessage = "Unsupported predicate type.";
    }

    return jit_value_create_nint_constant(function, jit_type_sys_char, 0);
}
