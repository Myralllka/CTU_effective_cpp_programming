// To test your solutoin, set the "ns" namespace to "epc" below !!!
// namespace ns = std;
#define BOOST_TEST_MODULE epc_optional_final_test

#include <boost/test/included/unit_test.hpp>
#include "optional.h"

#include <cmath>

#include <cstdint>
#include <optional>
#include <utility>

namespace ns = epc;

class X
{
   // counter variables:
   static unsigned long
      constructed_,
      default_constructed_,
      converting_lvalue_int_constructed_,
      converting_rvalue_int_constructed_,
      converting_double_constructed_,
      copy_constructed_,
      move_constructed_,
      copy_assigned_,
      move_assigned_,
      swapped_,
      alive_,
      destructed_;

   int i_;  // object content

   static const int EMPTY = -1;  // empty content

public:
   // default constructor:
   X() : i_(EMPTY)  // set empty state
   {
      constructed_++;
      default_constructed_++;
      alive_++;
   }

   // converting constructor #1 (for lvalue arguments of type int)
   X(const int& i) : i_(i)
   {
      constructed_++;
      converting_lvalue_int_constructed_++;
      alive_++;
   }

   // converting constructor #2 (for rvalue arguments of type int)
   X(int&& i) : i_(i)
   {
      constructed_++;
      converting_rvalue_int_constructed_++;
      alive_++;
   }

   // converting constructor #3 (for arguments of type double)
   X(double d) : i_(std::lround(d))  // round to nearest integer
   {
      constructed_++;
      converting_double_constructed_++;
      alive_++;
   }

   // copy constructor:
   X(const X& other) : i_(other.i_)
   {
      constructed_++;
      copy_constructed_++;
      alive_++;
   }

   // move constructor:
   X(X&& other) : i_(other.i_)
   {
      other.i_ = EMPTY;

      constructed_++;
      move_constructed_++;
      alive_++;
   }

   // copy assignment operator:
   X& operator=(const X& other)
   {
      if (this != &other)
      {
         i_ = EMPTY;
         i_ = other.i_;
      }

      copy_assigned_++;

      return *this;
   }

   // move assignment operator:
   X& operator=(X&& other)
   {
      if (this != &other)
      {
         i_ = EMPTY;
         i_ = other.i_;
         other.i_ = EMPTY;
      }

      move_assigned_++;

      return *this;
   }

   // destructor:
   ~X()
   {
      destructed_++;
      alive_--;
   }

   // empty check:
   bool empty() const { return i_ == EMPTY; }

   // get content:
   int value() const { return i_; }

   void swap(X& other)
   {
      std::swap(i_, other.i_);

      swapped_++;
   }

   static unsigned long constructed() { return constructed_; }
   static unsigned long default_constructed() { return default_constructed_; }
   static unsigned long converting_lvalue_int_constructed() { return converting_lvalue_int_constructed_; }
   static unsigned long converting_rvalue_int_constructed() { return converting_rvalue_int_constructed_; }
   static unsigned long converting_double_constructed() { return converting_double_constructed_; }
   static unsigned long copy_constructed() { return copy_constructed_; }
   static unsigned long move_constructed() { return move_constructed_; }
   static unsigned long move_assigned() { return move_assigned_; }
   static unsigned long copy_assigned() { return copy_assigned_; }
   static unsigned long swapped() { return swapped_; }
   static unsigned long alive() { return alive_; }
   static unsigned long destructed() { return destructed_; }

   static unsigned long sum_counters()
   {
      return
         constructed_ +
         default_constructed_ +
         converting_lvalue_int_constructed_ +
         converting_rvalue_int_constructed_ +
         converting_double_constructed_ +
         copy_constructed_ +
         move_constructed_ +
         copy_assigned_ +
         move_assigned_ +
         swapped_ +
         alive_ +
         destructed_;
   }

   static void reset_counters()
   {
      constructed_ = 0;
      default_constructed_ = 0;
      converting_lvalue_int_constructed_ = 0;
      converting_rvalue_int_constructed_ = 0;
      converting_double_constructed_ = 0;
      copy_constructed_ = 0;
      move_constructed_ = 0;
      copy_assigned_ = 0;
      move_assigned_ = 0;
      swapped_ = 0;
      alive_ = 0;
      destructed_ = 0;
   }
};

void swap(X& a, X& b) { a.swap(b); }

unsigned long X::constructed_ = 0;
unsigned long X::default_constructed_ = 0;
unsigned long X::converting_lvalue_int_constructed_ = 0;
unsigned long X::converting_rvalue_int_constructed_ = 0;
unsigned long X::converting_double_constructed_ = 0;
unsigned long X::copy_constructed_ = 0;
unsigned long X::move_constructed_ = 0;
unsigned long X::copy_assigned_ = 0;
unsigned long X::move_assigned_ = 0;
unsigned long X::swapped_ = 0;
unsigned long X::alive_ = 0;
unsigned long X::destructed_ = 0;

