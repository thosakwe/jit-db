// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Table.h"

jitdb::Schema &jitdb::Table::GetSchema() {
    return schema;
}

jitdb::Table::Table() = default;

jitdb::Table::Table(const jitdb::Table &other) : schema(other.schema) {
}

jitdb::Table::Table(const jitdb::Table &&other) : schema(other.schema) {
}

jitdb::Table::~Table() {
    delete data;
    data = nullptr;
}

const unsigned long jitdb::Table::GetNumberOfEntries() const {
    return numEntries;
}

const void *jitdb::Table::GetData() const {
    return data;
}

void jitdb::Table::Allocate(unsigned long size) {
    unsigned long newSize = this->size + size;
    auto *newData = new char[size];
    memcpy(newData, data, this->size);
    delete data;
    data = newData;
    this->size = newSize;
}
