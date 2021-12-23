#include "gtest/gtest.h"
#include "console.hpp"
#include <stdexcept>

using rpn_engine::DisplayMode;
using rpn_engine::Op;

TEST(ConsoleEditing, Initial)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000");
    EXPECT_EQ(decimal_point, 7);
}

TEST(ConsoleEditing, SetNum_1)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_3);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 3       ");
    EXPECT_EQ(decimal_point, -1);
}

TEST(ConsoleEditing, SetNum_2)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_3);
    c.Input(Op::num_1);
    c.Input(Op::num_4);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 314     ");
    EXPECT_EQ(decimal_point, -1);
}

TEST(ConsoleEditing, SetNum_3)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5);
    c.Input(Op::num_6);
    c.Input(Op::num_7);
    c.Input(Op::num_8);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678");
    EXPECT_EQ(decimal_point, -1);
    // test if try to exceed 8 digits
    c.Input(Op::num_9);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678"); // must not change
    EXPECT_EQ(decimal_point, -1);
}
