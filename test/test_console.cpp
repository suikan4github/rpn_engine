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

        c.engine_.Push(-99999999.4);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-99999999");
        EXPECT_EQ(c.decimal_point_position_, 0);

        // #.#######
        c.engine_.Push(0.00000014);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 00000001");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-0.00000014);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-00000001");
        EXPECT_EQ(c.decimal_point_position_, 7);
        c.engine_.Push(0.00000015);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, " 00000002");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-0.00000015);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-00000002");
        EXPECT_EQ(c.decimal_point_position_, 7);

        // very large number
        c.engine_.Push(100000000);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "+10000+08");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-100000000);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "-10000+08");
        EXPECT_EQ(c.decimal_point_position_, 7);

        // very small number
        c.engine_.Push(1e-8);
        c.RenderFixedMode();
        EXPECT_STREQ(c.text_buffer_, "+10000-08");
        EXPECT_EQ(c.decimal_point_position_, 7);
    }
}

namespace rpn_engine
{
    // Test the value which is unable to show in the fixed mode.
    // ex, very large, very small number.
    TEST(Console, ScientificMode)
    {
        rpn_engine::Console c;
        c.engine_.Push(4e8);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+40000+08");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(0.00000004);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+40000-08");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(0.000004);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+40000-06");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(0.0004);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+40000-04");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(0.04);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+40000-02");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(3.14);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+31400+00");
        EXPECT_EQ(c.decimal_point_position_, 7);

        // Very large number
        c.engine_.Push(1e100);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "+99999+99");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-1e100);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, "-99999+99");
        EXPECT_EQ(c.decimal_point_position_, 7);

        // Very small number
        c.engine_.Push(1e-100);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, " 00000000");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(-1e-100);
        c.RenderScientificMode(false); // render in the scientific mode
        EXPECT_STREQ(c.text_buffer_, " 00000000");
        EXPECT_EQ(c.decimal_point_position_, 7);
    }
}

namespace rpn_engine
{
    // Test the value which is unable to show in the fixed mode.
    // ex, very large, very small number.
    TEST(Console, EngineeringMode)
    {
        rpn_engine::Console c;
        c.engine_.Push(3.14);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+31400+00");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(31.4);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+31400+00");
        EXPECT_EQ(c.decimal_point_position_, 6);

        c.engine_.Push(314);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+31400+00");
        EXPECT_EQ(c.decimal_point_position_, 5);

        c.engine_.Push(3140);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+31400+03");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(1e-6);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+10000-06");
        EXPECT_EQ(c.decimal_point_position_, 7);

        c.engine_.Push(0.1e-6);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+10000-09");
        EXPECT_EQ(c.decimal_point_position_, 5);

        c.engine_.Push(0.01e-6);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+10000-09");
        EXPECT_EQ(c.decimal_point_position_, 6);

        c.engine_.Push(0.001e-6);
        c.RenderScientificMode(true); // render in the Engineering mode
        EXPECT_STREQ(c.text_buffer_, "+10000-09");
        EXPECT_EQ(c.decimal_point_position_, 7);
    }
}

TEST(Console, Inputmode)
{
    rpn_engine::Console c;
    char display_text[12];
    int decimal_point;

    c.Input(Op::pi);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, " 31415927");
    EXPECT_EQ(decimal_point, 7);

    // Scientific mode
    c.Input(Op::change_display);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+31415+00");
    EXPECT_EQ(decimal_point, 7);

    // Engineering mode
    c.Input(Op::change_display);
    c.Input(Op::square);
    c.Input(Op::square);
    c.GetText(display_text);
    decimal_point = c.GetDecimalPointPosition();
    EXPECT_STREQ(display_text, "+97409+00");
    EXPECT_EQ(decimal_point, 6);
}