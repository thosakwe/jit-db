// Copyright (c) 2019, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "server.h"

pubby::server::server(const pubby::options &options, pubby::environment &env)
        : env(env),
          options(options),
          io_context(1),
          acceptor(io_context),
          signals(io_context) {
    // TODO: Handle signals exit
    // https://github.com/chriskohlhoff/asio/blob/master/asio/src/examples/cpp11/http/server/server.cpp
    signals.add(SIGINT);
    signals.add(SIGTERM);
#ifdef SIGQUIT
    signals.add(SIGQUIT);
#endif
}
