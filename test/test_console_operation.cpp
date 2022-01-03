#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::DisplayMode;
using rpn_engine::Op;

TEST(Console, AddOp)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_2);
    c.Input(Op::enter);
    c.Input(Op::num_3);
    c.Input(Op::add);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 50000000");
    EXPECT_EQ(decimal_point, 7);
}

TEST(Console, DivOp)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_2);
    c.Input(Op::enter);
    c.Input(Op::num_3);
    c.Input(Op::div);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 06666667");
    EXPECT_EQ(decimal_point, 7);
}

TEST(Console, CosOp)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_3);
    c.Input(Op::period);
    c.Input(Op::num_1);
    c.Input(Op::num_4);
    c.Input(Op::num_1);
    c.Input(Op::num_5);
    c.Input(Op::num_9);
    c.Input(Op::num_2);
    c.Input(Op::num_7);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 31415927");
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_2);
    c.Input(Op::div);
    c.Input(Op::cos);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-23205-08");
    EXPECT_EQ(decimal_point, 7);
}

TEST(Console, Inf)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_3);
    c.Input(Op::enter);
    c.Input(Op::num_0);
    c.Input(Op::inv);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "      INF");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(Console, MinusInf)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_3);
    c.Input(Op::chs);
    c.Input(Op::enter);
    c.Input(Op::num_0);
    c.Input(Op::inv);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "      INF");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(Console, NaN)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_3);
    c.Input(Op::chs);
    c.Input(Op::enter);
    c.Input(Op::num_0);
    c.Input(Op::inv);
    c.Input(Op::enter);
    c.Input(Op::sub);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "      NaN");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}
