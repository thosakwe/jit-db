// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_COMPILER_H
#define JIT_DB_COMPILER_H

#include <jit/jit.h>
#include "../database/Environment.h"

namespace jitdb
{
    class Compiler
    {
        Compiler(const Environment &environment);

        Compiler(const Compiler &other) = delete;

        Compiler(const Compiler &&other) = delete;

        ~Compiler();

    private:
        const Environment &environment;
        jit_context_t jitContext = nullptr;
    };
}

#endif //JIT_DB_COMPILER_H
