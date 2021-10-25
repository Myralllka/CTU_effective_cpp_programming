#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H


#include <string>

class LookupTable {
private:
    class [[maybe_unused]] Impl;
    class [[maybe_unused]] Impl_map;

    Impl *m_pimpl;

public:
    LookupTable();

    ~LookupTable();

    // copy and move semantics deleted for sake of simplicity:
    LookupTable(const LookupTable &) = delete;

    LookupTable(LookupTable &&) = delete;

    LookupTable &operator=(const LookupTable &) = delete;

    LookupTable &operator=(LookupTable &&) = delete;

    // implementation
    void insert(int key, const std::string &name);

    void remove(int key);

    [[nodiscard]] const std::string *name(int key) const;

    [[nodiscard]] size_t count() const;

    void clear();
};

#endif