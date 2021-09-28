//
// Created by myralllka on 9/28/21.
//
#pragma once

#ifndef TEST_OPTIONAL_H
#define TEST_OPTIONAL_H

namespace epc {
    template<typename T>
    class optional {
        //        Constructors and destructor
        optional() = default;

        ~optional() = default;

        optional(const optional &other);

        optional(optional &&other);

        template<typename... Ts>
        optional(std::in_place_t, Ts &&... args);

        //      Assignment operators

        optional &operator=(const optional &other);

        optional &operator=(optional &&other);

        //        Other member functions

        const T *operator->() const;

        T *operator->();

        const T &operator*() const;

        T &operator*();

        operator bool() const;

        void swap(optional &other);

        void reset();

        template<typename... Ts>
        void emplace(Ts... && args);


    };

    template<typename T>
    void swap(optional<T> &a, optional<T> &b);
}

#endif //TEST_OPTIONAL_H
