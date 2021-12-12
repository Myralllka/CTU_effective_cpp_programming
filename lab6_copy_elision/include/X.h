#ifndef X_H
#define X_H

#include <iostream>
#include <utility>

struct in_place_t {
};

struct X {
    template<typename... Ts>
    X(in_place_t, Ts &&...) {}  // converting-forwarding constructor

    X(const X &) { std::cout << "(CC)"; };  // copy constructor

    X(X &&) { std::cout << "(MC)"; }    // move constructor
};

#ifdef CASE1

template<typename... Ts>
X make_X(Ts &&... params) {
    X tmp = X{in_place_t{}, std::forward<Ts>(params)...};
    return X{in_place_t{}, std::forward<Ts>(params)...};
}

#elif defined CASE2

template <typename... Ts>
X make_X(Ts&&... params)
{
    X tmp = X{in_place_t{}, std::forward<Ts>(params)...};
    return tmp;
}

#elif defined CASE3

template<typename... Ts>
X make_X(Ts &&... params) {
    return std::move(X{in_place_t{}, std::forward<Ts>(params)...});
}

#endif

#endif