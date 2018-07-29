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
        Schema() = default;

        Schema(const Schema &other) {
            fields.insert(other.fields.begin(), other.fields.end());
        }

        Schema(const Schema &&other) {
            fields.insert(other.fields.begin(), other.fields.end());
        }

        ~Schema() {
            fields.clear();
        }

        bool HasField(const std::string &name) const {
            return fields.find(name) != fields.end();
        }

        const Type &GetField(const std::string &name) const {
            return fields.at(name);
        }

        void SetField(const std::string &name, const Type &type) {
            fields.insert(std::make_pair(name, type));
        }

    private:
        std::unordered_map<std::string, Type> fields;
    };
}

#endif //JIT_DB_SCHEMA_H
