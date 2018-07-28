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

        if (i < argc - 2) {
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
        }

        std::ostringstream oss;
        oss << "Unknown argument '" << arg << "'.";
        *errorMessage = oss.str().c_str();
        return false;
    }

    return true;
}
