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
        Database();

        Database(const Database &other);

        Database(const Database &&other);

        ~Database();

        bool HasTable(const std::string &name) const;

        const Table &GetTable(const std::string &name) const;

        void SetTable(const std::string &name, const Table &table);

        // bool Query(const std::string &query, const char **errorMessage);

    private:
        std::unordered_map<std::string, Table> tables;
    };
}

#endif //JIT_DB_DATABASE_H
