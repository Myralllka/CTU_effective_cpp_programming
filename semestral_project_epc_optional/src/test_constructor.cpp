//
// Created by myralllka on 10/28/21.
//

#define BOOST_TEST_MODULE epc_optional_test_2

#include <boost/test/included/unit_test.hpp>

#include "optional.h"

#include <cstdint>
#include <optional>

class X {
    static long constructed_;
    static long default_constructed_;
    static long converting_constructed_1_;
    static long converting_constructed_2_;
    static long converting_constructed_3_;
    static long alive_;
    static long destructed_;
public:

    X() {
        constructed_++;
        default_constructed_++;
        alive_++;
    }

    X(const int &) {
        constructed_++;
        converting_constructed_1_++;
        alive_++;
    }

    X(int &&) {
        constructed_++;
        converting_constructed_2_++;
        alive_++;
    }

    X(double) {
        constructed_++;
        converting_constructed_3_++;
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

    static long constructed() { return constructed_; }

    static long default_constructed() { return default_constructed_; }

    static long converting_constructed_1() { return converting_constructed_1_; }

    static long converting_constructed_2() { return converting_constructed_2_; }

    static long converting_constructed_3() { return converting_constructed_3_; }

    static long alive() { return alive_; }

    static long destructed() { return destructed_; }
};

long X::constructed_ = 0;
long X::default_constructed_ = 0;
long X::converting_constructed_1_ = 0;
long X::converting_constructed_2_ = 0;
long X::converting_constructed_3_ = 0;
long X::alive_ = 0;
long X::destructed_ = 0;

namespace ns = epc;
//namespace ns = eps;

BOOST_AUTO_TEST_CASE(EpcOptionalTest2)
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
        ns::optional<X> o2(ns::in_place_t{});

        BOOST_TEST(X::constructed() == 1);
        BOOST_TEST(X::default_constructed() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 0);

        BOOST_TEST((bool) o2 == true);
    }

    BOOST_TEST(X::constructed() == 1);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 1);

    {
        int i = 1;

        ns::optional<X> o3(ns::in_place_t{}, i);

        BOOST_TEST(X::constructed() == 2);
        BOOST_TEST(X::converting_constructed_1() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 1);

        BOOST_TEST((bool) o3 == true);
    }

    BOOST_TEST(X::constructed() == 2);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 2);

    {
        ns::optional<X> o4(ns::in_place_t{}, 1);

        BOOST_TEST(X::constructed() == 3);
        BOOST_TEST(X::converting_constructed_2() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 2);

        BOOST_TEST((bool) o4 == true);
    }

    BOOST_TEST(X::constructed() == 3);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 3);

    {
        ns::optional<X> o5(ns::in_place_t{}, 1.0);

        BOOST_TEST(X::constructed() == 4);
        BOOST_TEST(X::converting_constructed_3() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 3);

        BOOST_TEST((bool) o5 == true);
    }

    BOOST_TEST(X::constructed() == 4);
    BOOST_TEST(X::default_constructed() == 1);
    BOOST_TEST(X::converting_constructed_1() == 1);
    BOOST_TEST(X::converting_constructed_2() == 1);
    BOOST_TEST(X::converting_constructed_3() == 1);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 4);
}