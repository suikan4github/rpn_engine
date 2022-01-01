#include "segmentdecoder.hpp"
#include "assert.h"

rpn_engine::SegmentDecoder::SegmentDecoder(uint8_t seg_a, uint8_t seg_b, uint8_t seg_c, uint8_t seg_d, uint8_t seg_e, uint8_t seg_f, uint8_t seg_g, uint8_t seg_period)
    : seg_a_(seg_a),
      seg_b_(seg_b),
      seg_c_(seg_c),
      seg_d_(seg_d),
      seg_e_(seg_e),
      seg_f_(seg_f),
      seg_g_(seg_g),
      seg_period_(seg_period)
{
    uint8_t mask;
    // consistency check.
    // All 8btis must be covered by given bit masks.
    assert((seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_e_ | seg_f_ | seg_g_ | seg_period_) == 0xFF);

    // Consistency check.
    // No bit masks can be owverwrapped.
    mask = seg_a_;
    assert((mask & seg_b_) == 0);
    mask |= seg_b_;
    assert((mask & seg_c_) == 0);
    mask |= seg_c_;
    assert((mask & seg_d_) == 0);
    mask |= seg_d_;
    assert((mask & seg_e_) == 0);
    mask |= seg_e_;
    assert((mask & seg_f_) == 0);
    mask |= seg_f_;
    assert((mask & seg_g_) == 0);
    mask |= seg_g_;
    assert((mask & seg_period_) == 0);
}

uint8_t rpn_engine::SegmentDecoder::decode(char c)
{
    uint8_t ret_val;

    switch (c)
    {
    case ' ':
        ret_val = 0;
        break;
    case '0':
        ret_val = seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_e_ | seg_f_;
        break;
    case 'i':
    case 'I':
    case '1':
        ret_val = seg_b_ | seg_c_;
        break;
    case '2':
        ret_val = seg_a_ | seg_b_ | seg_d_ | seg_e_ | seg_g_;
        break;
    case '3':
        ret_val = seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_g_;
        break;
    case '4':
        ret_val = seg_b_ | seg_c_ | seg_f_ | seg_g_;
        break;
    case '5':
        ret_val = seg_a_ | seg_c_ | seg_d_ | seg_f_ | seg_g_;
        break;
    case '6':
        ret_val = seg_a_ | seg_c_ | seg_d_ | seg_e_ | seg_f_ | seg_g_;
        break;
    case '7':
        ret_val = seg_a_ | seg_b_ | seg_c_;
        break;
    case '8':
        ret_val = seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_e_ | seg_f_ | seg_g_;
        break;
    case '9':
        ret_val = seg_a_ | seg_b_ | seg_c_ | seg_d_ | seg_f_ | seg_g_;
        break;
    case '+':
        ret_val = 0;
        break;
    case '-':
        ret_val = seg_g_;
        break;
    case '.':
        ret_val = seg_period_;
        break;
    case 'a':
    case 'A':
        ret_val = seg_a_ | seg_b_ | seg_c_ | seg_e_ | seg_f_ | seg_g_;
        break;
    case 'e':
    case 'E':
        ret_val = seg_a_ | seg_d_ | seg_e_ | seg_f_ | seg_g_;
        break;
    case 'f':
    case 'F':
        ret_val = seg_a_ | seg_e_ | seg_f_ | seg_g_;
        break;
    case 'l':
    case 'L':
        ret_val = seg_d_ | seg_e_ | seg_f_;
        break;
    case 'n':
    case 'N':
        ret_val = seg_c_ | seg_e_ | seg_g_;
        break;
    case 'p':
    case 'P':
        ret_val = seg_a_ | seg_b_ | seg_e_ | seg_f_ | seg_g_;
        break;
    case 'r':
    case 'R':
        ret_val = seg_e_ | seg_g_;
        break;

    default:
        ret_val = 0; // unknown character code
    }
    return ret_val;
}
