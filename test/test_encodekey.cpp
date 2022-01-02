#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::Op;

#define CE 0, 0
#define XTOM 0, 1
#define NUM0 0, 2
#define NA1 1, 0
#define NUM7 1, 1
#define NUM4 1, 2
#define CM 2, 0
#define NUM8 2, 1
#define NUM1 2, 2
#define PERIOD 3, 0
#define NUM5 3, 1
#define PERCENT 3, 2
#define PLUS 4, 0
#define RM 4, 1
#define NUM2 4, 2
#define C 5, 0
#define NUM9 5, 1
#define EQUAL 5, 2
#define DIV 6, 0
#define MMINUS 6, 1
#define NA2 6, 2
#define MUL 7, 0
#define NUM6 7, 1
#define NUM3 7, 2
#define MINUS 8, 0
#define MPLUS 8, 1
#define SQRT 8, 2

TEST(EncodeKey, undefined_A)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA1, false, false), "false");
#endif
}

TEST(EncodeKey, undefined_B)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA2, false, false), "false");
#endif
}

TEST(EncodeKey, undefined_C)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA1, false, true), "false");
#endif
}

TEST(EncodeKey, undefined_D)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA2, false, true), "false");
#endif
}

TEST(EncodeKey, undefined_E)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA1, true, false), "false");
#endif
}

TEST(EncodeKey, undefined_F)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA2, true, false), "false");
#endif
}

TEST(EncodeKey, undefined_G)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA1, true, true), "false");
#endif
}

TEST(EncodeKey, undefined_H)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(rpn_engine::EncodeKey(NA2, true, true), "false");
#endif
}

TEST(EncodeKey, DEC_NORMAL)
{
    EXPECT_EQ(rpn_engine::EncodeKey(XTOM, false, false), Op::swap);
    EXPECT_EQ(rpn_engine::EncodeKey(CM, false, false), Op::complex);
    EXPECT_EQ(rpn_engine::EncodeKey(RM, false, false), Op::rotate_pop);
    EXPECT_EQ(rpn_engine::EncodeKey(MMINUS, false, false), Op::change_display);
    EXPECT_EQ(rpn_engine::EncodeKey(MPLUS, false, false), Op::func);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM7, false, false), Op::num_7);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM8, false, false), Op::num_8);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM9, false, false), Op::num_9);
    EXPECT_EQ(rpn_engine::EncodeKey(DIV, false, false), Op::div);
    EXPECT_EQ(rpn_engine::EncodeKey(C, false, false), Op::del);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM4, false, false), Op::num_4);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM5, false, false), Op::num_5);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM6, false, false), Op::num_6);
    EXPECT_EQ(rpn_engine::EncodeKey(MUL, false, false), Op::mul);
    EXPECT_EQ(rpn_engine::EncodeKey(CE, false, false), Op::eex);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM1, false, false), Op::num_1);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM2, false, false), Op::num_2);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM3, false, false), Op::num_3);
    EXPECT_EQ(rpn_engine::EncodeKey(MINUS, false, false), Op::sub);
    EXPECT_EQ(rpn_engine::EncodeKey(SQRT, false, false), Op::sqrt);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM0, false, false), Op::num_0);
    EXPECT_EQ(rpn_engine::EncodeKey(PERIOD, false, false), Op::period);
    EXPECT_EQ(rpn_engine::EncodeKey(PERCENT, false, false), Op::chs);
    EXPECT_EQ(rpn_engine::EncodeKey(PLUS, false, false), Op::add);
    EXPECT_EQ(rpn_engine::EncodeKey(EQUAL, false, false), Op::enter);
}