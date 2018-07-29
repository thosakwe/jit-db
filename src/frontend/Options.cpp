// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <sstream>
#include "Options.h"

bool jitdb::ParseOptions(jitdb::Options &options, int argc, const char **argv, const char **errorMessage) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (i < argc - 1) {
            if (arg == "--port" || arg == "-p") {
                std::string next(argv[++i]);
                std::istringstream iss(next);

                if (iss >> options.port) {
                    *errorMessage = "Invalid port number.";
                    continue;
                } else {
                    return false;
                }
            } else if (arg == "--host" || arg == "-H") {
                std::string next(argv[++i]);
                options.host = next;
                continue;
            }
        } else if (arg == "--help" || arg == "-h") {
            options.printHelp = true;
            return true;
        } else if (arg == "--repl" || arg == "-x") {
            options.repl = true;
            return true;
        }

        std::ostringstream oss;
        oss << "Unknown argument '" << arg << "'.";
        *errorMessage = oss.str().c_str();
        return false;
    }

    return true;
}

void jitdb::PrintHelp(std::ostream &stream) {
    stream << "usage: jitdb [options...]" << std::endl;
    stream << std::endl;
    stream << "Options:" << std::endl;
    stream << "--help, -h    Print this help information." << std::endl;
    stream << "--host, -H    Address to listen at [127.0.0.1]" << std::endl;
    stream << "--port, -p    Port to listen at [27018]" << std::endl;
    stream << "--repl, -x    Start a REPL" << std::endl;
}
