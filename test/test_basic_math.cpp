// Test cases for the basic math operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>
#include <complex>

typedef rpn_engine::StackStrategy TheStack;

TEST(BasicMathTest, Add)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Operation(rpn_engine::Op::add);

    EXPECT_EQ(s->Get(0).real(), 11); // check the stack top.
    EXPECT_EQ(s->Get(1).real(), 4);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 3);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 3);  // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 6); // check the stack top.
    EXPECT_EQ(s->Get(1).real(), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 3); // check the stack 4th.
    delete s;
}

TEST(BasicMathTest, Sub)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Operation(rpn_engine::Op::sub);

    EXPECT_EQ(s->Get(0).real(), -1); // check the stack top.
    EXPECT_EQ(s->Get(1).real(), 4);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 3);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 3);  // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Mul)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Operation(rpn_engine::Op::mul);

    EXPECT_EQ(s->Get(0).real(), 30); // check the stack top.
    EXPECT_EQ(s->Get(1).real(), 4);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 3);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 3);  // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 6); // check the stack top.
    delete s;
}


TEST(BasicMathTest, Neg)
{
    TheStack *s;
    s = new TheStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Operation(rpn_engine::Op::neg);

    EXPECT_EQ(s->Get(0).real(), -6); // check the stack top.
    EXPECT_EQ(s->Get(1).real(), 5);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2).real(), 4);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3).real(), 3);  // check the stack 4th.

    s->Undo();
    EXPECT_EQ(s->Get(0).real(), 6); // check the stack top.
    delete s;
}






