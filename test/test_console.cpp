#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::DisplayMode;
using rpn_engine::Op;

TEST(Console, IsFuncKeyPressed)
{
    rpn_engine::Console c;

    EXPECT_FALSE(c.GetIsFuncKeyPressed());
    c.Input(Op::func);
    EXPECT_TRUE(c.GetIsFuncKeyPressed());
    c.Input(Op::func);
    EXPECT_FALSE(c.GetIsFuncKeyPressed());
}

TEST(Console, Inputmode)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::pi);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 31415927");
    EXPECT_EQ(decimal_point, 7);

    // Scientific mode
    c.Input(Op::change_display);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+31415+00");
    EXPECT_EQ(decimal_point, 7);

    // Engineering mode
    c.Input(Op::change_display);
    c.Input(Op::square);
    c.Input(Op::square);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+97409+00");
    EXPECT_EQ(decimal_point, 6);
}

TEST(Console, HexMode)
{
    rpn_engine::Console c;

    EXPECT_FALSE(c.GetIsHexMode());

    c.Input(Op::dec);
    EXPECT_FALSE(c.GetIsHexMode());

    c.Input(Op::hex);
    EXPECT_TRUE(c.GetIsHexMode());

    c.Input(Op::hex);
    EXPECT_TRUE(c.GetIsHexMode());

    c.Input(Op::dec);
    EXPECT_FALSE(c.GetIsHexMode());

    c.Input(Op::hex);
    EXPECT_TRUE(c.GetIsHexMode());

    c.Input(Op::dec);
    EXPECT_FALSE(c.GetIsHexMode());
}

TEST(Console, HexModeRenering)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_0);

    c.Input(Op::hex);
    EXPECT_TRUE(c.GetIsHexMode());
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0000000A");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::dec);
    EXPECT_FALSE(c.GetIsHexMode());
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 10000000");
    EXPECT_EQ(decimal_point, 6);
}

TEST(Console, InitialString)
{
    rpn_engine::Console c(" HELLO   ");
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " HELLO   ");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_1);
    c.Input(Op::num_0);

    c.Input(Op::hex);
    EXPECT_TRUE(c.GetIsHexMode());
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0000000A");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(Console, PiUndo)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_2);
    c.Input(Op::pi);
    c.Input(Op::undo);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 20000000");
    EXPECT_EQ(decimal_point, 7);
}

TEST(Console, StoRcl)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_2);
    c.Input(Op::rcl); // must be zero at first
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000");
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::num_2);
    c.Input(Op::sto); // store 2.0
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 20000000");
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::num_3);
    c.Input(Op::rcl); // must be 2.0
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 20000000");
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 30000000");
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rcl);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 20000000");
    EXPECT_EQ(decimal_point, 7);
}
