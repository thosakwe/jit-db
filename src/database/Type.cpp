// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Type.h"

jitdb::Type::Type(const std::string &name, const unsigned long size) : size(size) {
    this->name += name;
}

jitdb::Type::Type(const Type &other) : size(other.size) {
    this->name += other.name;
}

jitdb::Type::Type(const Type &&other) : size(other.size) {
    this->name += other.name;
}

const std::string &jitdb::Type::GetName() const {
    return name;
}

const unsigned long jitdb::Type::GetSize() const {
    return size;
}