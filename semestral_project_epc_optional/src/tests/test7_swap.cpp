#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE epc_optional_test_7

#include <boost/test/included/unit_test.hpp>

#include <cstdint>
#include <utility>

#include "optional.h"

class X {
    static long constructed_;
    static long copy_constructed_;
    static long move_constructed_;
    static long alive_;
    static long destructed_;

    int i_;

public:
    X(int i) : i_(i) {
        constructed_++;
        alive_++;
    }

    X(const X &other) : i_(other.i_) {
        constructed_++;
        copy_constructed_++;
        alive_++;
    }

    X(X &&other) : i_(other.i_) {
        constructed_++;
        move_constructed_++;
        alive_++;
    }

    X &operator=(const X &other) {
        i_ = other.i_;
        return *this;
    }

    X &operator=(X &&other) {
        i_ = other.i_;
        return *this;
    }

    ~X() {
        destructed_++;
        alive_--;
    }

    operator int() { return i_; }

    static long constructed() { return constructed_; }

    static long copy_constructed() { return copy_constructed_; }

    static long move_constructed() { return move_constructed_; }

    static long alive() { return alive_; }

    static long destructed() { return destructed_; }

    static void reset_counters() {
        constructed_ = 0;
        copy_constructed_ = 0;
        move_constructed_ = 0;
        alive_ = 0;
        destructed_ = 0;
    }
};

long X::constructed_ = 0;
long X::copy_constructed_ = 0;
long X::move_constructed_ = 0;
long X::alive_ = 0;
long X::destructed_ = 0;

//namespace ns = std;
namespace ns = epc;

BOOST_AUTO_TEST_CASE(EpcOptionalTest7)
{
    X::reset_counters();
    {
        ns::optional<X> o1;
        ns::optional<X> o2;

        ns::swap(o1, o2);

        BOOST_TEST((bool) o1 == false);
        BOOST_TEST((bool) o2 == false);

        BOOST_TEST(X::constructed() == 0);
    }

    X::reset_counters();
    {
        ns::optional<X> o1{ns::in_place_t{}, 1};
        ns::optional<X> o2;

        ns::swap(o1, o2);

        BOOST_TEST((bool) o1 == false);
        BOOST_TEST((bool) o2 == true);
        BOOST_TEST(o2->operator int() == 1);

        BOOST_TEST(X::constructed() == 2);
        BOOST_TEST(X::move_constructed() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 1);
    }
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 2);

    X::reset_counters();
    {
        ns::optional<X> o1;
        ns::optional<X> o2{ns::in_place_t{}, 1};

        ns::swap(o1, o2);

        BOOST_TEST((bool) o1 == true);
        BOOST_TEST((bool) o2 == false);
        BOOST_TEST(o1->operator int() == 1);

        BOOST_TEST(X::constructed() == 2);
        BOOST_TEST(X::move_constructed() == 1);
        BOOST_TEST(X::alive() == 1);
        BOOST_TEST(X::destructed() == 1);
    }
    BOOST_TEST(X::alive() == 0);
    BOOST_TEST(X::destructed() == 2);

    X::reset_counters();
    {
        ns::optional<X> o1{ns::in_place_t{}, 1};
        ns::optional<X> o2{ns::in_place_t{}, 2};

        ns::swap(o1, o2);

        BOOST_TEST((bool) o1 == true);
        BOOST_TEST((bool) o2 == true);
        BOOST_TEST(o1->operator int() == 2);
        BOOST_TEST(o2->operator int() == 1);
    }
    BOOST_TEST(X::alive() == 0);
}