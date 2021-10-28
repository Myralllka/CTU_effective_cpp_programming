//
// Created by myralllka on 9/28/21.
//
#pragma once

#ifndef TEST_OPTIONAL_H
#define TEST_OPTIONAL_H

#include <utility>

namespace epc {
    template<typename T>
    class optional {
    private:
        bool is_initialized;
        T *m_el;
    public:
        //        Constructors and destructor
        optional() : is_initialized(false) {
            m_el = (T *) ::operator new(sizeof(T));
        };

        ~optional() {
            ::operator delete(m_el);
        };

        optional(const optional &other) : is_initialized(false) {
            if (not other.is_initialized) return;
            std::copy(m_el, other.m_el);
        }
//
//        optional(optional &&other) noexcept {
//
//        }
//
//        template<typename... Ts>
//        [[maybe_unused]] explicit optional(std::in_place_t, Ts &&... args) {
//
//        }
//
//        //      Assignment operators
//
//        optional &operator=(const optional &other) {
//
//        }
//
//        optional &operator=(optional &&other) noexcept {
//
//        }

        //        Other member functions

//        const T *operator->() const {
//
//        }
//
//        T *operator->() {
//
//        }
//
//        const T &operator*() const {
//
//        }
//
//        T &operator*() {
//
//        }
//
        explicit operator bool() const {
            return is_initialized;
        }
//
//        void swap(optional &other) {
//
//        }
//
//        void reset() {
//
//        }

//
//        template <typename... Ts>
//        void emplace(Ts&&... args) {
//
//        }


    };

    template<typename T>
    void swap(optional<T> &a, optional<T> &b);
}

#endif //TEST_OPTIONAL_H
