// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_JITDB_SOCKET_H
#define JIT_DB_JITDB_SOCKET_H

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

#endif //JIT_DB_JITDB_SOCKET_H
