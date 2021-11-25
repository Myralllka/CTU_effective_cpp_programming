#ifndef VALUE_PTR_H
#define VALUE_PTR_H

#include <new>

template<typename T>
class ValuePtr {
private:
    // state == 0 -> not initialized
    // state == 1 -> ptr ownership passed
    // state == 2 -> object inside the local storage
    int8_t m_state;

    union {
        std::aligned_storage<sizeof(T), alignof(T)> m_buffer;
        T *m_trans_ptr;
    };

    T *m_ptr() {
        if (m_state == 2)
            return reinterpret_cast<T *> (&m_buffer);
        return m_trans_ptr;
    }

    const T *m_ptr() const {
        if (m_state == 2)
            return reinterpret_cast<const T *> (&m_buffer);
        return m_trans_ptr;
    }

public:
    ValuePtr() : m_state(0) {};


    ~ValuePtr() {
        if (m_state)
            m_ptr()->~T();
    }

    explicit ValuePtr(T *ptr) : m_state(1) {
        m_trans_ptr = ptr;
    }

    ValuePtr(const ValuePtr &other) : m_state(2) {
        if (other.m_state) {
            new(m_ptr()) T(*other.m_ptr());
        } else {
            m_state = 0;
        }
    }

    ValuePtr(ValuePtr &&other) noexcept: m_state(2) {
        if (other.m_state) {
            new(m_ptr()) T(std::move(*other.m_ptr()));
        } else {
            m_state = 0;
        }
    }

    ValuePtr &operator=(const ValuePtr &) = delete;

    ValuePtr &operator=(ValuePtr &&) = delete;

    T &operator*() { return *m_ptr(); }

    T *operator->() { return m_ptr(); }

    [[maybe_unused]] T *get() { return m_ptr(); }
};

#endif
