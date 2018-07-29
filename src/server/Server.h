// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_SERVER_H
#define JIT_DB_SERVER_H

#include <jitdb/jitdb_socket.h>
#include <mutex>
#include "../frontend/Options.h"

namespace jitdb
{
    class Server
    {
    public:
        Server(const Options &options);

        ~Server();

        // Disable copy, move constructors
        Server(const Server &server) = delete;

        Server(const Server &&server) = delete;

        /**
         * Accepts an incoming socket connection.
         *
         * Uses a mutex behind-the-scenes, so it's thread safe.
         * @return
         */
        int Accept(sockaddr *addr, socklen_t *socklen);

        /**
         * Binds a socket to the network interface.
         * @return true if successful.
         */
        bool BindSocket(const char **errorMessage);

    private:
        const Options &options;
        int sockfd;
        std::mutex socketMutex;
    };
}

#endif //JIT_DB_SERVER_H
