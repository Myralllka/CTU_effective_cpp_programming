#ifndef X_H
#define X_H

#include <iostream>
#include <utility>

struct in_place_t { };

struct X
{
    template <typename... Ts>
    X(in_place_t, Ts&&...) { }

    X(const X&) { std::cout << "(CC)"; };
    X(X&&) { std::cout << "(MC)"; }
};

#ifdef CASE1

template <typename... Ts>
X make_X(Ts&&... params)
{
    // ... to be implemented
}

#elif defined CASE2

template <typename... Ts>
X make_X(Ts&&... params)
{
    // ... to be implemented
}

#elif defined CASE3

template <typename... Ts>
X make_X(Ts&&... params)
{
    // ... to be implemented
}

#endif

#endif