#define BOOST_TEST_MODULE PairIntOwnerTest
#include <boost/test/included/unit_test.hpp>

#include "PairInt.h"
#include "PairIntOwner.h"

#include <cstdint>

BOOST_AUTO_TEST_CASE( PairIntOwnerTest )
{
    PairIntOwner emtpy;

    BOOST_TEST( PairInt::constructed() == 0 );
    BOOST_TEST( PairInt::alive() == 0 );
    BOOST_TEST( PairInt::destructed() == 0 );

    {
        PairIntOwner included(PairIntOwner::INCLUDED, 1, 2);

        BOOST_TEST( PairInt::constructed() == 1 );
        BOOST_TEST( PairInt::alive() == 1 );
        BOOST_TEST( PairInt::destructed() == 0 );

        PairInt& value = included.value();

        BOOST_TEST( value.a() == 1 );
        BOOST_TEST( value.b() == 2 );

        // check if value is in included storage of included:

        uintptr_t start_addr_included = (uintptr_t)(&included);
        uintptr_t end_addr_included = start_addr_included + sizeof(included) - 1;
        uintptr_t start_addr_value = (uintptr_t)(&value);
        uintptr_t end_addr_value = start_addr_value + sizeof(PairInt) - 1;

        BOOST_TEST( start_addr_value >= start_addr_included );
        BOOST_TEST( end_addr_value <= end_addr_included );
    }

    BOOST_TEST( PairInt::constructed() == 1 );
    BOOST_TEST( PairInt::alive() == 0 );
    BOOST_TEST( PairInt::destructed() == 1 );

    {
        PairIntOwner dynamic(PairIntOwner::DYNAMIC, 3, 4);

        BOOST_TEST( PairInt::constructed() == 2 );
        BOOST_TEST( PairInt::alive() == 1 );
        BOOST_TEST( PairInt::destructed() == 1 );

        PairInt& value = dynamic.value();

        BOOST_TEST( value.a() == 3 );
        BOOST_TEST( value.b() == 4 );

        // check if value is NOT in included storage of dynamic:

        uintptr_t start_addr_dynamic = (uintptr_t)(&dynamic);
        uintptr_t end_addr_dynamic = start_addr_dynamic + sizeof(dynamic) - 1;
        uintptr_t start_addr_value = (uintptr_t)(&value);
        uintptr_t end_addr_value = start_addr_value + sizeof(PairInt) - 1;

        BOOST_TEST((
                           ( start_addr_value < start_addr_dynamic && end_addr_value < start_addr_dynamic ) ||
                           ( start_addr_value > end_addr_dynamic && end_addr_value > end_addr_dynamic )
                   ));
    }

    BOOST_TEST( PairInt::constructed() == 2 );
    BOOST_TEST( PairInt::alive() == 0 );
    BOOST_TEST( PairInt::destructed() == 2 );
}