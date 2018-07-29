// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "Schema.h"

jitdb::Schema::Schema() = default;

jitdb::Schema::Schema(const jitdb::Schema &other) {
    fields.insert(other.fields.begin(), other.fields.end());
}

jitdb::Schema::Schema(const jitdb::Schema &&other) {
    fields.insert(other.fields.begin(), other.fields.end());
}

jitdb::Schema::~Schema() {
    fields.clear();
}

bool jitdb::Schema::HasField(const std::string &name) const {
    return fields.find(name) != fields.end();
}

const jitdb::Type &jitdb::Schema::GetField(const std::string &name) const {
    return fields.at(name);
}

void jitdb::Schema::SetField(const std::string &name, const jitdb::Type &type) {
    fields.insert(std::make_pair(name, type));
}

const unsigned long jitdb::Schema::SizeOfOneEntry() const {
    unsigned long sum = 0;

    for (auto &pair : fields) {
        sum += pair.second.GetSize();
    }

    return sum;
}