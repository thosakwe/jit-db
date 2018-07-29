// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_ENVIRONMENT_H
#define JIT_DB_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include "Database.h"

namespace jitdb
{
    class Environment
    {
    public:
        Environment() = default;

        Environment(const Environment &environment) = delete;

        Environment(const Environment &&environment) = delete;

        void AddDatabase(const std::string &name, const Database &database);

    private:
        std::unordered_map<std::string, Database> databases;
    };
}

#endif //JIT_DB_ENVIRONMENT_H
