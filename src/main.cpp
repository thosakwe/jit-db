// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <iostream>
#include <jitdb/jitdb_socket.h>
#include <readline/readline.h>
#include "database/Database.h"
#include "server/Server.h"

using namespace jitdb;
using namespace std;

int main(int argc, const char **argv) {
    // Parse the command-line options.
    const char *errorMessage = nullptr;
    Options options;

    if (!ParseOptions(options, argc, argv, &errorMessage)) {
        cerr << "fatal error: " << errorMessage << endl;
        PrintHelp(cerr);
        return 1;
    } else if (options.printHelp) {
        PrintHelp(cout);
        return 0;
    }

    if (options.repl) {
        const char *buf;

        while ((buf = readline("jitdb> ")) != nullptr) {
            std::string line(buf);
            if (line.empty())continue;
            add_history(buf);
            cout << "REPL: " << line << endl;
        }
    } else {

        Server server(options);

        if (!server.BindSocket(&errorMessage)) {
            cerr << "fatal error: " << errorMessage << endl;
            return 1;
        }

        cout << "jitdb listening at jitdb://" << options.host << ":" << options.port << endl;

        while (true) {
            sockaddr addr;
            socklen_t len;
            int sock = server.Accept(&addr, &len);
            if (sock < 0) continue;
            cout << "Hey: " << sock << endl;
            close(sock);
        }
    }

    return 0;
}