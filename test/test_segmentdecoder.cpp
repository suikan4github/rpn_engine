#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::SegmentDecoder;

//. Test of incomplete coverage
TEST(SegmentDecoderDeathTest, completeness)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(1, 2, 4, 8, 16, 32, 64, 120), "seg_a_ \\| seg_b_ \\| seg_c_ \\| seg_d_ \\| seg_e_ \\| seg_f_ \\| seg_g_ \\| seg_period_");
#endif
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_b)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x03, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80), "mask & seg_b_");
#endif
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_c)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x06, 0x08, 0x10, 0x20, 0x40, 0x80), "mask & seg_c_");
#endif
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_d)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x0c, 0x10, 0x20, 0x40, 0x80), "mask & seg_d_");
#endif
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_e)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x18, 0x20, 0x40, 0x80), "mask & seg_e_");
#endif
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_f)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x30, 0x40, 0x80), "mask & seg_f_");
#endif
}
// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_g)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x60, 0x80), "mask & seg_g_");
#endif
}

// Overwrapping test
TEST(SegmentDecoderDeathTest, Overwrapping_period)
{
#ifndef NDEBUG
    // We test only when assert() works.
    ASSERT_DEATH(SegmentDecoder sd(0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0xc0), "mask & seg_period_");
#endif
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
    EXPECT_EQ(sd.decode('b'), 0x7C);
    EXPECT_EQ(sd.decode('B'), 0x7C);
    EXPECT_EQ(sd.decode('c'), 0x39);
    EXPECT_EQ(sd.decode('C'), 0x39);
    EXPECT_EQ(sd.decode('d'), 0x5E);
    EXPECT_EQ(sd.decode('D'), 0x5E);
    EXPECT_EQ(sd.decode('e'), 0x79);
    EXPECT_EQ(sd.decode('E'), 0x79);
    EXPECT_EQ(sd.decode('f'), 0x71);
    EXPECT_EQ(sd.decode('F'), 0x71);
    EXPECT_EQ(sd.decode('g'), 0x3d);
    EXPECT_EQ(sd.decode('G'), 0x3d);
    EXPECT_EQ(sd.decode('h'), 0x76);
    EXPECT_EQ(sd.decode('H'), 0x76);
    EXPECT_EQ(sd.decode('i'), 0x06);
    EXPECT_EQ(sd.decode('I'), 0x06);
    EXPECT_EQ(sd.decode('j'), 0x0e);
    EXPECT_EQ(sd.decode('J'), 0x0e);
    EXPECT_EQ(sd.decode('l'), 0x38);
    EXPECT_EQ(sd.decode('L'), 0x38);
    EXPECT_EQ(sd.decode('n'), 0x54);
    EXPECT_EQ(sd.decode('N'), 0x54);
    EXPECT_EQ(sd.decode('o'), 0x3f);
    EXPECT_EQ(sd.decode('O'), 0x3f);
    EXPECT_EQ(sd.decode('p'), 0x73);
    EXPECT_EQ(sd.decode('P'), 0x73);
    EXPECT_EQ(sd.decode('q'), 0x67);
    EXPECT_EQ(sd.decode('Q'), 0x67);
    EXPECT_EQ(sd.decode('r'), 0x50);
    EXPECT_EQ(sd.decode('R'), 0x50);
    EXPECT_EQ(sd.decode('s'), 0x6d);
    EXPECT_EQ(sd.decode('S'), 0x6d);
    EXPECT_EQ(sd.decode('t'), 0x78);
    EXPECT_EQ(sd.decode('T'), 0x78);
    EXPECT_EQ(sd.decode('u'), 0x3e);
    EXPECT_EQ(sd.decode('U'), 0x3e);
    EXPECT_EQ(sd.decode('y'), 0x6e);
    EXPECT_EQ(sd.decode('Y'), 0x6e);
    EXPECT_EQ(sd.decode('.'), 0x80);
    EXPECT_EQ(sd.decode('_'), 0x08);
    EXPECT_EQ(sd.decode('?'), 0x00); // Unknown code must be set as blank.
}
