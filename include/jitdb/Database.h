// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_DATABASE_H
#define JIT_DB_DATABASE_H

#include <string>
#include <unordered_map>
#include "Table.h"

namespace jitdb
{
    class Database
    {
    public:
        Database() = default;

        Database(const Database &other) {
            tables.insert(other.tables.begin(), other.tables.end());
        }

        Database(const Database &&other) {
            tables.insert(other.tables.begin(), other.tables.end());
        }

        ~Database() {
            tables.clear();
        }

        bool HasTable(const std::string &name) const {
            return tables.find(name) != tables.end();
        }

        const Table &GetTable(const std::string &name) const {
            return tables.at(name);
        }

        void SetTable(const std::string &name, const Table &table) {
            tables.insert(std::make_pair(name, table));
        }

    private:
        std::unordered_map<std::string, Table> tables;
    };
}

#endif //JIT_DB_DATABASE_H
