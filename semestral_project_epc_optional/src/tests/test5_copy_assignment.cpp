#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE epc_optional_test_5

#include <boost/test/included/unit_test.hpp>

#include <cstdint>
#include <utility>

#include "optional.h"

class X {
    static long constructed_;
    static long default_constructed_;
    static long copy_constructed_;
    static long move_constructed_;
    static long copy_assigned_;
    static long move_assigned_;
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

    X(X &&) {
        constructed_++;
        move_constructed_++;
        alive_++;
    }

    X &operator=(const X &) {
        copy_assigned_++;
        return *this;
    }

    X &operator=(X &&) {
        move_assigned_++;
        return *this;
    }

    ~X() {
        destructed_++;
        alive_--;
    }

    static long constructed() { return constructed_; }

    static long default_constructed() { return default_constructed_; }

    static long copy_constructed() { return copy_constructed_; }

    static long move_constructed() { return move_constructed_; }

    static long copy_assigned() { return copy_assigned_; }

    static long move_assigned() { return move_assigned_; }

    static long alive() { return alive_; }

    static long destructed() { return destructed_; }

    static void reset_counters() {
        constructed_ = 0;
        default_constructed_ = 0;
        copy_constructed_ = 0;
        move_constructed_ = 0;
        copy_assigned_ = 0;
        move_assigned_ = 0;
        alive_ = 0;
        destructed_ = 0;
    }
};

long X::constructed_ = 0;
long X::default_constructed_ = 0;
long X::copy_constructed_ = 0;
long X::move_constructed_ = 0;
long X::copy_assigned_ = 0;
long X::move_assigned_ = 0;
long X::alive_ = 0;
long X::destructed_ = 0;

//namespace ns = std;
namespace ns = epc;

BOOST_AUTO_TEST_CASE(EpcOptionalTest5)
{
    // case #1 - both source and destination does not contain value:

    X::reset_counters();
    {

        ns::optional<X> o1;
        ns::optional<X> o2;

        BOOST_TEST(X::constructed() == 0);
        BOOST_TEST(X::alive() == 0);

        BOOST_TEST((bool) o1 == false);
        BOOST_TEST((bool) o2 == false);

        o2 = o1;

        BOOST_TEST(X::constructed() == 0);
        BOOST_TEST(X::alive() == 0);

        BOOST_TEST(X::copy_constructed() == 0);
        BOOST_TEST(X::move_constructed() == 0);
        BOOST_TEST(X::copy_assigned() == 0);
        BOOST_TEST(X::move_assigned() == 0);

        BOOST_TEST((bool) o1 == false);
        BOOST_TEST((bool) o2 == false);
    }

    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 0);

    // case #2 - source does contain value, destination does not contain value:
    X::reset_counters();
    {
        ns::optional<X> o1;
        ns::optional<X> o2(ns::in_place_t{});

        BOOST_TEST(X::constructed() == 1);
        BOOST_TEST(X::default_constructed() == 1);
        BOOST_TEST(X::alive() == 1);

        BOOST_TEST((bool) o1 == false);
        BOOST_TEST((bool) o2 == true);

        o1 = o2;

        BOOST_TEST(X::constructed() == 2);
        BOOST_TEST(X::alive() == 2);

        BOOST_TEST(X::copy_constructed() == 1);
        BOOST_TEST(X::move_constructed() == 0);
        BOOST_TEST(X::copy_assigned() == 0);
        BOOST_TEST(X::move_assigned() == 0);

        BOOST_TEST((bool) o1 == true);
        BOOST_TEST((bool) o2 == true);
    }

    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 2);

    // case #3 - source does not contain value, destination does contain value:

    X::reset_counters();
    {
        ns::optional<X> o1(ns::in_place_t{});
        ns::optional<X> o2;

        BOOST_TEST(X::constructed() == 1);
        BOOST_TEST(X::default_constructed() == 1);
        BOOST_TEST(X::alive() == 1);

        BOOST_TEST((bool) o1 == true);
        BOOST_TEST((bool) o2 == false);

        o1 = o2;

        BOOST_TEST(X::destructed() == 1);
        BOOST_TEST(X::alive() == 0);

        BOOST_TEST(X::copy_constructed() == 0);
        BOOST_TEST(X::move_constructed() == 0);
        BOOST_TEST(X::copy_assigned() == 0);
        BOOST_TEST(X::move_assigned() == 0);

        BOOST_TEST((bool) o1 == false);
        BOOST_TEST((bool) o2 == false);
    }

    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 1);

    // case #4 - both source and destination does contain value:

    X::reset_counters();
    {
        ns::optional<X> o1(ns::in_place_t{});
        ns::optional<X> o2(ns::in_place_t{});

        BOOST_TEST(X::constructed() == 2);
        BOOST_TEST(X::default_constructed() == 2);
        BOOST_TEST(X::alive() == 2);

        BOOST_TEST((bool) o1 == true);
        BOOST_TEST((bool) o2 == true);

        o1 = o2;

        BOOST_TEST(X::alive() == 2);
        BOOST_TEST(X::destructed() >= 0);        // copy-and-swap allowed

        BOOST_TEST(X::copy_constructed() >= 0);  // copy-and-swap allowed
        BOOST_TEST(X::move_constructed() == 0);
        BOOST_TEST(X::copy_assigned() == 1);
        BOOST_TEST(X::move_assigned() == 0);

        BOOST_TEST((bool) o1 == true);
        BOOST_TEST((bool) o2 == true);
    }

    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() >= 2); // copy-and-swap allowed
}