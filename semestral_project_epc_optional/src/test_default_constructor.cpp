//
// Created by myralllka on 10/28/21.
//

#define BOOST_TEST_MODULE epc_optional_test_1

#include <boost/test/included/unit_test.hpp>

#include "optional.h"

#include <cstdint>
#include <optional>

class X {
    int i_;

    static long constructed_;
    static long alive_;
    static long destructed_;
public:

    X(int i) : i_(i) {
        constructed_++;
        alive_++;
    }

    ~X() {
        destructed_++;
        alive_--;
    }

    X(const X &) = delete;

    X(X &&) = delete;

    X &operator=(const X &) = delete;

    X &operator=(X &&) = delete;

    operator const int &() const { return i_; }

    static long constructed() { return constructed_; }

    static long alive() { return alive_; }

    static long destructed() { return destructed_; }
};

long X::constructed_ = 0;
long X::alive_ = 0;
long X::destructed_ = 0;

namespace ns = epc;
//namespace ns = eps;

BOOST_AUTO_TEST_CASE(EpcOptionalTest1)
{
    {
        ns::optional<X> o1;

        BOOST_TEST(X::constructed() == 0);
        BOOST_TEST(X::alive() == 0);
        BOOST_TEST(X::destructed() == 0);

        BOOST_TEST((bool) o1 == false);
    }

    BOOST_TEST(X::constructed() == 0);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 0);

    {
        ns::optional<X> o2(ns::in_place_t{}, 1);

        BOOST_TEST(X::constructed() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 0);

        BOOST_TEST((bool) o2 == true);

        X &value = *o2;

        BOOST_TEST((int) value == 1);

        uintptr_t start_addr_o2 = (uintptr_t) (&o2);
        uintptr_t end_addr_o2 = start_addr_o2 + sizeof(o2) - 1;
        uintptr_t start_addr_value = (uintptr_t) (&value);
        uintptr_t end_addr_value = start_addr_value + sizeof(X) - 1;

        BOOST_TEST(start_addr_value >= start_addr_o2);
        BOOST_TEST(end_addr_value <= end_addr_o2);
    }

    BOOST_TEST(X::constructed() == 1);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 1);
}