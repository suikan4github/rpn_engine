#include "gtest/gtest.h"
#include "rpnengine.hpp"
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
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
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
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
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
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    // test if try to exceed 8 digits
    c.Input(Op::num_9);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678"); // must not change
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(ConsoleEditing, SetEEX)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    // EEX without editing mode
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1     00"); // must be pi
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// floating input prevention
TEST(ConsoleEditing, SetNum_EEX2)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5); // 5digits without decimal point
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345   "); // must prevent floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// floating input less or equal 4 digits
TEST(ConsoleEditing, SetNum_EEX3)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  00"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// floating input 5digits with decimal point
TEST(ConsoleEditing, SetNum_EEX4)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5);
    c.Input(Op::period); // 5digits with decimal point
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345 00"); // must in floating input
    EXPECT_EQ(decimal_point, 3);
}

// decimal point during floating input
TEST(ConsoleEditing, SetNum_EEX5)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.Input(Op::period); // period during floating point input
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  00");               // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed); // must be without decimal point
}

// floating input less or equal 4 digits
TEST(ConsoleEditing, SetNum_EEX6)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  00"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_1);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  01"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_2);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  12"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_3);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  23"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Left most decimal point
TEST(ConsoleEditing, DecimalPointAtDigit7)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::period); // period during floating point input
    //    c.Input(Op::period); // period during floating point input
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0       "); // must in floating input
    EXPECT_EQ(decimal_point, 7);             // must be right most
}

// decimal point at next of left most
TEST(ConsoleEditing, DecimalPointAtDigit6)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::period); // period during floating point input
    //    c.Input(Op::period); // period during floating point input
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1       "); // must in floating input
    EXPECT_EQ(decimal_point, 7);             // must be right most

    c.Input(Op::num_2);
    //    c.Input(Op::period); // period during floating point input
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12      "); // must in floating input
    EXPECT_EQ(decimal_point, 7);             // must be right most

    c.Input(Op::period); // duplicated period
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12      "); // must in floating input
    EXPECT_EQ(decimal_point, 7);             // duplicated period must be ignored
}

// Right most decimal point
TEST(ConsoleEditing, DecimalPointAtDigit0)
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
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    // test to place decimal point
    c.Input(Op::period);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678"); // must not change
    EXPECT_EQ(decimal_point, 0);             // must zero
}

// Test del key in exponent
TEST(ConsoleEditing, DelFloat)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  00"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_1);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  01"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::num_2);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  12"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  01"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  00"); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234    "); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123     "); // must in floating input
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Test del key in fixed point
TEST(ConsoleEditing, DelFixed)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123     "); // must delete last digit
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1       "); // must delete last digit
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // must delete last digit
    EXPECT_EQ(decimal_point, 7);
}

// Test chs on fixed input
TEST(ConsoleEditing, ChsFixed)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234    "); //
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-1234    "); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234    "); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Test chs on floating input
TEST(ConsoleEditing, ChsFloat)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.Input(Op::num_5);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  05"); //
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234 -05"); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  05"); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Test chs and del on fixed input
TEST(ConsoleEditing, ChsDelFixed)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234    "); //
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-1234    "); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-123     "); // must hold sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-12      "); // must hold sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-1       "); // must hold sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // must 0
    EXPECT_EQ(decimal_point, 7);
}

// Test chs del on floating input
TEST(ConsoleEditing, ChsDelFloat)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.Input(Op::num_5);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  05"); //
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234 -05"); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234 -00"); // must hold sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1234  00"); // must change sign
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Test chs as operation
TEST(ConsoleEditing, ChsOp)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12300000"); //
    EXPECT_EQ(decimal_point, 5);

    c.Input(Op::chs);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "-12300000"); // must negate
    EXPECT_EQ(decimal_point, 5);
}

// Test various input
TEST(ConsoleEditing, NumAndEnter1)
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
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    // test to place decimal point
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678"); // must not change
    EXPECT_EQ(decimal_point, 0);             // must zero
}

// Test various input
TEST(ConsoleEditing, NumAndEnter2)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::period);
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
    EXPECT_EQ(decimal_point, 7);

    // test to place decimal point
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678"); // must not change
    EXPECT_EQ(decimal_point, 7);             // 7
}

// Test various input
TEST(ConsoleEditing, NumAndEnter3)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::period);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::eex);
    c.Input(Op::num_8);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123   08");
    EXPECT_EQ(decimal_point, 7);

    // test to place decimal point
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+12300+08"); //
    EXPECT_EQ(decimal_point, 7);             // 7
}

// Test various input
TEST(ConsoleEditing, NumAndEnter4)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::eex);
    c.Input(Op::num_8);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123   08");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    // test to place decimal point
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+12300+10"); //
    EXPECT_EQ(decimal_point, 7);             // 7
}

// EEX when there is not zero
TEST(ConsoleEditing, EEXOnZero)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::clx);
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1     00");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(ConsoleEditing, EEXOnZero2)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::clx);
    c.Input(Op::num_0);
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1     00");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

TEST(ConsoleEditing, EEXOnZero3)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::clx);
    c.Input(Op::num_0);
    c.Input(Op::period);
    c.Input(Op::num_0);
    c.Input(Op::num_0);
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1     00");
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// duplicate eex
TEST(ConsoleEditing, DuplicateEex)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::clx);
    c.Input(Op::num_3);
    c.Input(Op::period);
    c.Input(Op::num_1);
    c.Input(Op::num_4);
    c.Input(Op::eex);
    c.Input(Op::num_4);
    c.Input(Op::eex);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 314   04");
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::eex);

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 314   04"); // 2nd eex has no effect
    EXPECT_EQ(decimal_point, 7);
}

