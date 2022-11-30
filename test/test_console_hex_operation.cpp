#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::DisplayMode;
using rpn_engine::Op;

TEST(ConsoleHexOperation, SignedMul)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f); // -1
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFF"); // -1
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::num_2);
    c.Input(Op::bit_mul);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFE"); // -2
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(ConsoleHexOperation, SignedMul2)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_e); // -2
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFE"); // -1
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f); // -1
    c.Input(Op::bit_mul);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000002"); // 2
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(ConsoleHexOperation, SignedMulOverflow)
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
    c.Input(Op::num_0);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 80000000"); // INT32_MIN
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::num_2);
    c.Input(Op::bit_mul);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 80000000"); // Must keep sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(ConsoleHexOperation, SignedDiv)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::num_e); // -2
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFE"); // -2
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::num_2);
    c.Input(Op::bit_div);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFFFF"); // -1
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}
