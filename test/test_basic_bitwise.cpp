// Test cases for the basic bitwise operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>
#include <complex>

typedef rpn_engine::StackStrategy<std::complex<double>> TheStack;

TEST(BasicBitwiseTest, BitAdd)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3);
    s->Push(7);
    s->Operation(rpn_engine::Op::bit_add);
    EXPECT_EQ(s->Get(0).real(), 10);

    s->Push(3.14);
    s->Push(7.1);
    s->Operation(rpn_engine::Op::bit_add);
    EXPECT_EQ(s->Get(0).real(), 10);

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 7.1);
    EXPECT_EQ(s->Get(1).real(), 3.14);
    delete s;
}

TEST(BasicBitwiseTest, BitSubtract)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3);
    s->Push(7);
    s->Operation(rpn_engine::Op::bit_sub);
    EXPECT_EQ(s->Get(0).real(), -4);

    // truncation test
    s->Push(3.14);
    s->Push(7.1);
    s->Operation(rpn_engine::Op::bit_sub);
    EXPECT_EQ(s->Get(0).real(), -4);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 7.1);
    EXPECT_EQ(s->Get(1).real(), 3.14);
    delete s;
}

TEST(BasicBitwiseTest, BitMultiply)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3.14);
    s->Push(3);
    s->Push(7);
    s->Operation(rpn_engine::Op::bit_mul);
    EXPECT_EQ(s->Get(0).real(), 21);
    EXPECT_EQ(s->Get(1).real(), 3.14);

    s->Push(-3);
    s->Push(7);
    s->Operation(rpn_engine::Op::bit_mul);
    EXPECT_EQ(s->Get(0).real(), -21);

    s->Push(3);
    s->Push(-7);
    s->Operation(rpn_engine::Op::bit_mul);
    EXPECT_EQ(s->Get(0).real(), -21);

    s->Push(-3);
    s->Push(-7);
    s->Operation(rpn_engine::Op::bit_mul);
    EXPECT_EQ(s->Get(0).real(), 21);

    // truncation test
    s->Push(3.14);
    s->Push(7.1);
    s->Operation(rpn_engine::Op::bit_mul);
    EXPECT_EQ(s->Get(0).real(), 21);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 7.1);
    EXPECT_EQ(s->Get(1).real(), 3.14);
    delete s;
}

TEST(BasicBitwiseTest, BitDivide)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(4.2);
    s->Push(7.1);
    s->Push(3.1);
    s->Operation(rpn_engine::Op::bit_div);
    EXPECT_EQ(s->Get(0).real(), 2);
    EXPECT_EQ(s->Get(1).real(), 4.2);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 3.1);
    EXPECT_EQ(s->Get(1).real(), 7.1);
    delete s;
}

TEST(BasicBitwiseTest, BitNegate)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push(3.1);
    s->Operation(rpn_engine::Op::bit_neg);
    EXPECT_EQ(s->Get(0).real(), -3);
    EXPECT_EQ(s->Get(1).real(), 7.1);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 3.1);
    EXPECT_EQ(s->Get(1).real(), 7.1);
    delete s;
}

TEST(BasicBitwiseTest, BitOr)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push(0x55AA);
    s->Push(0xFF00);
    s->Operation(rpn_engine::Op::bit_or);
    EXPECT_EQ(s->Get(0).real(), 0xFFAA);
    EXPECT_EQ(s->Get(1).real(), 7.1);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 0xff00);
    EXPECT_EQ(s->Get(1).real(), 0x55aa);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->Operation(rpn_engine::Op::bit_or);
    EXPECT_EQ(s->Get(0).real(), 13); // 0x0D
    delete s;
}

TEST(BasicBitwiseTest, BitExor)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push(0x55AA);
    s->Push(0xFF00);
    s->Operation(rpn_engine::Op::bit_xor);
    EXPECT_EQ(s->Get(0).real(), 0xAAAA);
    EXPECT_EQ(s->Get(1).real(), 7.1);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 0xff00);
    EXPECT_EQ(s->Get(1).real(), 0x55aa);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->Operation(rpn_engine::Op::bit_xor);
    EXPECT_EQ(s->Get(0).real(), 9); // 0x09
    delete s;
}

TEST(BasicBitwiseTest, BitAnd)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push(0x55AA);
    s->Push(0xFF00);
    s->Operation(rpn_engine::Op::bit_and);
    EXPECT_EQ(s->Get(0).real(), 0x5500);
    EXPECT_EQ(s->Get(1).real(), 7.1);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 0xff00);
    EXPECT_EQ(s->Get(1).real(), 0x55aa);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->Operation(rpn_engine::Op::bit_and);
    EXPECT_EQ(s->Get(0).real(), 4); // 0x04
    delete s;
}

TEST(BasicBitwiseTest, LogicalShiftRight)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push(0x7FFFFFFF);
    s->Push(1);
    s->Operation(rpn_engine::Op::logical_shift_right);
    EXPECT_EQ(s->Get(0).real(), 0x3FFFFFFF);
    EXPECT_EQ(s->Get(1).real(), 7.1);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 1);

    // zero padding at MSB check
    s->Push(0x80000000);
    s->Push(1);
    s->Operation(rpn_engine::Op::logical_shift_right);
    EXPECT_EQ(s->Get(0).real(), 0x40000000);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->Operation(rpn_engine::Op::bit_and);
    EXPECT_EQ(s->Get(0).real(), 4); // 0x04
    delete s;
}

TEST(BasicBitwiseTest, LogicalShiftLeft)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push(0x7FFFFFFF);
    s->Push(1);
    s->Operation(rpn_engine::Op::logical_shift_left);
    EXPECT_EQ(s->Get(0).real(), (int32_t)0xFFFFFFFE);
    EXPECT_EQ(s->Get(1).real(), 7.1);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 1);

    // zero padding at MSB check
    s->Push(0xFFFFFFFF);
    s->Push(1);
    s->Operation(rpn_engine::Op::logical_shift_left);
    EXPECT_EQ(s->Get(0).real(), (int32_t)0xFFFFFFFE);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->Operation(rpn_engine::Op::logical_shift_left);
    EXPECT_EQ(s->Get(0).real(), 0x5000); //
    delete s;
}

TEST(BasicBitwiseTest, BitNot)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(7.1);
    s->Push((int32_t)0x5555AAAA);
    s->Operation(rpn_engine::Op::bit_not);
    EXPECT_EQ(s->Get(0).real(), (int32_t)0xAAAA5555);
    EXPECT_EQ(s->Get(1).real(), 7.1);
    s->Operation(rpn_engine::Op::bit_not);
    EXPECT_EQ(s->Get(0).real(), (int32_t)0x5555AAAA);

    // Undo test
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), (int32_t)0xAAAA5555);

    // truncation check
    s->Push(5.1);  // 0x05
    s->Push(12.0); // 0x0C
    s->Operation(rpn_engine::Op::bit_not);
    EXPECT_EQ(s->Get(0).real(), (int32_t)0xFFFFFFF3); //
    delete s;
}
