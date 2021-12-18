// Test cases for the basic stack operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>

typedef rpn_engine::StackStrategy<int> IntStack;

// Testing the restriction of the stack size .
TEST(BasicStackDeathTest, StackSizeLimit)
{
    IntStack *s;
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(
        {
            s = new IntStack(0); // must not be non zero
        },
        "Assertion `stack_size_ >= 2' failed");
#endif
}

// Testing the restriction of the stack size and get() member function.
TEST(BasicStackDeathTest, GetPositionExceedStackLimit)
{
    IntStack *s;
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(
        {
            s = new IntStack(4);
            s->Get(4); // Accessing the position exeeds the Stack size.
        },
        "Assertion `stack_size_ > postion' failed");
#endif
}

TEST(BasicStackTest, StackInitialValueCheck)
{
    IntStack *s;
    s = new IntStack(4);
    EXPECT_EQ(s->Get(0), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(1), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(2), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check Whether the stack is initialize
    s->Undo();
    EXPECT_EQ(s->Get(0), 0); // check the stack top
    delete s;
}

TEST(BasicStackTest, GetAndPush)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    EXPECT_EQ(s->Get(0), 1); // Check pushed value
    EXPECT_EQ(s->Get(1), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(2), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check Whether the stack is initialize
    s->Push(2);
    EXPECT_EQ(s->Get(0), 2); // Check pushed value
    EXPECT_EQ(s->Get(1), 1); // Check pushed value
    EXPECT_EQ(s->Get(2), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check Whether the stack is initialize
    s->Push(3);
    s->Push(4);
    s->Push(5);
    EXPECT_EQ(s->Get(0), 5); // Check pushed value
    EXPECT_EQ(s->Get(1), 4); // Check pushed value
    EXPECT_EQ(s->Get(2), 3); // Check pushed value
    EXPECT_EQ(s->Get(3), 2); // Check pushed value
    delete s;
}

// Test for very small stack
TEST(BasicStackTest, GetAndPush2)
{
    IntStack *s;
    s = new IntStack(2);
    s->Push(1);
    EXPECT_EQ(s->Get(0), 1); // Check pushed value
    EXPECT_EQ(s->Get(1), 0); // Check pushed value
    s->Push(2);
    EXPECT_EQ(s->Get(0), 2); // Check pushed value
    EXPECT_EQ(s->Get(1), 1); // Check pushed value
    delete s;
}

TEST(BasicStackTest, PushAndUndo)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Push(5);

    s->Undo();               // cancel last operation
    EXPECT_EQ(s->Get(0), 4); //
    EXPECT_EQ(s->Get(1), 3); //
    EXPECT_EQ(s->Get(2), 2); //
    EXPECT_EQ(s->Get(3), 1); //
    delete s;
}

TEST(BasicStackTest, Pop)
{
    IntStack *s;
    s = new IntStack(4);
    EXPECT_EQ(s->Pop(), 0); // check Whether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop(), 4);  // check Whether the last pushed value is able to pop.
    EXPECT_EQ(s->Get(0), 3); // check Whether the stack top is lost and popped up.
    EXPECT_EQ(s->Get(1), 2); // check Whether the stack is popped up.
    EXPECT_EQ(s->Get(2), 1); // check Whether the stack top is popped up.
    EXPECT_EQ(s->Get(3), 1); // check Whether the stack top is popped up.
    delete s;
}

TEST(BasicStackTest, PopAndUndo)
{
    IntStack *s;
    s = new IntStack(4);
    EXPECT_EQ(s->Pop(), 0); // check Whether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop(), 4); // check Whether the last pushed value is able to pop.

    // last operation is canceled.
    s->Undo();
    EXPECT_EQ(s->Get(0), 4);
    delete s;
}

// Test for very small stack
TEST(BasicStackTest, Pop2)
{
    IntStack *s;
    s = new IntStack(2);
    EXPECT_EQ(s->Pop(), 0); // check Whether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop(), 4);  // check Whether the last pushed value is able to pop.
    EXPECT_EQ(s->Get(0), 3); // check Whether the stack top is lost and popped up.
    EXPECT_EQ(s->Get(0), 3); // check Whether the stack top is lost and popped up.
    delete s;
}

TEST(BasicStackTest, Dup)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::duplicate);
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 2); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check the stack 4th.
    delete s;
}

TEST(BasicStackTest, Swap)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::swap);
    EXPECT_EQ(s->Get(0), 3); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check the stacks 4th.

    delete s;
}

TEST(BasicStackTest, RotatePop)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::rotate_pop);
    EXPECT_EQ(s->Get(0), 3); // check the stack top
    EXPECT_EQ(s->Get(1), 2); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 1); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 4); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check the stack 4th.

    delete s;
}

TEST(BasicStackTest, RotatePush)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Operation(rpn_engine::Op::rotate_push);
    EXPECT_EQ(s->Get(0), 1); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 2); // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check the stack 4th.

    delete s;
}

namespace rpn_engine
{
    TEST(BasicStackTest, Undo)
    {
        IntStack *s;
        s = new IntStack(4);

        s->Push(1);
        s->Push(2);
        s->Push(3);
        s->Push(4);

        EXPECT_EQ(s->Get(0), 4); // check the stack top
        EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.
        EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
        EXPECT_EQ(s->Get(3), 1); // check the stack 4th.

        EXPECT_EQ(s->undo_saving_enabled_, true); // check the enabled state
        s->SaveToUndoBuffer();
        // Save stack state before mathematical operation
        {
            IntStack::DisableUndoSaving disable(s);
            EXPECT_EQ(s->undo_saving_enabled_, false); // check the enabled state

            s->Pop();
            s->Pop();
            EXPECT_EQ(s->undo_saving_enabled_, false); // check the enabled state
        }
        EXPECT_EQ(s->undo_saving_enabled_, true); // check the enabled state

        s->Undo();
        EXPECT_EQ(s->Get(0), 4); // check the stack top
        EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.
        EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
        EXPECT_EQ(s->Get(3), 1); // check the stack 4th.
        delete s;
    }
}