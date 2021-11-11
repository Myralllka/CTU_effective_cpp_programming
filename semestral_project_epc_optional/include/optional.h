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

        T *ptr() { return reinterpret_cast<T *>(&m_buffer); }

        bool m_is_initialized;

        explicit operator T &() { return *ptr(); }

    public:
        //        Constructors and destructor
        optional() : m_is_initialized(false) {};

        ~optional() {
            if (m_is_initialized) std::destroy_at(ptr());
        };

//        optional(const optional &other) : m_is_initialized(true) {
//            if (not other.m_is_initialized) return;
//            std::copy(m_buffer, other.m_el);
//        }

        optional(optional &&other) noexcept: m_is_initialized(true) {
            std::construct_at<T>(ptr(), std::forward<T>(other.m_buffer));
        }

        template<typename... Ts>
        [[maybe_unused]] explicit optional(epc::in_place_t, Ts &&... args) : m_is_initialized(true) {
            std::construct_at<T>(ptr(), std::forward<Ts>(args)...);
        }

        //      Assignment operators

        optional &operator=(const optional &other) {
            std::cerr << "not implemented_yet" << std::endl;
            exit;
        }

        optional &operator=(optional &&other) noexcept {
            std::cerr << "not implemented_yet" << std::endl;
            exit;
        }

        //        Other member functions

        const T *operator->() const {
            std::cerr << "not implemented_yet" << std::endl;
            exit;
        }

        T *operator->() {
            std::cerr << "not implemented_yet" << std::endl;
            exit;
        }

        const T &operator*() const {
            std::cerr << "not implemented_yet" << std::endl;
            exit;
        }

        T &operator*() {
            return *ptr();
        }

        explicit operator bool() const {
            return m_is_initialized;
        }

        void swap(optional &other) {
            if (other.m_is_initialized) {

            } else {
                std::cerr << "not implemented_yet" << std::endl;
                exit;
            }
        }

        void reset() {
            std::cerr << "not implemented_yet" << std::endl;
        }

//
        template<typename... Ts>
        void emplace(Ts &&... args) {
            std::cerr << "not implemented_yet" << std::endl;
        }


    };

    template<typename T>
    void swap(optional<T> &a, optional<T> &b);
}

#endif //TEST_OPTIONAL_H
