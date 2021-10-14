#include <cstdlib>
#include <string>
#include <map>
#include <unordered_map>

#include "LookupTable.h"

class LookupTable::Impl {
private:
    std::unordered_map<int, std::string> m_data;

public:
    Impl() = default;

    ~Impl() = default;

    void insert(int key, const std::string &name) {
        m_data.insert(std::make_pair(key, name));
    }

    void remove(int key) {
        m_data.erase(key);
    }

    [[nodiscard]] const std::string *name(int key) const {
        auto iter = m_data.find(key);
        if (iter != m_data.end())
            return &(iter->second);
        else
            return nullptr;
    }

    [[nodiscard]] size_t count() const {
        return m_data.size();
    }

    void clear() {
        m_data.clear();
    }
};

class [[maybe_unused]] LookupTable::Impl_map {
private:
    std::map<int, std::string> m_data;

public:
    Impl_map() = default;

    ~Impl_map() = default;

    [[maybe_unused]] void insert(int key, const std::string &name) {
        m_data.insert(std::make_pair(key, name));
    }

    [[maybe_unused]] void remove(int key) {
        m_data.erase(key);
    }

    [[nodiscard]] [[nodiscard]] const std::string *name(int key) const {
        auto iter = m_data.find(key);
        if (iter != m_data.end())
            return &(iter->second);
        else
            return nullptr;
    }

    [[maybe_unused]] [[nodiscard]] size_t count() const {
        return m_data.size();
    }

    [[maybe_unused]] void clear() {
        m_data.clear();
    }
};

LookupTable::LookupTable() : m_pimpl(new Impl{}) {}

LookupTable::~LookupTable() { delete m_pimpl; }

void LookupTable::insert(int key, const std::string &name) {
    m_pimpl->insert(key, name);
}

void LookupTable::remove(int key) {
    m_pimpl->remove(key);
}

const std::string *LookupTable::name(int key) const {
    return m_pimpl->name(key);
}

size_t LookupTable::count() const {
    return m_pimpl->count();
}

void LookupTable::clear() {
    m_pimpl->clear();
}