// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_TABLE_H
#define JIT_DB_TABLE_H

#include <cstring>
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

        ~Table() {
            delete data;
            data = nullptr;
        }

        const unsigned long GetNumberOfEntries() const {
            return numEntries;
        }

        const void *GetData() const {
            return data;
        }

        void Allocate(unsigned long size) {
            unsigned long newSize = this->size + size;
            auto *newData = (void *) new char[size];
            memcpy(newData, data, this->size);
            delete data;
            data = newData;
            this->size = newSize;
        }

    private:
        Schema schema;
        void *data = nullptr;
        unsigned long size = 0;
        unsigned long numEntries = 0;
    };
}

#endif //JIT_DB_TABLE_H
