// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Compiler.h"

jitdb::Compiler::Compiler(const jitdb::Environment &environment) : environment(environment) {
    jitContext = jit_context_create();
}

jitdb::Compiler::~Compiler() {
    jit_context_destroy(jitContext);
}
