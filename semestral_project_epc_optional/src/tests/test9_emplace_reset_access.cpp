#define BOOST_TEST_MODULE epc_optional_test_9
#include <boost/test/included/unit_test.hpp>

#include "optional.h"

#include <cstdint>
#include <optional>
#include <utility>

class X
{
    static long constructed_;
    static long converting_constructed_1_;
    static long converting_constructed_2_;
    static long converting_constructed_3_;
    static long alive_;
    static long destructed_;

    int i_;

public:
    X(const int& i) : i_(i)
    {
        converting_constructed_1_++;
        constructed_++;
        alive_++;
    }

    X(int&& i) : i_(i)
    {
        converting_constructed_2_++;
        constructed_++;
        alive_++;
    }

    X(void*) : i_(-1)
    {
        converting_constructed_3_++;
        constructed_++;
        alive_++;
    }

    ~X()
    {
        destructed_++;
        alive_--;
    }

    operator int() { return i_; }

    static long constructed() { return constructed_; }
    static long converting_constructed_1() { return converting_constructed_1_; }
    static long converting_constructed_2() { return converting_constructed_2_; }
    static long converting_constructed_3() { return converting_constructed_3_; }
    static long alive()       { return alive_; }
    static long destructed()  { return destructed_; }

    static void reset_counters()
    {
        constructed_ = 0;
        converting_constructed_1_ = 0;
        converting_constructed_2_ = 0;
        converting_constructed_3_ = 0;
        alive_ = 0;
        destructed_ = 0;
    }
};

long X::constructed_ = 0;
long X::converting_constructed_1_ = 0;
long X::converting_constructed_2_ = 0;
long X::converting_constructed_3_ = 0;
long X::alive_ = 0;
long X::destructed_ = 0;

namespace ns = std;
//namespace ns = epc;

BOOST_AUTO_TEST_CASE( EpcOptionalTest9 )
{
    X::reset_counters();
    {
        ns::optional<X> o;

        BOOST_TEST( (bool)o == false );

        BOOST_TEST( X::constructed() == 0 );
        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 0 );

        o.reset();

        BOOST_TEST( X::constructed() == 0 );
        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 0 );

        int i = 1;
        o.emplace(i);

        BOOST_TEST( (bool)o == true );
        BOOST_TEST( X::constructed() == 1 );
        BOOST_TEST( X::converting_constructed_1() == 1 );
        BOOST_TEST( X::converting_constructed_2() == 0 );
        BOOST_TEST( X::converting_constructed_3() == 0 );
        BOOST_TEST( X::alive() == 1 );

        int j = (*o).operator int();
        int k = o->operator int();

        BOOST_TEST( j == 1 );
        BOOST_TEST( k == 1 );

        o.reset();

        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 1 );
    }
    BOOST_TEST( X::alive() == 0 );
    BOOST_TEST( X::destructed() == 1 );

    X::reset_counters();
    {
        ns::optional<X> o;

        BOOST_TEST( (bool)o == false );

        BOOST_TEST( X::constructed() == 0 );
        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 0 );

        o.emplace(2);

        BOOST_TEST( (bool)o == true );
        BOOST_TEST( X::constructed() == 1 );
        BOOST_TEST( X::converting_constructed_1() == 0 );
        BOOST_TEST( X::converting_constructed_2() == 1 );
        BOOST_TEST( X::converting_constructed_3() == 0 );
        BOOST_TEST( X::alive() == 1 );

        int j = (*o).operator int();
        int k = o->operator int();

        BOOST_TEST( j == 2 );
        BOOST_TEST( k == 2 );

        o.reset();

        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 1 );
    }
    BOOST_TEST( X::alive() == 0 );
    BOOST_TEST( X::destructed() == 1 );

    X::reset_counters();
    {
        ns::optional<X> o;

        BOOST_TEST( (bool)o == false );

        BOOST_TEST( X::constructed() == 0 );
        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 0 );

        o.emplace(nullptr);

        BOOST_TEST( (bool)o == true );
        BOOST_TEST( X::constructed() == 1 );
        BOOST_TEST( X::converting_constructed_1() == 0 );
        BOOST_TEST( X::converting_constructed_2() == 0 );
        BOOST_TEST( X::converting_constructed_3() == 1 );
        BOOST_TEST( X::alive() == 1 );

        int j = (*o).operator int();
        int k = o->operator int();

        BOOST_TEST( j == -1 );
        BOOST_TEST( k == -1 );

        o.reset();

        BOOST_TEST( X::alive() == 0 );
        BOOST_TEST( X::destructed() == 1 );
    }
    BOOST_TEST( X::alive() == 0 );
    BOOST_TEST( X::destructed() == 1 );
}