// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <iostream>
#include <readline/readline.h>
#include "database/environment.h"
#include "frontend/options.h"

int main(int argc, const char **argv) {
    try {
        pubby::options options;
        pubby::parse_options(options, argc, argv);

        if (options.help) {
            pubby::print_help(std::cout);
            return 0;
        }

        auto env = pubby::load_environment(options);
        std::cout << env.databases.at(0)->name << std::endl;
    } catch (const std::string &msg) {
        std::cerr << "fatal error: " << msg << std::endl;
    }
}