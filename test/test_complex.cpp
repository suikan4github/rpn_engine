// Test cases for the basic math operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>
#include <math.h>
#include <complex>

typedef rpn_engine::StackStrategy<std::complex<double>> DoubleComplexStack;

TEST(DoubleComplexTest, Add)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(5.0, 2.0));
    s->Push(std::complex<double>(6.0, 3.0));
    s->Operation(rpn_engine::Op::add);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 11.0); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 5.0);  // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Mul)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(5.0, 2.0));
    s->Push(std::complex<double>(6.0, 3.0));
    s->Operation(rpn_engine::Op::mul);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 24); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 27); // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Sqrt)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(-1);
    s->Operation(rpn_engine::Op::sqrt);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 1); // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Exp)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0.0, 1.0));
    s->Operation(rpn_engine::Op::pi);
    s->Operation(rpn_engine::Op::mul);
    s->Push(4);
    s->Operation(rpn_engine::Op::div);
    s->Operation(rpn_engine::Op::exp);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), ::cos(rpn_engine::pi / 4)); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), ::sin(rpn_engine::pi / 4)); // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Log)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0, 1));
    s->Operation(rpn_engine::Op::log);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0);      // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), rpn_engine::pi/2); // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Power10)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0, 1));
    s->Operation(rpn_engine::Op::power10);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), -0.6682015101903129); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 0.7439803369574931);  // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Power)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(rpn_engine::pi);
    s->Push(std::complex<double>(0, 1));
    s->Operation(rpn_engine::Op::power);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0.4132921161015943); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 0.9105984992126147); // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Sin)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0, 1));
    s->Operation(rpn_engine::Op::sin);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0);                    // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 1.175201193643801456); // check imaginary part of top.
    delete s;
}

TEST(DoubleComplexTest, Complex)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Operation(rpn_engine::Op::complex);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 3); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 4); // check imaginary part of top.

    s->Undo();
    x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 4); // Undo check
}

TEST(DoubleComplexTest, DeComplex)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(0);
    s->Push(std::complex<double>(3, 4)); // 3+4i
    s->Operation(rpn_engine::Op::decomplex);

    auto x = s->Get(0);
    auto y = s->Get(1);
    EXPECT_DOUBLE_EQ(x.real(), 4); // check imaginary part.
    EXPECT_DOUBLE_EQ(y.real(), 3); // check real part .

    s->Undo();
    x = s->Get(0);
    y = s->Get(1);
    EXPECT_DOUBLE_EQ(x.real(), 3); // Undo buffered
    EXPECT_DOUBLE_EQ(x.imag(), 4); // Undo buffered
    EXPECT_DOUBLE_EQ(y.real(), 0); // Undo buffered
    EXPECT_DOUBLE_EQ(y.imag(), 0); // Undo buffered
    delete s;
}

TEST(DoubleComplexTest, Conjugate)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3, 4)); // 3+4i
    s->Operation(rpn_engine::Op::conjugate);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 3);  // check real part.
    EXPECT_DOUBLE_EQ(x.imag(), -4); // check imaginary part.

    s->Undo();
    x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 3); // check real part.
    EXPECT_DOUBLE_EQ(x.imag(), 4); // check imaginary part.
    delete s;
}

TEST(DoubleComplexTest, ToPorlar)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(1, 1)); // 1+i
    s->Operation(rpn_engine::Op::to_polar);

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), sqrt((double)2.0)); // Abs of 1+i is 1.41421356...
    EXPECT_DOUBLE_EQ(x.imag(), rpn_engine::pi/4);            // Angular of 1+i is pi/4
    delete s;
}

TEST(DoubleComplexTest, ToCartesian)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(sqrt((double)2.0), rpn_engine::pi/4)); // 1.414 + i(3.1415/4)
    s->Operation(rpn_engine::Op::to_cartesian);

    // must be converted to 1+i;
    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 1.0); //
    EXPECT_DOUBLE_EQ(x.imag(), 1.0); //
    delete s;
}

TEST(DoubleComplexTest, SwapReIm)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(std::complex<double>(1, 2)); // 1+2i
    s->Operation(rpn_engine::Op::swap_re_im);

    // must be converted to 2+i;
    EXPECT_DOUBLE_EQ(s->Get(0).real(), 2.0); //
    EXPECT_DOUBLE_EQ(s->Get(0).imag(), 1.0); //
    EXPECT_DOUBLE_EQ(s->Get(1).real(), 4);   //
    EXPECT_DOUBLE_EQ(s->Get(2).real(), 3);   //
    delete s;
}
