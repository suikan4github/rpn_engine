#include "gtest/gtest.h"
#include "console.hpp"
#include <stdexcept>

using rpn_engine::DisplayMode;
using rpn_engine::Op;

TEST(Console, IsFuncKeyPressed)
{
    rpn_engine::Console c;

    EXPECT_FALSE(c.GetIsFuncKeyPressed());
    c.SetIsFuncKeyPressed(true);
    EXPECT_TRUE(c.GetIsFuncKeyPressed());
    c.SetIsFuncKeyPressed(false);
    EXPECT_FALSE(c.GetIsFuncKeyPressed());
}

namespace rpn_engine
{
    TEST(Console, ModeTest)
    {
        rpn_engine::Console c;

        EXPECT_EQ(c.display_mode_, DisplayMode::fixed);
        c.Input(Op::change_display);
        EXPECT_EQ(c.display_mode_, DisplayMode::scientific);
        c.Input(Op::change_display);
        EXPECT_EQ(c.display_mode_, DisplayMode::engineering);
        c.Input(Op::change_display);
        EXPECT_EQ(c.display_mode_, DisplayMode::fixed);
    }
}