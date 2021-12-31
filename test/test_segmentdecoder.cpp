#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

using rpn_engine::SegmentDecoder;

TEST(SegmentDecoderDeathTest, overwrapped)
{
    ASSERT_DEATH(SegmentDecoder sd(1, 2, 3, 4, 5, 6, 6, 7), "seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_e_ | seg_f_ | seg_g_ | seg_period_ == 0xFF");
}
