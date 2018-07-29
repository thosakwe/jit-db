// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Type.h"

jitdb::Type::Type(const unsigned long size) : size(size) {

}

jitdb::Type::Type(const Type &other) : size(other.size) {

}

jitdb::Type::Type(const Type &&other) : size(other.size) {

}

const unsigned long jitdb::Type::GetSize() const {
    return size;
}