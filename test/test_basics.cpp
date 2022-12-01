// Test cases for the basic stack operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>
#include <complex>

using rpn_engine::Op;
typedef rpn_engine::StackStrategy<std::complex<double>> TheStack;

// Testing the restriction of the stack size .
TEST(BasicStackDeathTest, StackSizeLimit)
{
    TheStack *s;
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(
        {
            s = new TheStack(0); // must not be non zero
            if (s == nullptr)    // Dummy code to supress the "unsed" warning.
            {
            }
        },
        "stack_size_ >= 2");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_0)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_0), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_1)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_1), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_2)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_2), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_3)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_3), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_4)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_4), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_5)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_5), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_6)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_6), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_7)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_7), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_8)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_8), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_9)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_9), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_a)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_a), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_b)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_b), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_c)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_c), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_d)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_d), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_e)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_e), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, num_f)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::num_f), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, period)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::period), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, clx)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::clx), "opcode != Op::clx");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, del)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::del), "Op::num_0 > opcode");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, change_display)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::change_display), "opcode != Op::change_display");
#endif
}

// Testing the restriction of opcode
TEST(BasicStackDeathTest, enter)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::enter), "opcode != Op::enter");
#endif
}

// Testing the restriction of the wrong operation
TEST(BasicStackDeathTest, eex)
{
    TheStack *s;
    s = new TheStack(4);

#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(s->Operation(Op::eex), "Op::num_0 > opcode");
#endif
}

// Testing the wrong opecode
TEST(BasicStackDeathTest, GetPositionExceedStackLimit)
{
    TheStack *s;
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(
        {
            s = new TheStack(4);
            s->Get(4).real(); // Accessing the position exeeds the Stack size.
        },
        "stack_size_ > postion");
#endif
}

TEST(BasicStackTest, StackInitialValueCheck)
{
    TheStack *s;
    s = new TheStack(4);
    EXPECT_EQ(s->Get(0).real(), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(1).real(), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(2).real(), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3).real(), 0); // check Whether the stack is initialize
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 0); // check the stack top
    delete s;
}

TEST(BasicStackTest, GetAndPush)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    EXPECT_EQ(s->Get(0).real(), 1); // Check pushed value
    EXPECT_EQ(s->Get(1).real(), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(2).real(), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3).real(), 0); // check Whether the stack is initialize
    s->Push(2);
    EXPECT_EQ(s->Get(0).real(), 2); // Check pushed value
    EXPECT_EQ(s->Get(1).real(), 1); // Check pushed value
    EXPECT_EQ(s->Get(2).real(), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3).real(), 0); // check Whether the stack is initialize
    s->Push(3);
    s->Push(4);
    s->Push(5);
    EXPECT_EQ(s->Get(0).real(), 5); // Check pushed value
    EXPECT_EQ(s->Get(1).real(), 4); // Check pushed value
    EXPECT_EQ(s->Get(2).real(), 3); // Check pushed value
    EXPECT_EQ(s->Get(3).real(), 2); // Check pushed value
    delete s;
}

// Test for very small stack
TEST(BasicStackTest, GetAndPush2)
{
    TheStack *s;
    s = new TheStack(2);
    s->Push(1);
    EXPECT_EQ(s->Get(0).real(), 1); // Check pushed value
    EXPECT_EQ(s->Get(1).real(), 0); // Check pushed value
    s->Push(2);
    EXPECT_EQ(s->Get(0).real(), 2); // Check pushed value
    EXPECT_EQ(s->Get(1).real(), 1); // Check pushed value
    delete s;
}

TEST(BasicStackTest, Set)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Get(0).real(), 4); // Check pushed value
    s->SetX(8);
    EXPECT_EQ(s->Get(0).real(), 8); // Check pushed value
    EXPECT_EQ(s->Get(1).real(), 3); // Check pushed value
    delete s;
}

TEST(BasicStackTest, PushAndUndo)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Push(5);

    s->Undo();               // cancel last operation
    EXPECT_EQ(s->Get(0).real(), 4); //
    EXPECT_EQ(s->Get(1).real(), 3); //
    EXPECT_EQ(s->Get(2).real(), 2); //
    EXPECT_EQ(s->Get(3).real(), 1); //
    delete s;
}

TEST(BasicStackTest, Pop)
{
    TheStack *s;
    s = new TheStack(4);
    EXPECT_EQ(s->Pop().real(), 0); // check Whether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop().real(), 4);  // check Whether the last pushed value is able to pop.
    EXPECT_EQ(s->Get(0).real(), 3); // check Whether the stack top is lost and popped up.
    EXPECT_EQ(s->Get(1).real(), 2); // check Whether the stack is popped up.
    EXPECT_EQ(s->Get(2).real(), 1); // check Whether the stack top is popped up.
    EXPECT_EQ(s->Get(3).real(), 1); // check Whether the stack top is popped up.
    delete s;
}

TEST(BasicStackTest, PopAndUndo)
{
    TheStack *s;
    s = new TheStack(4);
    EXPECT_EQ(s->Pop().real(), 0); // check Whether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop().real(), 4); // check Whether the last pushed value is able to pop.

    // last operation is canceled.
    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 4);
    delete s;
}

// Test for very small stack
TEST(BasicStackTest, Pop2)
{
    TheStack *s;
    s = new TheStack(2);
    EXPECT_EQ(s->Pop().real(), 0); // check Whether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop().real(), 4);  // check Whether the last pushed value is able to pop.
    EXPECT_EQ(s->Get(0).real(), 3); // check Whether the stack top is lost and popped up.
    EXPECT_EQ(s->Get(0).real(), 3); // check Whether the stack top is lost and popped up.
    delete s;
}

TEST(BasicStackTest, Dup)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::duplicate);
    EXPECT_EQ(s->Get(0).real(), 4); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 2); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 4); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 1); // check the stack 4th.
    delete s;
}

TEST(BasicStackTest, Swap)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::swap);
    EXPECT_EQ(s->Get(0).real(), 3); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 1); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 4); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 1); // check the stacks 4th.

    delete s;
}

TEST(BasicStackTest, RotatePop)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::rotate_pop);
    EXPECT_EQ(s->Get(0).real(), 3); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 2); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 1); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 4); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 4); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 1); // check the stack 4th.

    delete s;
}

TEST(BasicStackTest, RotatePush)
{
    TheStack *s;
    s = new TheStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::rotate_push);
    EXPECT_EQ(s->Get(0).real(), 1); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 2); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 4); // check the stack top
    EXPECT_EQ(s->Get(1).real(), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 1); // check the stack 4th.

    delete s;
}
