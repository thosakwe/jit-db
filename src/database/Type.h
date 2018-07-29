// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_TYPE_H
#define JIT_DB_TYPE_H

#include <string>

namespace jitdb
{
    class Type
    {
    public:
        Type(const std::string &name, unsigned long size);

        Type(const Type &other);

        Type(const Type &&other);

        const std::string &GetName() const;

        const unsigned long GetSize() const;

    private:
        std::string &name;
        const unsigned long size;
    };
}

#endif //JIT_DB_TYPE_H
