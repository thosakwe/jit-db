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
        Table();

        Table(const Table &other);

        Table(const Table &&other);

        ~Table();

        const unsigned long GetNumberOfEntries() const;

        const void *GetData() const;

        void Allocate(unsigned long size);

        Schema &GetSchema();

    private:
        Schema schema;
        char *data = nullptr;
        unsigned long size = 0;
        unsigned long numEntries = 0;
    };
}

#endif //JIT_DB_TABLE_H
