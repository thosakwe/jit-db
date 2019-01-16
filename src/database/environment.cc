// Copyright (c) 2019, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "environment.h"

std::unique_ptr<pubby::database> create_meta_db() {
    auto meta_db = std::make_unique<pubby::database>();
    meta_db->name = "pubby";
    return meta_db;
}

pubby::environment pubby::load_environment(const pubby::options &options) {
    // TODO: Actually load databases, etc.
    environment env;
    env.databases.push_back(create_meta_db());
    return env;
}
