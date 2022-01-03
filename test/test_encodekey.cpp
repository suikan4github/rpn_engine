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

TEST(EncodeKey, dec_normal)
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

TEST(EncodeKey, dec_func)
{
    EXPECT_EQ(rpn_engine::EncodeKey(XTOM, true, false), Op::swap_re_im);
    EXPECT_EQ(rpn_engine::EncodeKey(CM, true, false), Op::decomplex);
    EXPECT_EQ(rpn_engine::EncodeKey(RM, true, false), Op::rotate_push);
    EXPECT_EQ(rpn_engine::EncodeKey(MMINUS, true, false), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(MPLUS, true, false), Op::func);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM7, true, false), Op::exp);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM8, true, false), Op::power10);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM9, true, false), Op::conjugate);
    EXPECT_EQ(rpn_engine::EncodeKey(DIV, true, false), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(C, true, false), Op::clx);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM4, true, false), Op::log);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM5, true, false), Op::log10);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM6, true, false), Op::hex);
    EXPECT_EQ(rpn_engine::EncodeKey(MUL, true, false), Op::power);
    EXPECT_EQ(rpn_engine::EncodeKey(CE, true, false), Op::pi);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM1, true, false), Op::sin);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM2, true, false), Op::cos);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM3, true, false), Op::tan);
    EXPECT_EQ(rpn_engine::EncodeKey(MINUS, true, false), Op::to_cartesian);
    EXPECT_EQ(rpn_engine::EncodeKey(SQRT, true, false), Op::nop);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM0, true, false), Op::asin);
    EXPECT_EQ(rpn_engine::EncodeKey(PERIOD, true, false), Op::acos);
    EXPECT_EQ(rpn_engine::EncodeKey(PERCENT, true, false), Op::atan);
    EXPECT_EQ(rpn_engine::EncodeKey(PLUS, true, false), Op::to_polar);
    EXPECT_EQ(rpn_engine::EncodeKey(EQUAL, true, false), Op::undo);
}

TEST(EncodeKey, hex_normal)
{
    EXPECT_EQ(rpn_engine::EncodeKey(XTOM, false, true), Op::swap);
    EXPECT_EQ(rpn_engine::EncodeKey(CM, false, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(RM, false, true), Op::rotate_pop);
    EXPECT_EQ(rpn_engine::EncodeKey(MMINUS, false, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(MPLUS, false, true), Op::func);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM7, false, true), Op::num_7);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM8, false, true), Op::num_8);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM9, false, true), Op::num_9);
    EXPECT_EQ(rpn_engine::EncodeKey(DIV, false, true), Op::bit_div);
    EXPECT_EQ(rpn_engine::EncodeKey(C, false, true), Op::del);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM4, false, true), Op::num_4);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM5, false, true), Op::num_5);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM6, false, true), Op::num_6);
    EXPECT_EQ(rpn_engine::EncodeKey(MUL, false, true), Op::bit_mul);
    EXPECT_EQ(rpn_engine::EncodeKey(CE, false, true), Op::nop);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM1, false, true), Op::num_1);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM2, false, true), Op::num_2);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM3, false, true), Op::num_3);
    EXPECT_EQ(rpn_engine::EncodeKey(MINUS, false, true), Op::bit_sub);
    EXPECT_EQ(rpn_engine::EncodeKey(SQRT, false, true), Op::nop);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM0, false, true), Op::num_0);
    EXPECT_EQ(rpn_engine::EncodeKey(PERIOD, false, true), Op::period);
    EXPECT_EQ(rpn_engine::EncodeKey(PERCENT, false, true), Op::bit_neg);
    EXPECT_EQ(rpn_engine::EncodeKey(PLUS, false, true), Op::bit_add);
    EXPECT_EQ(rpn_engine::EncodeKey(EQUAL, false, true), Op::enter);
}

TEST(EncodeKey, hex_func)
{
    EXPECT_EQ(rpn_engine::EncodeKey(XTOM, true, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(CM, true, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(RM, true, true), Op::rotate_push);
    EXPECT_EQ(rpn_engine::EncodeKey(MMINUS, true, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(MPLUS, true, true), Op::func);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM7, true, true), Op::logical_shift_left);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM8, true, true), Op::logical_shift_right);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM9, true, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(DIV, true, true), Op::nop);
    EXPECT_EQ(rpn_engine::EncodeKey(C, true, true), Op::clx);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM4, true, true), Op::num_e);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM5, true, true), Op::num_f);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM6, true, true), Op::dec);
    EXPECT_EQ(rpn_engine::EncodeKey(MUL, true, true), Op::bit_and);
    EXPECT_EQ(rpn_engine::EncodeKey(CE, true, true), Op::nop);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM1, true, true), Op::num_b);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM2, true, true), Op::num_c);
    EXPECT_EQ(rpn_engine::EncodeKey(NUM3, true, true), Op::num_d);
    EXPECT_EQ(rpn_engine::EncodeKey(MINUS, true, true), Op::bit_xor);
    EXPECT_EQ(rpn_engine::EncodeKey(SQRT, true, true), Op::nop);

    EXPECT_EQ(rpn_engine::EncodeKey(NUM0, true, true), Op::num_a);
    EXPECT_EQ(rpn_engine::EncodeKey(PERIOD, true, true), Op::period);
    EXPECT_EQ(rpn_engine::EncodeKey(PERCENT, true, true), Op::bit_not);
    EXPECT_EQ(rpn_engine::EncodeKey(PLUS, true, true), Op::bit_or);
    EXPECT_EQ(rpn_engine::EncodeKey(EQUAL, true, true), Op::undo);
}
