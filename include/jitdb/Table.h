// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_TABLE_H
#define JIT_DB_TABLE_H

#include "Schema.h"

namespace jitdb
{
    class Table
    {
    public:
        Schema GetSchema() const {
            return schema;
        }

        Table() = default;

        Table(const Table &other) {
            this->schema = Schema(other.schema);
        }

        Table(const Table &&other) {
            this->schema = Schema(other.schema);
        }

    private:
        Schema schema;
    };
}

#endif //JIT_DB_TABLE_H
