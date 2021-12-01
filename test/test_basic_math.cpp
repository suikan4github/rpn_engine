// Test cases for the basic math operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>

typedef rpn_engine::StackStrategy<int> IntStack;

TEST(BasicMathTest, Add)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Add();

    EXPECT_EQ(s->Get(0), 11); // check the stack top.
    EXPECT_EQ(s->Get(1), 4);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);  // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6);  // check the stack top.
    EXPECT_EQ(s->Get(1), 11); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);  // check the stack 4th.
    delete s;
}

TEST(BasicMathTest, Sub)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Subtract();

    EXPECT_EQ(s->Get(0), -1); // check the stack top.
    EXPECT_EQ(s->Get(1), 4);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);  // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Mul)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Multiply();

    EXPECT_EQ(s->Get(0), 30); // check the stack top.
    EXPECT_EQ(s->Get(1), 4);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);  // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Div)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Divide();

    EXPECT_EQ(s->Get(0), 0); // check the stack top.
    EXPECT_EQ(s->Get(1), 4); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 3); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Neg)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Nagate();

    EXPECT_EQ(s->Get(0), -6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);  // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Inv)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Inverse();

    EXPECT_EQ(s->Get(0), 0); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Sqrt)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Sqrt();

    EXPECT_EQ(s->Get(0), 2); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Square)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Square();

    EXPECT_EQ(s->Get(0), 36); // check the stack top.
    EXPECT_EQ(s->Get(1), 5);  // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);  // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);  // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    delete s;
}

TEST(BasicMathTest, Complex)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Complex(); // must be no operation in scalar specialization

    // must be no change
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0); // must not saved.
    delete s;
}

TEST(BasicMathTest, DeComplex)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->DeComplex(); // must be no operation in scalar specialization

    // must be no change
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0); // must not saved.
    delete s;
}

TEST(BasicMathTest, Conjugate)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->Conjugate(); // must be no operation in scalar specialization

    // must be no change
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0); // must not saved.
    delete s;
}

TEST(BasicMathTest, ToPolar)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->ToPolar(); // must be no operation in scalar specialization

    // must be no change
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0); // must not saved.
    delete s;
}

TEST(BasicMathTest, ToCartesian)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->ToCartesian(); // must be no operation in scalar specialization

    // must be no change
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0); // must not saved.
    delete s;
}

TEST(BasicMathTest, SwapReIm)
{
    IntStack *s;
    s = new IntStack(4);

    s->Push(3);
    s->Push(4);
    s->Push(5);
    s->Push(6);
    s->SwapReIm(); // must be no operation in scalar specialization

    // must be no change
    EXPECT_EQ(s->Get(0), 6); // check the stack top.
    EXPECT_EQ(s->Get(1), 5); // check the stack 2nd.
    EXPECT_EQ(s->Get(2), 4); // check the stack 3rd.
    EXPECT_EQ(s->Get(3), 3); // check the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0); // must not saved.
    delete s;
}