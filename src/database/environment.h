// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_ENVIRONMENT_H
#define JIT_DB_ENVIRONMENT_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include "../frontend/options.h"

namespace pubby
{
    struct type
    {
        std::string name;
        unsigned long size;
    };

    struct field
    {
        std::string name;
        type type;
    };

    struct schema
    {
        std::vector<std::unique_ptr<field>> fields;
    };

    struct table
    {
        std::string name;
        schema &schema;
        std::mutex mutex;
    };

    struct database
    {
        std::string name;
        std::vector<std::unique_ptr<table>> tables;
    };

    struct environment
    {
        std::vector<std::unique_ptr<database>> databases;
    };

    environment load_environment(const options &options);
}

#endif //JIT_DB_ENVIRONMENT_H
