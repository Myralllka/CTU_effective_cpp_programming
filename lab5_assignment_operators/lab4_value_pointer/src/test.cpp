#define BOOST_TEST_MODULE value_ptr_test

#include <boost/test/included/unit_test.hpp>

#include "ValuePtr.h"

class X {
    int i_;  // -1 indicates empty content

public:
    X() : i_(-1) {
        constructed++;
        default_constructed++;
        alive++;
    }

    explicit X(int i) : i_(i) {
        constructed++;
        converting_constructed++;
        alive++;
    }

    X(const X &other) : i_(other.i_) {
        constructed++;
        copy_constructed++;
        alive++;
    }

    X(X &&other)  noexcept : i_(other.i_) {
        other.i_ = -1;
        constructed++;
        move_constructed++;
        alive++;
    }

    ~X() {
        destructed++;
        alive--;
    }

    X &operator=(const X &) = delete;

    X &operator=(X &&) = delete;

    [[nodiscard]] int value() const { return i_; }

    // for testing purposes:
    static long constructed, default_constructed, converting_constructed,
            copy_constructed, move_constructed, alive, destructed;
};

long X::constructed = 0, X::default_constructed = 0,
        X::converting_constructed = 0, X::copy_constructed = 0,
        X::move_constructed = 0, X::alive = 0, X::destructed = 0;

BOOST_AUTO_TEST_CASE(ValuePtrTest)
{
    {
        ValuePtr<X> vp;

        BOOST_TEST(X::constructed == 0);
        BOOST_TEST(X::alive == 0);
    }

    BOOST_TEST(X::destructed == 0);

    {
        auto x = new X;
        ValuePtr<X> vp{x};

        BOOST_TEST(X::constructed == 1);
        BOOST_TEST(X::converting_constructed == 0);
        BOOST_TEST(X::copy_constructed == 0);
        BOOST_TEST(X::default_constructed == 1);
        BOOST_TEST(X::alive == 1);

        BOOST_TEST(vp->value() == -1);
    }

    BOOST_TEST(X::alive == 0);
    BOOST_TEST(X::destructed == 1);

    {
        ValuePtr<X> vp{new X{1}};

        BOOST_TEST(X::constructed == 2);
        BOOST_TEST(X::converting_constructed == 1);
        BOOST_TEST(X::alive == 1);

        BOOST_TEST((*vp).value() == 1);
        BOOST_TEST(vp->value() == 1);
    }

    BOOST_TEST(X::alive == 0);
    BOOST_TEST(X::destructed == 2);

    {
        ValuePtr<X> vp{new X{2}};
        ValuePtr<X> vp_copy{vp};

        BOOST_TEST(X::constructed == 4);
        BOOST_TEST(X::converting_constructed == 2);
        BOOST_TEST(X::copy_constructed == 1);
        BOOST_TEST(X::alive == 2);

        BOOST_TEST(vp->value() == 2);
        BOOST_TEST(vp_copy->value() == 2);
    }

    BOOST_TEST(X::alive == 0);
    BOOST_TEST(X::destructed == 4);

    {
        ValuePtr<X> vp{new X{3}};
        ValuePtr<X> vp_move{std::move(vp)};

        BOOST_TEST(X::constructed == 6);
        BOOST_TEST(X::converting_constructed == 3);
        BOOST_TEST(X::move_constructed == 1);
        BOOST_TEST(X::alive == 2);

        BOOST_TEST(vp->value() == -1);
        BOOST_TEST(vp_move->value() == 3);
    }

    BOOST_TEST(X::alive == 0);
    BOOST_TEST(X::destructed == 6);

    {
        ValuePtr<X> vp;
        ValuePtr<X> vp_copy{vp};

        BOOST_TEST(X::constructed == 6);
        BOOST_TEST(X::copy_constructed == 1);
        BOOST_TEST(X::alive == 0);
    }

    BOOST_TEST(X::destructed == 6);

    {
        ValuePtr<X> vp;
        ValuePtr<X> vp_move{std::move(vp)};

        BOOST_TEST(X::constructed == 6);
        BOOST_TEST(X::move_constructed == 1);
        BOOST_TEST(X::alive == 0);
    }

    BOOST_TEST(X::destructed == 6);
}
