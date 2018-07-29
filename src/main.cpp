// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <iostream>
#include <jitdb/jitdb_socket.h>
#include <readline/readline.h>
#include "compiler/Compiler.h"
#include "database/Database.h"
#include "server/Server.h"

using namespace hsql;
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

    Environment environment;
    Database test;
    Table todos;
    todos.GetSchema().SetField("num", Type("Int32", 4));
    test.SetTable("todos", todos);
    environment.AddDatabase("test", test);

    Compiler compiler(environment);

    options.repl = true; // TODO: Actually support network protocol

    if (options.repl) {
        const char *buf;

        while ((buf = readline("jitdb> ")) != nullptr) {
            std::string line(buf);
            if (line.empty()) continue;
            add_history(buf);

            SQLParserResult result;
            SQLParser::parse(line, &result);

            if (!result.isValid()) {
                cout << "sql error at line " << result.errorLine() << ", column " << result.errorColumn() << ": "
                     << result.errorMsg() << endl;
            } else {
                for (int i = 0; i < result.getStatements().size(); i++) {
                    auto *statement = result.getStatement(i);
                    const char *errorMessage;

                    if (!compiler.Execute(statement, &errorMessage)) {
                        cout << "error: " << errorMessage << endl;
                    } else {
                        // TODO: Print the rows.
                    }
                }
            }
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