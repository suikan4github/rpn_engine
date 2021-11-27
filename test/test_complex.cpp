// Test cases for the basic math operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
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
    s->Add();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 11.0); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 5.0);  // check imaginaly part of top.
}

TEST(DoubleComplexTest, Mul)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(5.0, 2.0));
    s->Push(std::complex<double>(6.0, 3.0));
    s->Multiply();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 24); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 27); // check imaginaly part of top.
}

TEST(DoubleComplexTest, Sqrt)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(-1);
    s->Sqrt();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 1); // check imaginaly part of top.
}

TEST(DoubleComplexTest, Exp)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0.0, 1.0));
    s->Pi();
    s->Multiply();
    s->Push(4);
    s->Divide();
    s->Exp();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), ::cos(M_PI / 4)); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), ::sin(M_PI / 4)); // check imaginaly part of top.
}

TEST(DoubleComplexTest, Log)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0, 1));
    s->Log();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0);      // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), M_PI_2); // check imaginaly part of top.
}

TEST(DoubleComplexTest, Power10)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0, 1));
    s->Power10();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), -0.6682015101903129); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 0.7439803369574931);  // check imaginaly part of top.
}

TEST(DoubleComplexTest, Power)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(M_PI);
    s->Push(std::complex<double>(0, 1));
    s->Power();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0.4132921161015943); // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 0.9105984992126147); // check imaginaly part of top.
}

TEST(DoubleComplexTest, Sin)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(std::complex<double>(0, 1));
    s->Sin();

    auto x = s->Get(0);
    EXPECT_DOUBLE_EQ(x.real(), 0);                    // check real part of top.
    EXPECT_DOUBLE_EQ(x.imag(), 1.175201193643801456); // check imaginaly part of top.
}
