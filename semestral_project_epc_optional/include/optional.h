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

        T *ptr() {
            return reinterpret_cast<T *>(&m_buffer);
        }

        const T *ptr() const {
            return reinterpret_cast<const T *>(&m_buffer);
        }

        bool m_has_value;

        explicit operator T &() { return *ptr(); }

    public:
        //        Constructor and destructor
        optional() : m_has_value(false) {};

        ~optional() {
            if (m_has_value) std::destroy_at(ptr());
        };

        // copy constructor
        optional(const optional &other) : m_has_value(true) {
            // if other is empty = do nothing
            if (not other.m_has_value) {
                m_has_value = false;
                return;
            }

            if (std::is_trivially_copyable_v<T>) {
                memcpy(&m_buffer, &other.m_buffer, sizeof(&other.m_buffer));
            } else {
                std::construct_at<T>(ptr(), *other);
            }
        }

        // move constructor
        optional(optional &&other) noexcept: m_has_value(true) {
            // if other is empty = do nothing
            if (not other.m_has_value) {
                m_has_value = false;
                return;
            }
            std::construct_at<T>(ptr(), std::move(*other));
        }

        template<typename... Ts>
        [[maybe_unused]] explicit optional(epc::in_place_t, Ts &&... args) : m_has_value(true) {
            std::construct_at<T>(ptr(), std::forward<Ts>(args)...);
        }

        //      Assignment operators

//        optional &operator=(const optional &other) {
//            std::cerr << "not implemented_yet" << std::endl;
//            exit;
//        }
//
//        optional &operator=(optional &&other) noexcept {
//            std::cerr << "not implemented_yet" << std::endl;
//            exit;
//        }

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

        explicit operator bool() const {
            return m_has_value;
        }

//        void swap(optional &other) {
//            if (other.m_has_value) {
//
//            } else {
//                std::cerr << "not implemented_yet" << std::endl;
//                exit;
//            }
//        }
//
//        void reset() {
//            std::cerr << "not implemented_yet" << std::endl;
//        }
//
//
//        template<typename... Ts>
//        void emplace(Ts &&... args) {
//            std::cerr << "not implemented_yet" << std::endl;
//        }


    };

//    template<typename T>
//    void swap(optional<T> &a, optional<T> &b);
}

#endif //TEST_OPTIONAL_H
