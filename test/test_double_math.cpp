// Test cases for the basic math operation of the rpn_engine::StackStrategy class

#include "gtest/gtest.h"
#include "stackstrategy.hpp"
#include <stdexcept>
#include <math.h>

typedef rpn_engine::StackStrategy<double> DoubleStack;

TEST(DoubleMathTest, Add)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Add();

    EXPECT_DOUBLE_EQ(s->Get(0), 11.0); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 4);           // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 3);           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);           // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 11);  // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);   // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);   // check wether the stack 4th.
}

TEST(DoubleMathTest, Div)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Divide();

    EXPECT_DOUBLE_EQ(s->Get(0), 0.833333333333333333); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 4);                           // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 3);                           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                           // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                      // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), 5.0 / (double)6.0); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                        // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                        // check wether the stack 4th.
}

TEST(DoubleMathTest, Inverse)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Inverse();

    EXPECT_DOUBLE_EQ(s->Get(0), 0.16666666666666666666); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                             // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                             // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                             // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                      // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), 1.0 / (double)6.0); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                        // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                        // check wether the stack 4th.
}

TEST(DoubleMathTest, Sqrt)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Sqrt();

    EXPECT_DOUBLE_EQ(s->Get(0), 2.4494897427831780981); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                            // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                            // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                            // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                      // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), sqrt((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                        // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                        // check wether the stack 4th.
}

TEST(DoubleMathTest, Pi)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Pi();

    // Comparing with 20 digit Pi. The double float is 15digit by decimal.
    // Google test is ignoring las few digit. So, it is comparing about 12digit.
    EXPECT_DOUBLE_EQ(s->Get(0), 3.14159265358979323846); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 6);                             // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                             // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                             // check wether the stack 4th.

    s->LastX();                        // Pi() doesn't save last X
    EXPECT_EQ(s->Get(0), 0);           // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), M_PI); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 6);           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 5);           // check wether the stack 4th.
}

TEST(DoubleMathTest, Exp)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Exp();

    EXPECT_DOUBLE_EQ(s->Get(0), 403.4287934927351226); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                           // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                           // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                     // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), exp((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                       // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                       // check wether the stack 4th.
}

TEST(DoubleMathTest, Log)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Log();

    EXPECT_DOUBLE_EQ(s->Get(0), 1.791759469228055000); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                           // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                           // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                     // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), log((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                       // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                       // check wether the stack 4th.
}

TEST(DoubleMathTest, Log10)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Log10();

    EXPECT_DOUBLE_EQ(s->Get(0), 0.7781512503836436325); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                            // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                            // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                            // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                       // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), log10((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                         // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                         // check wether the stack 4th.
}

TEST(DoubleMathTest, Pow10)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Power10();

    EXPECT_DOUBLE_EQ(s->Get(0), 1e6); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);          // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);          // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);          // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);        // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), 1e6); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);          // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);          // check wether the stack 4th.

    s->Push(2.5);
    s->Power10();
    EXPECT_DOUBLE_EQ(s->Get(0), 316.22776601683793); // check wether the stack top.
}

TEST(DoubleMathTest, Power)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Power();

    EXPECT_DOUBLE_EQ(s->Get(0), 15625); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 4);            // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 3);            // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);            // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                    // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::pow(5.0, 6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                      // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                      // check wether the stack 4th.

    s->Push(5.0);
    s->Push(2.5);
    s->Power();

    EXPECT_DOUBLE_EQ(s->Get(0), 55.90169943749474241); // check wether the stack top.
}

TEST(DoubleMathTest, Sin)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Sin();

    EXPECT_DOUBLE_EQ(s->Get(0), -0.27941549819892587); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                           // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                           // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                       // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::sin((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                         // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                         // check wether the stack 4th.
}

TEST(DoubleMathTest, Cos)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Cos();

    EXPECT_DOUBLE_EQ(s->Get(0), 0.96017028665036602054); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                             // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                             // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                             // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                       // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::cos((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                         // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                         // check wether the stack 4th.
}

TEST(DoubleMathTest, Tan)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(6.0);
    s->Tan();

    EXPECT_DOUBLE_EQ(s->Get(0), -0.2910061913847491570); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                             // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                             // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                             // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 6.0);                       // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::tan((double)6.0)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                         // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                         // check wether the stack 4th.
}

TEST(DoubleMathTest, Asin)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(0.5);
    s->Asin();

    EXPECT_DOUBLE_EQ(s->Get(0), 0.52359877559829887); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                          // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                          // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                          // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0.5);                         // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::asin((double)0.50)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                           // check wether the stack 4th.
}

TEST(DoubleMathTest, Acos)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(0.5);
    s->Acos();

    EXPECT_DOUBLE_EQ(s->Get(0), 1.0471975511965977); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                         // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                         // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                         // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0.5);                        // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::acos((double)0.5)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                          // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                          // check wether the stack 4th.
}

TEST(DoubleMathTest, Atan)
{
    DoubleStack *s;
    s = new DoubleStack(4);

    s->Push(3.0);
    s->Push(4);
    s->Push(5.0);
    s->Push(0.5);
    s->Atan();

    EXPECT_DOUBLE_EQ(s->Get(0), 0.4636476090008061162); // check wether the stack top.
    EXPECT_EQ(s->Get(1), 5);                            // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 4);                            // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 3);                            // check wether the stack 4th.

    s->LastX();
    EXPECT_EQ(s->Get(0), 0.5);                         // check wether the stack top.
    EXPECT_DOUBLE_EQ(s->Get(1), ::atan((double)0.50)); // check wether the stack 2nd.
    EXPECT_EQ(s->Get(2), 5);                           // check wether the stack 3rd.
    EXPECT_EQ(s->Get(3), 4);                           // check wether the stack 4th.
}
