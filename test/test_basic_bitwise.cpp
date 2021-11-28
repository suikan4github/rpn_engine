// Test cases for the basic bitwise operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>

typedef rpn_engine::StackStrategy<double> DoubleStack;

namespace rpn_engine
{

    TEST(BasicBitwiseTest, To32bitValue)
    {
        DoubleStack *s;
        s = new DoubleStack(4);

        // truncation from integer is "round to zero" according to the C++ standard.
        EXPECT_EQ(s->To32bitValue(1.414), 1);   // truncation test.
        EXPECT_EQ(s->To32bitValue(1.8), 1);     // truncation test.
        EXPECT_EQ(s->To32bitValue(-1.414), -1); // truncation test.
        EXPECT_EQ(s->To32bitValue(-1.8), -1);   // truncation test.

        // Large number extraction.
        EXPECT_GT((1LL << 40), INT32_MAX);                       // compiler check.
        EXPECT_EQ(s->To32bitValue(INT32_MAX - 1.0), 0x7ffffffe); // extracted data must be INT32_MAX-1.
        EXPECT_EQ(s->To32bitValue(INT32_MAX + 1.0), 0x80000000); // extracted data must be overflown
        EXPECT_EQ(s->To32bitValue(INT32_MIN + 1.0), 0x80000001); // extracted data must be zero.
        EXPECT_EQ(s->To32bitValue(INT32_MIN - 1.0), 0x7fffffff); // extracted data must be INT32_MIN+1.
        delete s;
    }

    TEST(BasicBitwiseTest, ToElementValue)
    {
        DoubleStack *s;
        s = new DoubleStack(4);

        EXPECT_EQ(s->ToElementValue(1), 1.0);
        EXPECT_EQ(s->ToElementValue(-1), -1.0);
        EXPECT_EQ(s->ToElementValue(0x7FFFFFFF), INT32_MAX);
        EXPECT_EQ(s->ToElementValue(0x80000000), INT32_MIN);
        delete s;
    }

}

TEST(BasicBitwiseTest, BitAdd)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3);
    s->Push(7);
    s->BitAdd();
    EXPECT_EQ(s->Get(0), 10);

    s->Push(3.14);
    s->Push(7.1);
    s->BitAdd();
    EXPECT_EQ(s->Get(0), 10);

    s->LastX();
    EXPECT_EQ(s->Get(0), 7.1);
    delete s;
}

TEST(BasicBitwiseTest, BitSubtract)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3);
    s->Push(7);
    s->BitSubtract();
    EXPECT_EQ(s->Get(0), -4);

    // truncation test
    s->Push(3.14);
    s->Push(7.1);
    s->BitSubtract();
    EXPECT_EQ(s->Get(0), -4);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 7.1);
    delete s;
}

TEST(BasicBitwiseTest, BitMultiply)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.14);
    s->Push(3);
    s->Push(7);
    s->BitMultiply();
    EXPECT_EQ(s->Get(0), 21);
    EXPECT_EQ(s->Get(1), 3.14);

    s->Push(-3);
    s->Push(7);
    s->BitMultiply();
    EXPECT_EQ(s->Get(0), -21);

    s->Push(3);
    s->Push(-7);
    s->BitMultiply();
    EXPECT_EQ(s->Get(0), -21);

    s->Push(-3);
    s->Push(-7);
    s->BitMultiply();
    EXPECT_EQ(s->Get(0), 21);

    // truncation test
    s->Push(3.14);
    s->Push(7.1);
    s->BitMultiply();
    EXPECT_EQ(s->Get(0), 21);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 7.1);
    delete s;
}

TEST(BasicBitwiseTest, BitDivide)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(4.2);
    s->Push(7.1);
    s->Push(3.1);
    s->BitDivide();
    EXPECT_EQ(s->Get(0), 2);
    EXPECT_EQ(s->Get(1), 4.2);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 3.1);
    delete s;
}

TEST(BasicBitwiseTest, BitNagate)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push(3.1);
    s->BitNagate();
    EXPECT_EQ(s->Get(0), -3);
    EXPECT_EQ(s->Get(1), 7.1);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 3.1);
    delete s;
}

TEST(BasicBitwiseTest, BitOr)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push(0x55AA);
    s->Push(0xFF00);
    s->BitOr();
    EXPECT_EQ(s->Get(0), 0xFFAA);
    EXPECT_EQ(s->Get(1), 7.1);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 0xFF00);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->BitOr();
    EXPECT_EQ(s->Get(0), 13); // 0x0D
    delete s;
}

TEST(BasicBitwiseTest, BitExor)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push(0x55AA);
    s->Push(0xFF00);
    s->BitExor();
    EXPECT_EQ(s->Get(0), 0xAAAA);
    EXPECT_EQ(s->Get(1), 7.1);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 0xFF00);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->BitExor();
    EXPECT_EQ(s->Get(0), 9); // 0x09
    delete s;
}

TEST(BasicBitwiseTest, BitAnd)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push(0x55AA);
    s->Push(0xFF00);
    s->BitAnd();
    EXPECT_EQ(s->Get(0), 0x5500);
    EXPECT_EQ(s->Get(1), 7.1);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 0xFF00);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->BitAnd();
    EXPECT_EQ(s->Get(0), 4); // 0x04
    delete s;
}

TEST(BasicBitwiseTest, LogicalShiftRight)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push(INT32_MAX);
    s->Push(1);
    s->LogicalShiftRight();
    EXPECT_EQ(s->Get(0), 0x3FFFFFFF);
    EXPECT_EQ(s->Get(1), 7.1);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 1);

    // zero padding at MSB check
    s->Push(INT32_MIN);
    s->Push(1);
    s->LogicalShiftRight();
    EXPECT_EQ(s->Get(0), 0x40000000);

    // truncation checkds
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->BitAnd();
    EXPECT_EQ(s->Get(0), 4); // 0x04
    delete s;
}

TEST(BasicBitwiseTest, LogicalShiftLeft)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push(0x7FFFFFFF);
    s->Push(1);
    s->LogicalShiftLeft();
    EXPECT_EQ(s->Get(0), (int32_t)0xFFFFFFFE);
    EXPECT_EQ(s->Get(1), 7.1);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), 1);

    // zero padding at MSB check
    s->Push(0xFFFFFFFF);
    s->Push(1);
    s->LogicalShiftLeft();
    EXPECT_EQ(s->Get(0), (int32_t)0xFFFFFFFE);

    // truncation checkds
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->LogicalShiftLeft();
    EXPECT_EQ(s->Get(0), 0x5000); //
    delete s;
}

TEST(BasicBitwiseTest, BitNot)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(7.1);
    s->Push((int32_t)0x5555AAAA);
    s->BitNot();
    EXPECT_EQ(s->Get(0), (int32_t)0xAAAA5555);
    EXPECT_EQ(s->Get(1), 7.1);
    s->BitNot();
    EXPECT_EQ(s->Get(0), (int32_t)0x5555AAAA);

    // last x test
    s->LastX();
    EXPECT_EQ(s->Get(0), (int32_t)0xAAAA5555);

    // truncation checkds
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->BitNot();
    EXPECT_EQ(s->Get(0), (int32_t)0xFFFFFFF3); //
    delete s;
}
