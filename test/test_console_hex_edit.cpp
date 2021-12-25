#include "gtest/gtest.h"
#include "console.hpp"
#include <stdexcept>

using rpn_engine::DisplayMode;
using rpn_engine::Op;

// basic hex edit
TEST(ConsoleEditing, HexEdit)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);

    c.Input(Op::num_b);
    c.Input(Op::num_e);
    c.Input(Op::num_e);
    c.Input(Op::num_f);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " BEEF    ");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0000BEEF");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// basic hex display
TEST(ConsoleEditing, HexDisplay)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12000000");
    EXPECT_EQ(decimal_point, 6);

    c.Input(Op::hex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0000000C");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// basic hex to int
TEST(ConsoleEditing, HexToInt)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_1);
    c.Input(Op::num_c);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0000001C");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::dec);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 28000000");
    EXPECT_EQ(decimal_point, 6);
}

// minus basic hex display
TEST(ConsoleEditing, HexMinusDisplay)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::chs);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-10000000");
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::hex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFF");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Hex with eex
TEST(ConsoleEditing, HexEEX)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_1);
    c.Input(Op::eex);
    c.Input(Op::num_1);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000011"); // eex is ignored
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Hex with period
TEST(ConsoleEditing, HexPeriod)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_1);
    c.Input(Op::period);
    c.Input(Op::num_1);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000011"); // chs is ignored
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Hex with period
TEST(ConsoleEditing, HexChs)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_1);
    c.Input(Op::chs);
    c.Input(Op::num_1);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000011"); // chs is ignored
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Hex with neg
TEST(ConsoleEditing, HexNeg)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_1);
    c.Input(Op::enter);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000001"); //
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFF"); //
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}
