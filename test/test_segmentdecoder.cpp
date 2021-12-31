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

// Segment check
TEST(SegmentDecoder, DecodeSegments)
{
    SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80);

    EXPECT_EQ(sd.decode(' '), 0);
    EXPECT_EQ(sd.decode('+'), 0);
    EXPECT_EQ(sd.decode('-'), 0x40);
    EXPECT_EQ(sd.decode('0'), 0x3f);
    EXPECT_EQ(sd.decode('1'), 0x06);
    EXPECT_EQ(sd.decode('2'), 0x5b);
    EXPECT_EQ(sd.decode('3'), 0x4f);
    EXPECT_EQ(sd.decode('4'), 0x66);
    EXPECT_EQ(sd.decode('5'), 0x6d);
    EXPECT_EQ(sd.decode('6'), 0x7d);
    EXPECT_EQ(sd.decode('7'), 0x07);
    EXPECT_EQ(sd.decode('8'), 0x7f);
    EXPECT_EQ(sd.decode('9'), 0x6f);
    EXPECT_EQ(sd.decode('a'), 0x77);
    EXPECT_EQ(sd.decode('A'), 0x77);
    EXPECT_EQ(sd.decode('e'), 0x79);
    EXPECT_EQ(sd.decode('E'), 0x79);
    EXPECT_EQ(sd.decode('f'), 0x71);
    EXPECT_EQ(sd.decode('F'), 0x71);
    EXPECT_EQ(sd.decode('l'), 0x38);
    EXPECT_EQ(sd.decode('l'), 0x38);
    EXPECT_EQ(sd.decode('n'), 0x54);
    EXPECT_EQ(sd.decode('N'), 0x54);
    EXPECT_EQ(sd.decode('p'), 0x73);
    EXPECT_EQ(sd.decode('P'), 0x73);
    EXPECT_EQ(sd.decode('r'), 0x50);
    EXPECT_EQ(sd.decode('R'), 0x50);
    EXPECT_EQ(sd.decode('.'), 0x80);

}
