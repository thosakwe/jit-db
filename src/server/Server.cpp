// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Server.h"

jitdb::Server::Server(const Options &options) : options(options) {

}

jitdb::Server::~Server() {
    close(sockfd);
}

int jitdb::Server::Accept(sockaddr *addr, socklen_t *socklen) {
    std::lock_guard<std::mutex> lock(socketMutex);
    return accept(sockfd, addr, socklen);
}

bool jitdb::Server::BindSocket(const char **errorMessage) {
    // Parse the IP; check if it's IPv6.
    bool isIpv6 = true;
    struct sockaddr_in ipv4Address;
    struct sockaddr_in6 ipv6Address;
    int result = inet_pton(AF_INET6, options.host.c_str(), &(ipv6Address.sin6_addr));
    ipv4Address.sin_family = AF_INET;
    ipv6Address.sin6_family = AF_INET6;
    ipv4Address.sin_port = ipv6Address.sin6_port = htons(options.port);

    if (result < 0) {
        // An actual error occurred.
        *errorMessage = strerror(errno);
        return false;
    } else if (result != 0) {
        // This isn't an IPv6 address, try parsing it as IPv4.
        isIpv6 = false;
        result = inet_pton(AF_INET, options.host.c_str(), &(ipv4Address.sin_addr));

        if (result < 0) {
            *errorMessage = strerror(errno);
            return false;
        } else if (result == 0) {
            *errorMessage = "Invalid IP address.";
            return false;
        }
    }

    // Next, open the socket.
    int sockfd = socket(isIpv6 ? AF_INET6 : AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sockfd < 0) {
        *errorMessage = strerror(errno);
        return false;
    }

    // Enable address reuse.
    int i;
    result = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

    if (result < 0) {
        *errorMessage = strerror(errno);
        return false;
    }

    // Now, bind the socket.
    if (isIpv6) {
        result = bind(sockfd, (const sockaddr *) &ipv6Address, sizeof(ipv6Address));
    } else {
        result = bind(sockfd, (const sockaddr *) &ipv4Address, sizeof(ipv4Address));
    }

    if (result < 0) {
        *errorMessage = strerror(errno);
        return false;
    }

    // Start listening.
    if (listen(sockfd, SOMAXCONN) < 0) {
        *errorMessage = strerror(errno);
        return false;
    }

    // All done!
    return true;
}
