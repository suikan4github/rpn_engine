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
    TEST(Console, Mode)
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

namespace rpn_engine
{
    TEST(Console, PrimitivePi)
    {
        rpn_engine::Console c;

        c.Input(Op::pi);
        EXPECT_DOUBLE_EQ(c.engine_.Get(0).real(), 3.14159265358979323846);
    }
}

namespace rpn_engine
{
    TEST(Console, FixedMode)
    {
        rpn_engine::Console c;

        c.engine_.Push(3.14);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 31400000");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-3.14);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-31400000");
        EXPECT_EQ(c.decimal_point_position_, 7);
        // #.#######
        c.engine_.Push(9.99999994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-9.99999994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 7);

        // ##.######
        c.engine_.Push(9.99999995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 6);

        c.engine_.Push(-9.99999995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 6);

        c.engine_.Push(99.9999994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 6);

        c.engine_.Push(-99.9999994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 6);

        // ###.#####
        c.engine_.Push(99.9999995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 5);

        c.engine_.Push(-99.9999995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 5);

        c.engine_.Push(999.999994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 5);

        c.engine_.Push(-999.999994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 5);

        // ####.####
        c.engine_.Push(999.999995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 4);

        c.engine_.Push(-999.999995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 4);

        // #####.###
        c.engine_.Push(9999.99995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 3);

        c.engine_.Push(-9999.99995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 3);

        c.engine_.Push(99999.9994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 3);

        c.engine_.Push(-99999.9994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 3);

        // ######.##
        c.engine_.Push(99999.9995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 2);

        c.engine_.Push(-99999.9995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 2);

        c.engine_.Push(999999.994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 2);

        c.engine_.Push(-999999.994);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 2);

        // #######.#
        c.engine_.Push(999999.995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 1);

        c.engine_.Push(-999999.995);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 1);

        c.engine_.Push(9999999.94);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 1);

        c.engine_.Push(-9999999.94);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 1);

        // #######.#
        c.engine_.Push(9999999.95);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 10000000");
        EXPECT_EQ(c.decimal_point_position_, 0);

        c.engine_.Push(-9999999.95);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000000");
        EXPECT_EQ(c.decimal_point_position_, 0);

        c.engine_.Push(99999999.4);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 99999999");
        EXPECT_EQ(c.decimal_point_position_, 0);
        std::cout << "c.text_buffer_: " << c.text_buffer_ << std::endl;

        c.engine_.Push(-99999999.4);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 0);
#if 0
#endif
    }
}
