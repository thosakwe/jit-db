// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <jitdb/jitdb.h>
#include <iostream>

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

    cout << "yay" << endl;

    return 0;
}