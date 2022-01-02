#include "encodekey.hpp"

#include <assert.h>

namespace rpn_engine
{

    Op EncodeKey(unsigned int row, unsigned int col, bool is_func_key_pressed, bool is_hex_mode)
    {
        // parameter validation.
        assert(8 >= row); // shared with digit driver in LI2026A. 0..8
        assert(2 >= col); // 3 input from key. 0..2

        // create easy to handle key code.
        unsigned int key_code = (row << 8) | col;
        Op ret_val;

        if (is_hex_mode)
        {
            if (is_func_key_pressed)
            {
                switch (key_code)
                {
                    // Row 0
                case 0x0000: // 0
                    ret_val = Op::num_a;
                    break;
                case 0x0001: // X->M
                    // do nothing
                    break;
                case 0x0002: // CE
                    // do nothing
                    break;
                    // Row 1
                case 0x0100: // 4
                    ret_val = Op::num_e;
                    break;
                case 0x0101: // 7
                    ret_val = Op::logical_shift_left;
                    break;
                case 0x0102: // N.A.
                    assert(false);
                    break;
                    // Row 2
                case 0x0200: // 1
                    ret_val = Op::num_b;
                    break;
                case 0x0201: // 8
                    ret_val = Op::logical_shift_right;
                    break;
                case 0x0202: // CM
                    // do nothing
                    break;
                    // Row 3
                case 0x0300: // %
                    ret_val = Op::bit_not;
                    break;
                case 0x0301: // 5
                    ret_val = Op::num_f;
                    break;
                case 0x0302: // .
                    ret_val = Op::period;
                    break;
                    // Row 4
                case 0x0400: // 2
                    ret_val = Op::num_c;
                    break;
                case 0x0401: // RM
                    ret_val = Op::rotate_pop;
                    break;
                case 0x0402: // +
                    ret_val = Op::bit_or;
                    break;
                    // Row 5
                case 0x0500: // =
                    ret_val = Op::undo;
                    break;
                case 0x0501: // 9
                    // do nothing
                    break;
                case 0x0502: // C
                    ret_val = Op::clx;
                    break;
                    // Row 6
                case 0x0600: // N.A.
                    assert(false);
                    break;
                case 0x0601: // M-
                    // do nothing
                    break;
                case 0x0602: // /
                    // do nothing
                    break;
                    // Row 7
                case 0x0700: // 3
                    ret_val = Op::num_d;
                    break;
                case 0x0701: // 6
                    ret_val = Op::dec;
                    break;
                case 0x0702: // *
                    ret_val = Op::bit_and;
                    break;
                    // Row 8
                case 0x0800: // sqrt
                    // do nothing
                    break;
                case 0x0801: // M+
                    ret_val = Op::func;
                    break;
                case 0x0802: // -
                    ret_val = Op::bit_xor;
                    break;
                default:
                    assert(false); // logic error. Must not come here
                }
            }
            else // not func key pressed
            {
                switch (key_code)
                {
                    // Row 0
                case 0x0000: // 0
                    ret_val = Op::num_0;
                    break;
                case 0x0001: // X->M
                    ret_val = Op::swap;
                    break;
                case 0x0002: // CE
                    // do nothing
                    break;
                    // Row 1
                case 0x0100: // 4
                    ret_val = Op::num_4;
                    break;
                case 0x0101: // 7
                    ret_val = Op::num_7;
                    break;
                case 0x0102: // N.A.
                    assert(false);
                    break;
                    // Row 2
                case 0x0200: // 1
                    ret_val = Op::num_1;
                    break;
                case 0x0201: // 8
                    ret_val = Op::num_8;
                    break;
                case 0x0202: // CM
                    // do nothing
                    break;
                    // Row 3
                case 0x0300: // %
                    ret_val = Op::bit_neg;
                    break;
                case 0x0301: // 5
                    ret_val = Op::num_5;
                    break;
                case 0x0302: // .
                    ret_val = Op::period;
                    break;
                    // Row 4
                case 0x0400: // 2
                    ret_val = Op::num_2;
                    break;
                case 0x0401: // RM
                    ret_val = Op::rotate_pop;
                    break;
                case 0x0402: // +
                    ret_val = Op::bit_add;
                    break;
                    // Row 5
                case 0x0500: // =
                    ret_val = Op::enter;
                    break;
                case 0x0501: // 9
                    ret_val = Op::num_9;
                    break;
                case 0x0502: // C
                    ret_val = Op::del;
                    break;
                    // Row 6
                case 0x0600: // N.A.
                    assert(false);
                    break;
                case 0x0601: // M-
                             // do nothing
                    break;
                case 0x0602: // /
                    ret_val = Op::bit_div;
                    break;
                    // Row 7
                case 0x0700: // 3
                    ret_val = Op::num_3;
                    break;
                case 0x0701: // 6
                    ret_val = Op::num_6;
                    break;
                case 0x0702: // *
                    ret_val = Op::bit_mul;
                    break;
                    // Row 8
                case 0x0800: // sqrt
                    // do nothing
                    break;
                case 0x0801: // M+
                    ret_val = Op::func;
                    break;
                case 0x0802: // -
                    ret_val = Op::bit_sub;
                    break;
                default:
                    assert(false); // logic error. Must not come here
                }
            }
        }
        else // not hex mode
        {
            if (is_func_key_pressed)
            {
                switch (key_code)
                {
                    // Row 0
                case 0x0000: // 0
                    ret_val = Op::asin;
                    break;
                case 0x0001: // X->M
                    ret_val = Op::swap_re_im;
                    break;
                case 0x0002: // CE
                    ret_val = Op::pi;
                    break;
                    // Row 1
                case 0x0100: // 4
                    ret_val = Op::log;
                    break;
                case 0x0101: // 7
                    ret_val = Op::exp;
                    break;
                case 0x0102: // N.A.
                    assert(false);
                    break;
                    // Row 2
                case 0x0200: // 1
                    ret_val = Op::sin;
                    break;
                case 0x0201: // 8
                    ret_val = Op::power10;
                    break;
                case 0x0202: // CM
                    ret_val = Op::decomplex;
                    break;
                    // Row 3
                case 0x0300: // %
                    ret_val = Op::atan;
                    break;
                case 0x0301: // 5
                    ret_val = Op::log10;
                    break;
                case 0x0302: // .
                    ret_val = Op::acos;
                    break;
                    // Row 4
                case 0x0400: // 2
                    ret_val = Op::cos;
                    break;
                case 0x0401: // RM
                    ret_val = Op::rotate_push;
                    break;
                case 0x0402: // +
                    ret_val = Op::to_polar;
                    break;
                    // Row 5
                case 0x0500: // =
                    ret_val = Op::undo;
                    break;
                case 0x0501: // 9
                    ret_val = Op::conjugate;
                    break;
                case 0x0502: // C
                    ret_val = Op::clx;
                    break;
                    // Row 6
                case 0x0600: // N.A.
                    assert(false);
                    break;
                case 0x0601: // M-
                    // do nothing
                    break;
                case 0x0602: // /
                    ret_val = Op::inv;
                    break;
                    // Row 7
                case 0x0700: // 3
                    ret_val = Op::tan;
                    break;
                case 0x0701: // 6
                    ret_val = Op::hex;
                    break;
                case 0x0702: // *
                    ret_val = Op::power;
                    break;
                    // Row 8
                case 0x0800: // sqrt
                    ret_val = Op::square;
                    break;
                case 0x0801: // M+
                    ret_val = Op::func;
                    break;
                case 0x0802: // -
                    ret_val = Op::to_cartesian;
                    break;
                default:
                    assert(false); // logic error. Must not come here
                }
            }
            else // not func key pressed
            {
                switch (key_code)
                {
                    // Row 0
                case 0x0000: // 0
                    ret_val = Op::num_0;
                    break;
                case 0x0001: // X->M
                    ret_val = Op::swap;
                    break;
                case 0x0002: // CE
                    ret_val = Op::eex;
                    break;
                    // Row 1
                case 0x0100: // 4
                    ret_val = Op::num_4;
                    break;
                case 0x0101: // 7
                    ret_val = Op::num_7;
                    break;
                case 0x0102: // N.A.
                    assert(false);
                    break;
                    // Row 2
                case 0x0200: // 1
                    ret_val = Op::num_1;
                    break;
                case 0x0201: // 8
                    ret_val = Op::num_8;
                    break;
                case 0x0202: // CM
                    ret_val = Op::complex;
                    break;
                    // Row 3
                case 0x0300: // %
                    ret_val = Op::chs;
                    break;
                case 0x0301: // 5
                    ret_val = Op::num_5;
                    break;
                case 0x0302: // .
                    ret_val = Op::period;
                    break;
                    // Row 4
                case 0x0400: // 2
                    ret_val = Op::num_2;
                    break;
                case 0x0401: // RM
                    ret_val = Op::rotate_pop;
                    break;
                case 0x0402: // +
                    ret_val = Op::add;
                    break;
                    // Row 5
                case 0x0500: // =
                    ret_val = Op::enter;
                    break;
                case 0x0501: // 9
                    ret_val = Op::num_9;
                    break;
                case 0x0502: // C
                    ret_val = Op::del;
                    break;
                    // Row 6
                case 0x0600: // N.A.
                    assert(false);
                    break;
                case 0x0601: // M-
                    ret_val = Op::change_display;
                    break;
                case 0x0602: // /
                    ret_val = Op::div;
                    break;
                    // Row 7
                case 0x0700: // 3
                    ret_val = Op::num_3;
                    break;
                case 0x0701: // 6
                    ret_val = Op::num_6;
                    break;
                case 0x0702: // *
                    ret_val = Op::mul;
                    break;
                    // Row 8
                case 0x0800: // sqrt
                    ret_val = Op::sqrt;
                    break;
                case 0x0801: // M+
                    ret_val = Op::func;
                    break;
                case 0x0802: // -
                    ret_val = Op::sub;
                    break;
                default:
                    assert(false); // logic error. Must not come here
                }
            }
        }
        return ret_val;
    }
}
