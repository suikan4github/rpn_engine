// Test cases for the basic math operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>
#include <math.h>
#include <complex>

typedef rpn_engine::StackStrategy<std::complex<double>> DoubleComplexStack;

TEST(ComplexBitwiseTest, BitAdd)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));
    s->Push(std::complex<double>(2.1, 7.3));

    s->Operation(rpn_engine::Op::bitadd);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 5); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitSubtract)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));
    s->Push(std::complex<double>(2.1, 7.3));

    s->Operation(rpn_engine::Op::bitsub);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 1); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitMultiply)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));
    s->Push(std::complex<double>(2.1, 7.3));

    s->Operation(rpn_engine::Op::bitmul);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 6); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitDivide)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));
    s->Push(std::complex<double>(2.1, 7.3));

    s->Operation(rpn_engine::Op::bitdiv);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 1); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitNagate)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));
    s->Push(std::complex<double>(2.1, 7.3));

    s->Operation(rpn_engine::Op::bit_neg);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), -2); // real part must be integer
    EXPECT_EQ(c.imag(), 0);  // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitOr)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));   // 0x3
    s->Push(std::complex<double>(6.1, 7.3)); // 0x6

    s->Operation(rpn_engine::Op::bit_or);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 7); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitExor)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));   // 0x3
    s->Push(std::complex<double>(6.1, 7.3)); // 0x6

    s->Operation(rpn_engine::Op::bit_xor);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 5); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitAnd)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(3.4, 5));   // 0x3
    s->Push(std::complex<double>(6.1, 7.3)); // 0x6

    s->Operation(rpn_engine::Op::bit_and);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 2); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, LogicalShiftRight)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(12.4, 5));  // 0x3
    s->Push(std::complex<double>(2.1, 7.3)); // 0x6

    s->Operation(rpn_engine::Op::logical_shift_right);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 3); // real part must be integer
    EXPECT_EQ(c.imag(), 0); // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, LogicalShiftLeft)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(12.4, 5));  // 0x3
    s->Push(std::complex<double>(2.1, 7.3)); // 0x6

    s->Operation(rpn_engine::Op::logical_shift_left);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), 48); // real part must be integer
    EXPECT_EQ(c.imag(), 0);  // imaginary part must be 0
    delete s;
}

TEST(ComplexBitwiseTest, BitNot)
{
    DoubleComplexStack *s;
    s = new DoubleComplexStack(4);

    s->Push(std::complex<double>(12.4, 5));  // 0x3
    s->Push(std::complex<double>(2.1, 7.3)); // 0x6

    s->Operation(rpn_engine::Op::bit_not);
    auto c = s->Get(0);
    EXPECT_EQ(c.real(), (int32_t)0xFFFFFFFD); // real part must be integer
    EXPECT_EQ(c.imag(), 0);                   // imaginary part must be 0
    delete s;
}
