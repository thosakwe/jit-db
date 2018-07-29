// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Type.h"

jitdb::Type::Type(const std::string& name, const unsigned long size) : name(name), size(size) {

}

jitdb::Type::Type(const Type &other) : name(other.name), size(other.size) {

}

jitdb::Type::Type(const Type &&other) : name(other.name), size(other.size) {

}

const std::string &jitdb::Type::GetName() const {
    return name;
}

const unsigned long jitdb::Type::GetSize() const {
    return size;
}