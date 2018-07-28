// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_SERVER_H
#define JIT_DB_SERVER_H

#ifndef WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#else
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")
#endif

#include <mutex>
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
