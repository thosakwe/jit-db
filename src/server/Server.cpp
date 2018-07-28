// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <jitdb/jitdb.h>

jitdb::Server::Server(const Options &options) : options(options) {

}

jitdb::Server::~Server() {
    close(sockfd);
}

int jitdb::Server::Accept(sockaddr *addr, socklen_t *socklen) {
    std::lock_guard(socketMutex);
    return accept(sockfd, addr, socklen);
}

bool jitdb::Server::BindSocket(const char **errorMessage) {
    return false;
}
