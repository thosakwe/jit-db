// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_SCHEMA_H
#define JIT_DB_SCHEMA_H

#include <string>
#include <unordered_map>
#include "Type.h"

namespace jitdb
{
    class Schema
    {
    public:
        Schema();

        Schema(const Schema &other);

        Schema(const Schema &&other);

        ~Schema();

        bool HasField(const std::string &name) const;

        const Type &GetField(const std::string &name) const;

        void SetField(const std::string &name, const Type &type);

        const unsigned long SizeOfOneEntry() const;

    private:
        std::unordered_map<std::string, Type> fields;
    };
}

#endif //JIT_DB_SCHEMA_H