BOOST_AUTO_TEST_CASE( empty_optional_test )
{
   X::reset_counters();
   {
      ns::optional<X> o;

      BOOST_TEST( X::constructed() == 0 );
      BOOST_TEST( X::alive() == 0 );
      BOOST_TEST( X::sum_counters() == 0 );

      BOOST_TEST( (bool)o == false );
   }
   BOOST_TEST( X::destructed() == 0 );
   BOOST_TEST( X::sum_counters() == 0 );
}

BOOST_AUTO_TEST_CASE( default_constructor_test )
{
   X::reset_counters();
   {
      ns::optional<X> o(ns::in_place_t{});

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::default_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( o->empty() == true );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );
}

BOOST_AUTO_TEST_CASE( converting_constructor_test )
{
   X::reset_counters();
   {
      int i = 12;
      ns::optional<X> o(ns::in_place_t{}, i);

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::converting_lvalue_int_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( (*o).value() == 12 );
      BOOST_TEST( o->value() == 12 );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );

   X::reset_counters();
   {
      ns::optional<X> o(ns::in_place_t{}, 34);

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::converting_rvalue_int_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( (*o).value() == 34 );
      BOOST_TEST( o->value() == 34 );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );

   X::reset_counters();
   {
      ns::optional<X> o(ns::in_place_t{}, 56.2);

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::converting_double_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( (*o).value() == 56 );
      BOOST_TEST( o->value() == 56 );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );
}

BOOST_AUTO_TEST_CASE( included_storage_test )
{
   X::reset_counters();
   {
      ns::optional<int> o(ns::in_place_t{}, 123);

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( *o == 123 );

      *o = 456;

      BOOST_TEST( *o == 456 );

      int& value = *o;

      BOOST_TEST( value == 456 );

      uintptr_t start_addr_o = (uintptr_t)(&o);
      uintptr_t end_addr_o = start_addr_o + sizeof(o) - 1;
      uintptr_t start_addr_value = (uintptr_t)(&value);
      uintptr_t end_addr_value = start_addr_value + sizeof(int) - 1;

      BOOST_TEST( start_addr_value >= start_addr_o );
      BOOST_TEST( end_addr_value <= end_addr_o );

      BOOST_TEST( start_addr_value % alignof(int) == 0 );
   }
}

BOOST_AUTO_TEST_CASE( emplace_reset_test )
{
   X::reset_counters();
   {
      ns::optional<X> o;

      BOOST_TEST( (bool)o == false );
      BOOST_TEST( X::sum_counters() == 0 );

      o.reset();

      BOOST_TEST( (bool)o == false );
      BOOST_TEST( X::sum_counters() == 0 );
   }
   BOOST_TEST( X::sum_counters() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o;

      int i = 12;
      o.emplace(i);

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::converting_lvalue_int_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( (*o).value() == 12 );
      BOOST_TEST( o->value() == 12 );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );

   X::reset_counters();
   {
      ns::optional<X> o;

      o.emplace(34);

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::converting_rvalue_int_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( (*o).value() == 34 );
      BOOST_TEST( o->value() == 34 );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );

   X::reset_counters();
   {
      ns::optional<X> o;

      o.emplace(55.8);

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::converting_double_constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
      BOOST_TEST( X::sum_counters() == 3 );

      BOOST_TEST( (bool)o == true );
      BOOST_TEST( (*o).value() == 56 );
      BOOST_TEST( o->value() == 56 );
   }
   BOOST_TEST( X::destructed() == 1 );
   BOOST_TEST( X::alive() == 0 );
   BOOST_TEST( X::sum_counters() == 3 );
}

