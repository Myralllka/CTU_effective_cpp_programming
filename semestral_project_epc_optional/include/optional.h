//
// Created by myralllka on 9/28/21.
//
#pragma once

#ifndef TEST_OPTIONAL_H
#define TEST_OPTIONAL_H

#include <utility>
#include <memory>

namespace epc {
    // within namespace epc:
    struct in_place_t {
        explicit in_place_t() = default;
    };

    template<typename T>
    class optional {
    private:
        std::aligned_storage_t<sizeof(T), alignof(T)> m_buffer;

        bool m_has_value;

        [[maybe_unused]] T *ptr() {
            return reinterpret_cast<T *>(&m_buffer);
        }

        [[maybe_unused]] const T *ptr() const {
            return reinterpret_cast<const T *>(&m_buffer);
        }

    public:
        // default constructor and destructor
        optional() : m_has_value(false) {};

        ~optional() {
            if (m_has_value) std::destroy_at(ptr());
        };

        // copy constructor
        optional(const optional &other) : m_has_value(true) {
#ifdef DEBUG
            std::cout << "CC" << std::endl;
#endif
            // if other is empty = do nothing
            if (not other.m_has_value) {
                m_has_value = false;
                return;
            }
            std::construct_at<T>(ptr(), *other);
        }

        // move constructor
        optional(optional &&other) noexcept: m_has_value(true) {
#ifdef DEBUG
            std::cout << "MC" << std::endl;
#endif
            // if other is empty = do nothing
            if (not other.m_has_value) {
                m_has_value = false;
                return;
            }
            std::construct_at<T>(ptr(), std::move(*other));
        }

        template<typename... Ts>
        [[maybe_unused]] explicit optional(epc::in_place_t, Ts &&... args) : m_has_value(true) {
#ifdef DEBUG
            std::cout << "FC" << std::endl;
#endif
            std::construct_at<T>(ptr(), std::forward<Ts>(args)...);
        }

        //      Assignment operators

        // copy assignment operator
        optional &operator=(const optional &other) {
#ifdef DEBUG
            std::cout << "CA" << std::endl;
#endif
            if (other.m_has_value) {
                if (m_has_value) {
                    *ptr() = *other.ptr();
                } else {
                    m_has_value = true;
                    std::construct_at<T>(ptr(), *other);
                }
            } else if (m_has_value) {
                reset();
            }
            return *this;
        }

        // move assignment operator
        optional &operator=(optional &&other) noexcept {
#ifdef DEBUG
            std::cout << "MA" << std::endl;
#endif
            if (other.m_has_value) {
                if (m_has_value) {
                    *ptr() = std::move(*other.ptr());
                } else {
                    m_has_value = true;
                    std::construct_at<T>(ptr(), std::move(*other));
                }
            } else if (m_has_value) {
                reset();
            }
            return *this;
        }

        //        Other member functions

        const T *operator->() const {
            return ptr();
        }

        T *operator->() {
            return ptr();
        }

        const T &operator*() const {
            return *ptr();
        }

        T &operator*() {
            return *ptr();
        }

        [[maybe_unused]] explicit operator bool() const {
            return m_has_value;
        }

        [[maybe_unused]] void swap(optional &other) {
#ifdef DEBUG
            std::cout << "SWAP" << std::endl;
#endif
            if (std::is_swappable_v<T>) {
                ptr()->swap(*other.ptr());
            } else {
                std::swap(*ptr(), *other.ptr());
            }
        }

        [[maybe_unused]] void reset() {
            if (m_has_value) {
                std::destroy_at(ptr());
                m_has_value = false;
            }
        }


//        template<typename... Ts>
//        void emplace(Ts &&... args) {
//            std::cerr << "not implemented_yet" << std::endl;
//        }

    };

    template<typename T>
    void swap(optional<T> &a, optional<T> &b) {
        a.swap(b);
    }
}

#endif //TEST_OPTIONAL_H
