#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::SegmentDecoder;

//. Test of incomplete coverage
TEST(SegmentDecoderDeathTest, completeness)
{
    ASSERT_DEATH(SegmentDecoder sd(1, 2, 4, 8, 16, 32, 64, 120), "seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_e_ | seg_f_ | seg_g_ | seg_period_ == 0xFF");
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_b)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x03, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80), "mask & seg_b_");
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_c)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x06, 0x08, 0x10, 0x20, 0x40, 0x80), "mask & seg_c_");
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_d)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x0c, 0x10, 0x20, 0x40, 0x80), "mask & seg_d_");
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_e)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x18, 0x20, 0x40, 0x80), "mask & seg_e_");
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_f)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x30, 0x40, 0x80), "mask & seg_f_");
}
// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_g)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x60, 0x80), "mask & seg_g_");
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_period)
{
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0xc0), "mask & seg_period_");
}
