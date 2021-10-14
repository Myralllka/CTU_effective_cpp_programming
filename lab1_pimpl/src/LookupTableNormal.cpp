// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include <cstdlib>
#include <string>

#include "LookupTableNormal.h"

[[maybe_unused]] void LookupTableNormal::insert(int key, const std::string &name) {
    data_.insert(std::make_pair(key, name));
}

[[maybe_unused]] void LookupTableNormal::remove(int key) {
    data_.erase(key);
}

[[maybe_unused]] const std::string *LookupTableNormal::name(int key) const {
    auto iter = data_.find(key);
    if (iter != data_.end())
        return &(iter->second);
    else
        return nullptr;
}

[[maybe_unused]] size_t LookupTableNormal::count() const {
    return data_.size();
}

[[maybe_unused]] void LookupTableNormal::clear() {
    data_.clear();
}