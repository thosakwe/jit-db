// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <jitdb/jitdb.h>

void jitdb::Environment::AddDatabase(const std::string &name, const jitdb::Database &database) {
    databases.insert(std::make_pair(name, database));
}