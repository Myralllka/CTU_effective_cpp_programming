#define BOOST_TEST_MODULE epc_optional_test_3
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <utility>
#include <cstdint>

#include "optional.h"

class X {
    static long constructed_;
    static long default_constructed_;
    static long copy_constructed_;
    static long alive_;
    static long destructed_;

public:
    X() {
        constructed_++;
        default_constructed_++;
        alive_++;
    }

    X(const X &) {
        constructed_++;
        copy_constructed_++;
        alive_++;
    }

    ~X() {
        destructed_++;
        alive_--;
    }

    X &operator=(const X &) = delete;

    static long constructed() { return constructed_; }

    static long default_constructed() { return default_constructed_; }

    static long copy_constructed() { return copy_constructed_; }

    static long alive() { return alive_; }

    static long destructed() { return destructed_; }
};

long X::constructed_ = 0;
long X::default_constructed_ = 0;
long X::copy_constructed_ = 0;
long X::alive_ = 0;
long X::destructed_ = 0;

//namespace ns = std;
namespace ns = epc;

BOOST_AUTO_TEST_CASE(EpcOptionalTest3)
{
    {
        ns::optional<X> o1;

        BOOST_TEST(X::constructed() == 0);
        BOOST_TEST(X::alive() == 0);

        BOOST_TEST((bool) o1 == false);

        ns::optional<X> o1_copy{o1};

        BOOST_TEST(X::constructed() == 0);
        BOOST_TEST(X::alive() == 0);

        BOOST_TEST((bool) o1_copy == false);
    }

    BOOST_TEST(X::constructed() == 0);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 0);

    {
        ns::optional<X> o2(ns::in_place_t{});

        BOOST_TEST(X::constructed() == 1);
        BOOST_TEST(X::default_constructed() == 1);
        BOOST_TEST(X::alive() == 1);

        BOOST_TEST((bool) o2 == true);

        ns::optional<X> o2_copy{o2};

        BOOST_TEST(X::constructed() == 2);
        BOOST_TEST(X::copy_constructed() == 1);
        BOOST_TEST(X::alive() == 2);

        BOOST_TEST((bool) o2_copy == true);
    }

    BOOST_TEST(X::constructed() == 2);
    BOOST_TEST(X::default_constructed() == 1);
    BOOST_TEST(X::copy_constructed() == 1);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 2);

    {
        ns::optional<X> o3(ns::in_place_t{});

        BOOST_TEST(X::constructed() == 3);
        BOOST_TEST(X::default_constructed() == 2);
        BOOST_TEST(X::alive() == 1);

        BOOST_TEST((bool) o3 == true);

        // must fall back to copy:
        ns::optional<X> o3_copy{std::move(o3)};

        BOOST_TEST(X::constructed() == 4);
        BOOST_TEST(X::copy_constructed() == 2);
        BOOST_TEST(X::alive() == 2);

        BOOST_TEST((bool) o3_copy == true);
    }

    BOOST_TEST(X::constructed() == 4);
    BOOST_TEST(X::default_constructed() == 2);
    BOOST_TEST(X::copy_constructed() == 2);
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 4);
}