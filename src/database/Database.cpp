// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Database.h"

jitdb::Database::Database() = default;

jitdb::Database::Database(const jitdb::Database &other) {
    tables.insert(other.tables.begin(), other.tables.end());
}

jitdb::Database::Database(const jitdb::Database &&other) {
    tables.insert(other.tables.begin(), other.tables.end());
}

jitdb::Database::~Database() {
    tables.clear();
}

bool jitdb::Database::HasTable(const std::string &name) const {
    return tables.find(name) != tables.end();
}

const jitdb::Table &jitdb::Database::GetTable(const std::string &name) const {
    return tables.at(name);
}

void jitdb::Database::SetTable(const std::string &name, const jitdb::Table &table) {
    tables.insert(std::make_pair(name, table));
}
