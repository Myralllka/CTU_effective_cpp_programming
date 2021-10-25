#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include <cstdlib>
#include <map>
#include <string>

class LookupTableNormal {
    std::map<int, std::string> data_;

public:
    LookupTableNormal() = default;

    ~LookupTableNormal() = default;

    // copy and move semantics deleted for sake of simplicity:
    LookupTableNormal(const LookupTableNormal &) = delete;

    LookupTableNormal(LookupTableNormal &&) = delete;

    LookupTableNormal &operator=(const LookupTableNormal &) = delete;

    LookupTableNormal &operator=(LookupTableNormal &&) = delete;

    [[maybe_unused]] void insert(int key, [[maybe_unused]] const std::string &name);

    [[maybe_unused]] void remove(int key);

    [[maybe_unused]] [[nodiscard]] const std::string *name(int key) const;

    [[maybe_unused]] [[nodiscard]] size_t count() const;

    [[maybe_unused]] void clear();
};

#endif