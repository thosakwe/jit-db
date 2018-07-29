// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef JIT_DB_TYPE_H
#define JIT_DB_TYPE_H

namespace jitdb
{
    class Type
    {
    public:
        Type(const unsigned long size) : size(size) {

        }

        Type(const Type &other) : size(other.size) {

        }

        Type(const Type &&other) : size(other.size) {

        }

        const unsigned long GetSize() const {
            return size;
        }

    private:
        const unsigned long size;
    };
}

#endif //JIT_DB_TYPE_H
