// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <exception>
#include <sstream>
#include "options.h"

void pubby::parse_options(pubby::options &options, int argc, const char **argv) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (i < argc - 1) {
            if (arg == "--port" || arg == "-p") {
                std::string next(argv[++i]);
                std::istringstream iss(next);

                if (!(iss >> options.port)) {
                    throw "Invalid (or missing) port number.";
                }
            } else if (arg == "--host" || arg == "-H") {
                std::string next(argv[++i]);
                options.host = next;
                continue;
            }
        } else if (arg == "--help" || arg == "-h") {
            options.help = true;
        } else if (arg == "--repl" || arg == "-x") {
            options.repl = true;
        } else {
            std::ostringstream oss;
            oss << "Unknown argument '" << arg << "'.";
            throw oss.str();
        }
    }
}

void pubby::print_help(std::ostream &stream) {
    stream << "usage: pubby [options...]" << std::endl;
    stream << std::endl;
    stream << "options:" << std::endl;
    stream << "--help, -h    Print this help information." << std::endl;
    stream << "--host, -H    Address to listen at [127.0.0.1]" << std::endl;
    stream << "--port, -p    Port to listen at [27018]" << std::endl;
    stream << "--repl, -x    Start a REPL" << std::endl;
}
