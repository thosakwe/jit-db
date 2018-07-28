// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_SERVER_H
#define JIT_DB_SERVER_H

#include "Options.h"

namespace jitdb
{
    class Server
    {
    public:
        explicit Server(const Options &options);

        ~Server();

        // Disable copy, move constructors
        Server(const Server &server) = delete;

        Server(const Server &&server) = delete;

    private:
        const Options &options;
    };
}

#endif //JIT_DB_SERVER_H
