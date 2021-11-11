#define BOOST_TEST_MODULE LookupTableTest
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

#include "LookupTable.h"

BOOST_AUTO_TEST_CASE( LookupTableTest )
{
    // fails with PIMPLed implementation:
    BOOST_TEST( sizeof(LookupTable) == sizeof( std::map<int, std::string> ) );

    // fails with original implementation:
    BOOST_TEST( sizeof(LookupTable) == sizeof(void*) );
    
    LookupTable names;
    
    BOOST_TEST( names.count() == 0);
    
    names.insert(1, "John Doe");
    names.insert(2, "Jane Doe");
    
    BOOST_TEST( names.count() == 2 );    
    BOOST_TEST( names.name(1) != nullptr );
    BOOST_TEST( names.name(2) != nullptr );
    BOOST_TEST( names.name(3) == nullptr);    
    BOOST_TEST( names.name(1)->compare("John Doe") == 0 );
    BOOST_TEST( names.name(2)->compare("Jane Doe") == 0 );

    // will neither insert nor overwrite:
    names.insert(2, "Johnny Doe");

    BOOST_TEST( names.count() == 2 );
    BOOST_TEST( names.name(2) != nullptr );
    BOOST_TEST( names.name(2)->compare("Jane Doe") == 0 );
    
    names.insert(3, "Johnny Doe");
    
    BOOST_TEST( names.count() == 3 );    
    BOOST_TEST (names.name(3) != nullptr);
    BOOST_TEST( names.name(3)->compare("Johnny Doe") == 0 );
    
    names.remove(2);
    
    BOOST_TEST( names.count() == 2 );
    BOOST_TEST( names.name(2) == nullptr );
    
    names.clear();
    
    BOOST_TEST( names.count() == 0 );
    BOOST_TEST (names.name(1) == nullptr);
    BOOST_TEST (names.name(2) == nullptr);
    BOOST_TEST (names.name(3) == nullptr);
}
