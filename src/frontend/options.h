// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_OPTIONS_H
#define JIT_DB_OPTIONS_H

#include <ostream>
#include <string>

namespace pubby
{
    struct options
    {
        std::string host = std::string("127.0.0.1");
        int port = 27018;
        bool help = false;
        bool repl = false;
    };

    void parse_options(pubby::options &options, int argc, const char **argv);

    void print_help(std::ostream &stream);
}

#endif //JIT_DB_OPTIONS_H
