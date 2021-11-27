#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>

typedef rpn_engine::StackStrategy<int> IntStack;
IntStack *s;

// Testing the restriction of the stack size .
TEST(RPNTest, StackSizeLimit)
{
    ASSERT_DEATH(
        {
            s = new IntStack(0); // must not be non zero
        },
        "Assertion `stack_size_ >= 2' failed");
}

// Testing the restriction of the stack size and get() member function.
TEST(RPNTest, GetPositionExceedStackLimit)
{
    ASSERT_DEATH(
        {
            s = new IntStack(4);
            s->Get(4); // Accessing the position exeeds the Stack size.
        },
        "Assertion `stack_size_ > postion' failed");
}

TEST(RPNTest, StackInitialValueCheck)
{
    s = new IntStack(4);
    EXPECT_EQ(s->Get(0), 0); // check wether the stack is initialize
    EXPECT_EQ(s->Get(1), 0); // check wether the stack is initialize
    EXPECT_EQ(s->Get(2), 0); // check wether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check wether the stack is initialize
}

TEST(RPNTest, GetAndPush)
{
    s = new IntStack(4);
    s->Push(1);
    EXPECT_EQ(s->Get(0), 1); // Check pushed value
    EXPECT_EQ(s->Get(1), 0); // check wether the stack is initialize
    EXPECT_EQ(s->Get(2), 0); // check wether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check wether the stack is initialize
    s->Push(2);
    EXPECT_EQ(s->Get(0), 2); // Check pushed value
    EXPECT_EQ(s->Get(1), 1); // Check pushed value
    EXPECT_EQ(s->Get(2), 0); // check wether the stack is initialize
    EXPECT_EQ(s->Get(3), 0); // check wether the stack is initialize
    s->Push(3);
    s->Push(4);
    s->Push(5);
    EXPECT_EQ(s->Get(0), 5); // Check pushed value
    EXPECT_EQ(s->Get(1), 4); // Check pushed value
    EXPECT_EQ(s->Get(2), 3); // Check pushed value
    EXPECT_EQ(s->Get(3), 2); // Check pushed value
}

TEST(RPNTest, GetAndPush1)
{
    s = new IntStack(2);
    s->Push(1);
    EXPECT_EQ(s->Get(0), 1); // Check pushed value
    EXPECT_EQ(s->Get(1), 0); // Check pushed value
    s->Push(2);
    EXPECT_EQ(s->Get(0), 2); // Check pushed value
    EXPECT_EQ(s->Get(1), 1); // Check pushed value
}

TEST(RPNTest, Pop)
{
    s = new IntStack(4);
    EXPECT_EQ(s->Pop(), 0); // check wether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop(), 4);  // check wether the last pushed value is able to pop.
    EXPECT_EQ(s->Get(0), 3); // check wether the stack top is lost and poped up.
    EXPECT_EQ(s->Get(1), 2); // check wether the stack is poped up.
    EXPECT_EQ(s->Get(2), 1); // check wether the stack top is popped up.
    EXPECT_EQ(s->Get(3), 1); // check wether the stack top is poped up.
}

TEST(RPNTest, Pop2)
{
    s = new IntStack(2);
    EXPECT_EQ(s->Pop(), 0); // check wether the stack is initialize
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    EXPECT_EQ(s->Pop(), 4);  // check wether the last pushed value is able to pop.
    EXPECT_EQ(s->Get(0), 3); // check wether the stack top is lost and poped up.
    EXPECT_EQ(s->Get(0), 3); // check wether the stack top is lost and poped up.
}

TEST(RPNTest, Dup)
{
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Duplicate();
    EXPECT_EQ(s->Get(0), 4); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 4); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 2); // check wether the stack 4th.
}

TEST(RPNTest, Swap)
{
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->Swap();
    EXPECT_EQ(s->Get(0), 3); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 4); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 2); // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 1); // check wether the stack 4th.
}

TEST(RPNTest, RotatePop)
{
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->RotatePop();
    EXPECT_EQ(s->Get(0), 3); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 2); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 1); // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4); // check wether the stack 4th.
}

TEST(RPNTest, RotatePush)
{
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->RotatePush();
    EXPECT_EQ(s->Get(0), 1); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 4); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 2); // check wether the stack 4th.
}

TEST(RPNTest, SetTop)
{
    s = new IntStack(4);
    s->Push(1);
    s->Push(2);
    s->Push(3);
    s->Push(4);
    s->SetTop(100);
    EXPECT_EQ(s->Get(0), 100); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 3);   // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 2);   // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 1);   // check wether the stack 4th.
}
