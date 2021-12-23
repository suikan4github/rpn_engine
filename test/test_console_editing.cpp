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
    EXPECT_STREQ(display_text, " 31415927"); // must be pi
    EXPECT_EQ(decimal_point, 7);
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
