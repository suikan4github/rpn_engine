// Test cases for the basic stack operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>

typedef rpn_engine::StackStrategy<int> IntStack;

// Testing the restriction of the stack size .
TEST(BasicStackTest, StackSizeLimit)
{
    IntStack *s;
    ASSERT_DEATH(
        {
            s = new IntStack(0); // must not be non zero
        },
        "Assertion `stack_size_ >= 2' failed");
}

// Testing the restriction of the stack size and get() member function.
TEST(BasicStackTest, GetPositionExceedStackLimit)
{
    IntStack *s;
    ASSERT_DEATH(
        {
            s = new IntStack(4);
            s->Get(4); // Accessing the position exeeds the Stack size.
        },
        "Assertion `stack_size_ > postion' failed");
}

TEST(BasicStackTest, StackInitialValueCheck)
{
    IntStack *s;
    s = new IntStack(4);
    EXPECT_EQ(s->Get(0), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(1), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(2), 0); // check Whether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check Whether the stack is initialize
    s->LastX();
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
    EXPECT_EQ(s->Get(0), 3); // check Whether the stack top is lost and poped up.
    EXPECT_EQ(s->Get(1), 2); // check Whether the stack is poped up.
    EXPECT_EQ(s->Get(2), 1); // check Whether the stack top is popped up.
    EXPECT_EQ(s->Get(3), 1); // check Whether the stack top is poped up.
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
    EXPECT_EQ(s->Get(0), 3); // check Whether the stack top is lost and poped up.
    EXPECT_EQ(s->Get(0), 3); // check Whether the stack top is lost and poped up.
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
    s->Duplicate();
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 2); // check the stack 4th.
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
    s->Swap();
    EXPECT_EQ(s->Get(0), 3); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check the stack 4th.
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
    s->RotatePop();
    EXPECT_EQ(s->Get(0), 3); // check the stack top
    EXPECT_EQ(s->Get(1), 2); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 1); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 4); // check the stack 4th.
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
    s->RotatePush();
    EXPECT_EQ(s->Get(0), 1); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 2); // check the stack 4th.
    delete s;
}

TEST(BasicStackTest, SetTop)
{
    IntStack *s;
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->SetTop(100);
    EXPECT_EQ(s->Get(0), 100); // check the stack top
    EXPECT_EQ(s->Get(1), 3);   // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 2);   // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 1);   // check the stack 4th.
    delete s;
}

TEST(BasicStackTest, LastX)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);

    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 3); // check the stack 2nd.

    s->SaveToLastX();
    s->LastX();
    EXPECT_EQ(s->Get(0), 4); // check the stack top
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    delete s;
}