// F key should not effect to editing
TEST(ConsoleEditing, FuncDuringEditing)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::func);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123     "); // func key doesn't change
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::num_4);
    EXPECT_FALSE(c.GetIsFuncKeyPressed()); // any input except f-key clear the state.
    c.Input(Op::num_5);
    c.Input(Op::period); // 5digits with decimal point
    c.Input(Op::eex);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345 00"); // must in floating input
    EXPECT_EQ(decimal_point, 3);
}

// Edit then del
TEST(ConsoleEditing, EditNumDel)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12      "); // intermediate
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::del);
    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // 2nd del works as clx
    EXPECT_EQ(decimal_point, 7);
}

// Clx, del then, number
TEST(ConsoleEditing, ClxDelNum)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::clx);
    c.Input(Op::del);
    c.Input(Op::num_1);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1       "); // after clx, must input correct
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// bit Negate
TEST(ConsoleEditing, BitNegate)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 000000FF"); // Before bit neg
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::bit_neg);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFF01"); // must bit not + 1
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// bit Negate
TEST(ConsoleEditing, BitNot)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::hex);
    c.Input(Op::num_f);
    c.Input(Op::num_f);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 000000FF"); // before operation
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::bit_not);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " FFFFFF00"); // bit not
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Edit with period
TEST(ConsoleEditing, EditWithPeriod)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12      "); // first 2 digit
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
    c.Input(Op::period);
    c.Input(Op::num_3);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123     "); // 3 digit and period
    EXPECT_EQ(decimal_point, 6);             // now, "12.3"

    c.Input(Op::del); // now, "12."
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12      "); // just before deleting period
    EXPECT_EQ(decimal_point, 6);

    c.Input(Op::del); // now, "12"
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12      "); // period is deleted
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del); // now, "1"
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1       "); // and delete digit
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);
}

// Input period immediately
TEST(ConsoleEditing, ImmediatePeriod)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::period);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0       "); // must 0.0000000
    EXPECT_EQ(decimal_point, 7);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer1)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 10000000"); // 1 digit
    EXPECT_EQ(decimal_point, 7);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer2)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12000000"); // 2 digit
    EXPECT_EQ(decimal_point, 6);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer3)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12300000"); // 3 digit
    EXPECT_EQ(decimal_point, 5);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer4)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12340000"); // 4 digit
    EXPECT_EQ(decimal_point, 4);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer5)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345000"); // 5 digit
    EXPECT_EQ(decimal_point, 3);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer6)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5);
    c.Input(Op::num_6);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345600"); // 6 digit
    EXPECT_EQ(decimal_point, 2);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer7)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5);
    c.Input(Op::num_6);
    c.Input(Op::num_7);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345670"); // 7 digit
    EXPECT_EQ(decimal_point, 1);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, Integer8)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::num_4);
    c.Input(Op::num_5);
    c.Input(Op::num_6);
    c.Input(Op::num_7);
    c.Input(Op::num_8);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 12345678"); // 8 digit
    EXPECT_EQ(decimal_point, 0);
}

// Comprehensive test for integer input
TEST(ConsoleEditing, RenderBiggerNumber)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::period);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.Input(Op::eex);
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::enter);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+12300+12"); // must in scientific display
    EXPECT_EQ(decimal_point, 7);
}

// Duplication check by enter key.
TEST(ConsoleEditing, EnterCheck)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_1);
    c.Input(Op::enter);
    c.Input(Op::num_2);
    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 10000000"); // must in scientific display
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // must in scientific display
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // must in scientific display
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 20000000"); // must in scientific display
    EXPECT_EQ(decimal_point, 7);
}

// The input ".3" must be interpreted as "0.3"
// Issue #3
TEST(ConsoleEditing, InputFromPeriod)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::period);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 0       "); // Leading 0
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_3);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 03      "); // Leading 0
    EXPECT_EQ(decimal_point, 7);
}

// The [Clear] during editing must not push the stack
// Issue #5
TEST(ConsoleEditing, DeleteAllDuringReset)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // Initial value
    EXPECT_EQ(decimal_point, 7);
    c.Input(Op::num_9); // Set initial T
    c.Input(Op::enter);
    c.Input(Op::num_8); // Set initial Z
    c.Input(Op::enter);
    c.Input(Op::num_7); // Set initial Y
    c.Input(Op::enter);
    c.Input(Op::num_6); // Set initial X

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 70000000"); // Y
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 80000000"); // Z
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 90000000"); // T
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 60000000"); // X
    EXPECT_EQ(decimal_point, 7);

    // Now we edit on the X register. The current X register value is 9.
    c.Input(Op::num_1);
    c.Input(Op::num_2);
    c.Input(Op::num_3);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 123     "); // must delete last digit
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 1       "); // must delete last digit
    EXPECT_EQ(decimal_point, c.kDecimalPointNotDisplayed);

    c.Input(Op::del);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // must delete last digit
    EXPECT_EQ(decimal_point, 7);

    // Up to here, the X register value is as expected.
    // Now, let's check other register.

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 70000000"); // Y
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 80000000"); // Z
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 90000000"); // T
    EXPECT_EQ(decimal_point, 7);

    c.Input(Op::rotate_pop);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 00000000"); // X
    EXPECT_EQ(decimal_point, 7);
}
