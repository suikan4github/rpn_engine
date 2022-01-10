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

    c.Input(Op::num_0);
    c.Input(Op::log);
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

// If either real or imag is NaN, it should be NaN
TEST(Console, NaN2)
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
    EXPECT_STREQ(display_text, "      NaN");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// If either real or imag is NaN, it should be NaN
TEST(Console, NaN3)
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
    EXPECT_STREQ(display_text, "      NaN");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Check whether overflown is trapped.
TEST(Console, BitMulOverflow)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_8);
    c.Input(Op::num_0);
    c.Input(Op::num_0);
    c.Input(Op::num_0);
    c.Input(Op::num_0);
    c.Input(Op::num_0);
    c.Input(Op::num_0);
    c.Input(Op::num_0); // INT32_MIN
    c.Input(Op::enter);
    c.Input(Op::num_2);
    c.Input(Op::bit_mul); // cause overflow
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 80000000"); // must be saturated
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_7);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f); // INT32_MAX
    c.Input(Op::enter);
    c.Input(Op::num_2);
    c.Input(Op::bit_mul); // cause overflow
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 7FFFFFFF"); // must be saturated
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Display 99999999.5. This must be showed as scientific mode
TEST(Console, ScientifcDisplayBOverflow)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::num_9); // mux fixed mode number
    c.Input(Op::enter);
    c.Input(Op::num_0);
    c.Input(Op::period);
    c.Input(Op::num_5);
    c.Input(Op::add); // cause overflow from the fixed mode display because of rounding
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+10000+08"); // must be saturated
    EXPECT_EQ(decimal_point, 7);
}

// display_chante test
TEST(Console, display_change)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::period);
    c.Input(Op::num_4);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12340000"); // must be fixed mode
    EXPECT_EQ(decimal_point, 5);

    c.Input(Op::change_display);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+12340+02"); // must be scientific mode
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::change_display);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+12340+00"); // must be engineering mode
    EXPECT_EQ(decimal_point, 5);

    c.Input(Op::change_display);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12340000"); // must be fixed mode
    EXPECT_EQ(decimal_point, 5);
}

// Input period during floating input
TEST(Console, period_float)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::period);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.Input(Op::num_5);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  05"); // must be float
    EXPECT_EQ(decimal_point, 5);

    c.Input(Op::period);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  05"); // must not be changed
    EXPECT_EQ(decimal_point, 5);
}

// Input period during floating input
TEST(Console, period_double)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::period);
    c.Input(Op::num_4);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234    "); // must be with one period
    EXPECT_EQ(decimal_point, 5);

    c.Input(Op::period);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234    "); // must not be changed
    EXPECT_EQ(decimal_point, 5);
}

TEST(Console, display_too_large)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::eex);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+99999+99"); //
    EXPECT_EQ(decimal_point, 7);
}

TEST(Console, display_too_negative)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::chs);
    c.Input(Op::eex);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-99999+99"); //
    EXPECT_EQ(decimal_point, 7);
}

TEST(Console, display_too_small)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::chs);
    c.Input(Op::eex);
    c.Input(Op::num_9);
    c.Input(Op::num_9);
    c.Input(Op::inv);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); //
    EXPECT_EQ(decimal_point, 7);
}
