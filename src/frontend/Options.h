// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_OPTIONS_H
#define JIT_DB_OPTIONS_H

#include <string>

namespace jitdb
{

    struct Options
    {
        std::string host;
        int port;
    };

    bool ParseOptions(jitdb::Options &options, int argc, const char **argv, const char **errorMessage);
}

#endif //JIT_DB_OPTIONS_H
