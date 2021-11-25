//
// Created by myralllka on 11/25/21.
//
#ifndef X_H
#define X_H

#include <iostream>
#include <utility>

#define CASE1

class X {
    int i_;                       // non-negative values represent content...
    static const int EMPTY = -1;  // -1 represents no content

    void destroy() { i_ = EMPTY; }

public:
    X(int i) : i_(i) {}

    ~X() { destroy(); }

    X(const X &other) : i_(other.i_) { std::cout << "(CC)"; }

    X(X &&other) : i_(other.i_) {
        other.destroy();
        std::cout << "(MC)";
    }

    void swap(X &other) { std::swap(i_, other.i_); }

#ifdef CASE1
    X& operator=(const X& other) {
        std::cout << "(CA)";
        // ... to be implemented
    }

    X& operator=(X&& other) {
        std::cout << "(MA)";
        // ... to be implemented
    }
#elif defined CASE2
    X& operator=(const X& other) {
        std::cout << "(CA)";
        // ... to be implemented
    }

    X& operator=(X&& other) {
        std::cout << "(MA)";
        // ... to be implemented
    }
#elif defined CASE3
    X& operator=(X other) {
        std::cout << "(UA)";
        // ... to be implemented
    }
#endif
};

void swap(X &a, X &b) { a.swap(b); }

#endif