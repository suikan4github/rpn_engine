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
    }

    TEST(BasicBitwiseTest, ToElementValue)
    {
        DoubleStack *s;
        s = new DoubleStack(4);

        EXPECT_EQ(s->ToElementValue(1), 1.0);
        EXPECT_EQ(s->ToElementValue(-1), -1.0);
        EXPECT_EQ(s->ToElementValue(0x7FFFFFFF), INT32_MAX);
        EXPECT_EQ(s->ToElementValue(0x80000000), INT32_MIN);
    }

}