BOOST_AUTO_TEST_CASE( copy_constructor_test )
{
   X::reset_counters();
   {
      ns::optional<X> o1;

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( X::sum_counters() == 0 );

      ns::optional<X> o2(o1);

      BOOST_TEST( (bool)o2 == false );
      BOOST_TEST( X::sum_counters() == 0 );
   }
   BOOST_TEST( X::constructed() == 0 );
   BOOST_TEST( X::destructed() == 0 );
   BOOST_TEST( X::sum_counters() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 78);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( o1->value() == 78 );
      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );

      ns::optional<X> o2(o1);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 78 );
      BOOST_TEST( o2->value() == 78 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::copy_constructed() == 1 );
      BOOST_TEST( X::alive() == 2 );
   }
   BOOST_TEST( X::destructed() == 2 );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE( move_constructor_test )
{
   X::reset_counters();
   {
      ns::optional<X> o1;

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( X::sum_counters() == 0 );

      ns::optional<X> o2(std::move(o1));

      BOOST_TEST( (bool)o2 == false );
      BOOST_TEST( X::sum_counters() == 0 );
   }
   BOOST_TEST( X::constructed() == 0 );
   BOOST_TEST( X::destructed() == 0 );
   BOOST_TEST( X::sum_counters() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 90);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( o1->value() == 90 );
      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );

      ns::optional<X> o2(std::move(o1));

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->empty() == true );
      BOOST_TEST( o2->value() == 90 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::move_constructed() == 1 );
      BOOST_TEST( X::alive() == 2 );
   }
   BOOST_TEST( X::destructed() == 2 );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE( copy_assignment_test )
{
   X::reset_counters();
   {
      ns::optional<X> o1;
      ns::optional<X> o2;

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::sum_counters() == 0 );

      o1 = o2;

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::sum_counters() == 0 );
   }
   BOOST_TEST( X::sum_counters() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o1;
      ns::optional<X> o2(ns::in_place_t{}, 1234);

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o2->value() == 1234 );

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );

      o1 = o2;

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 1234 );
      BOOST_TEST( o2->value() == 1234 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::copy_constructed() == 1 );
      BOOST_TEST( X::alive() == 2 );
   }
   BOOST_TEST( X::destructed() == 2 );
   BOOST_TEST( X::alive() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 5678);
      ns::optional<X> o2;

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == false );
      BOOST_TEST( o1->value() == 5678 );

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );

      o1 = o2;

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::destructed() == 1 );
      BOOST_TEST( X::alive() == 0 );
   }

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 234);
      ns::optional<X> o2(ns::in_place_t{}, 678);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 234 );
      BOOST_TEST( o2->value() == 678 );

      o1 = o2;

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 678 );
      BOOST_TEST( o2->value() == 678 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::copy_assigned() == 1 );
   }
}

BOOST_AUTO_TEST_CASE( move_assignment_test )
{
   X::reset_counters();
   {
      ns::optional<X> o1;
      ns::optional<X> o2;

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::sum_counters() == 0 );

      o1 = std::move(o2);

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::sum_counters() == 0 );
   }
   BOOST_TEST( X::sum_counters() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o1;
      ns::optional<X> o2(ns::in_place_t{}, 1234);

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o2->value() == 1234 );

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );

      o1 = std::move(o2);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 1234 );
      BOOST_TEST( o2->empty() == true );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::move_constructed() == 1 );
      BOOST_TEST( X::alive() == 2 );
   }
   BOOST_TEST( X::destructed() == 2 );
   BOOST_TEST( X::alive() == 0 );

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 5678);
      ns::optional<X> o2;

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == false );
      BOOST_TEST( o1->value() == 5678 );

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::alive() == 1 );

      o1 = std::move(o2);

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::constructed() == 1 );
      BOOST_TEST( X::destructed() == 1 );
      BOOST_TEST( X::alive() == 0 );
   }

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 234);
      ns::optional<X> o2(ns::in_place_t{}, 678);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 234 );
      BOOST_TEST( o2->value() == 678 );

      o1 = std::move(o2);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 678 );
      BOOST_TEST( o2->empty() == true );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::move_assigned() == 1 );
   }
}

BOOST_AUTO_TEST_CASE( swap_test )
{
   X::reset_counters();
   {
      ns::optional<X> o1;
      ns::optional<X> o2;

      swap(o1, o2);

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == false );

      BOOST_TEST( X::sum_counters() == 0 );
   }

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 321);
      ns::optional<X> o2;

      swap(o1, o2);

      BOOST_TEST( (bool)o1 == false );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o2->value() == 321 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::move_constructed() == 1 );
      BOOST_TEST( X::destructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
   }
   BOOST_TEST( X::destructed() == 2 );

   X::reset_counters();
   {
      ns::optional<X> o1;
      ns::optional<X> o2(ns::in_place_t{}, 654);

      swap(o1, o2);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == false );
      BOOST_TEST( o1->value() == 654 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::move_constructed() == 1 );
      BOOST_TEST( X::destructed() == 1 );
      BOOST_TEST( X::alive() == 1 );
   }
   BOOST_TEST( X::destructed() == 2 );

   X::reset_counters();
   {
      ns::optional<X> o1(ns::in_place_t{}, 76);
      ns::optional<X> o2(ns::in_place_t{}, 98);

      ns::swap(o1, o2);

      BOOST_TEST( (bool)o1 == true );
      BOOST_TEST( (bool)o2 == true );
      BOOST_TEST( o1->value() == 98 );
      BOOST_TEST( o2->value() == 76 );

      BOOST_TEST( X::constructed() == 2 );
      BOOST_TEST( X::move_constructed() == 0 );
      BOOST_TEST( X::copy_constructed() == 0 );
      BOOST_TEST( X::swapped() == 1 );
      BOOST_TEST( X::destructed() == 0 );
      BOOST_TEST( X::alive() == 2 );
   }
   BOOST_TEST( X::destructed() == 2 );
   BOOST_TEST( X::alive() == 0 );
}
