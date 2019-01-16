// Copyright (c) 2019, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_SERVER_H
#define JIT_DB_SERVER_H

#include <asio.hpp>
#include "../database/environment.h"
#include "options.h"

namespace pubby
{
    class server
    {
    public:
        server(const options &options, environment &env);

    private:
        asio::ip::tcp::acceptor acceptor;
        asio::io_context io_context;
        asio::signal_set signals;
        environment &env;
        const options &options;
    };
}

#endif //JIT_DB_SERVER_H
