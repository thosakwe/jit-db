// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_COMPILER_H
#define JIT_DB_COMPILER_H

#include <unordered_map>
#include <jit/jit.h>
#include <SQLParser.h>
#include "../database/Environment.h"

namespace jitdb
{
    class Compiler
    {
    public:
        Compiler(const Environment &environment);

        Compiler(const Compiler &other) = delete;

        Compiler(const Compiler &&other) = delete;

        ~Compiler();

        bool Execute(const hsql::SQLStatement *statement, const char **errorMessage);


    private:
        const Environment &environment;
        jit_context_t jitContext = nullptr;
        std::unordered_map<std::string, jit_function_t> queryCache; // TODO: Cache queries...?

        struct SelectContinuation
        {
            jit_function_t function;
            jit_value_t dataPointer;
            jit_value_t currentReturnValue;
            jit_value_t currentLength;
        };

        bool ExecuteSelect(const hsql::SelectStatement *statement, const char **errorMessage);
    };
}

#endif //JIT_DB_COMPILER_H
