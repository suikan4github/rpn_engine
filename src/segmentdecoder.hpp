#pragma once
/**
 * @file segmentdecoder.hpp
 * @author Seiichi "Suikan" Horie
 * @brief
 * @version 0.1
 * @date 2021-12-31
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdint.h>

namespace rpn_engine
{

    /**
     * @brief Convert from an ASCII character to the segment bit map.
     * @details
     * Convert given character to the 7 segments display. The 7 segments are
     * represented by a 7 bits bit map.
     *
     * The 7 segment display has segment named a, b, ... g. These segments are
     * allocated as below :
     * @code
     *  ----- a -----
     * |             |
     * f             b
     * |             |
     *  ----- g -----
     * |             |
     * e             c
     * |             |
     *  ----- d -----
     * @endcode
     *
     * This class decode the given character as bit map for this 7bit segment.
     * To allow the flexible bit allocation, user can specify the bit position of
     * each segment by the constructor.
     *
     */
    class SegmentDecoder
    {
    public:
        /**
         * @brief Construct a new Segment Decoder object
         *
         * @param seg_a Bit map of the segment a.
         * @param seg_b Bit map of the segment b.
         * @param seg_c Bit map of the segment c.
         * @param seg_d Bit map of the segment d.
         * @param seg_e Bit map of the segment e.
         * @param seg_f Bit map of the segment f.
         * @param seg_g Bit map of the segment g.
         * @param seg_period  Bit map of the segment DP.
         * @details
         * Each parameter receives the dedicated bit map for the segments.
         * This allow user customize the decoder for his/her own display.
         *
         * The bit map must not be overwrapped. It triggers assertins.
         *
         */
        SegmentDecoder(uint8_t seg_a = 0x01,
                       uint8_t seg_b = 0x02,
                       uint8_t seg_c = 0x04,
                       uint8_t seg_d = 0x08,
                       uint8_t seg_e = 0x10,
                       uint8_t seg_f = 0x20,
                       uint8_t seg_g = 0x40,
                       uint8_t seg_period = 0x80);
        SegmentDecoder() = delete; // Forbid the default constructor

        /**
         * @brief Decoding character.
         *
         * @param c Character to decdoe.
         * @return uint8_t Decoded 7 segment ( +DP) display pattern.
         * @details Unknown character is converted to a space.
         */
        uint8_t decode(char c);

    private:
        const uint8_t seg_a_;
        const uint8_t seg_b_;
        const uint8_t seg_c_;
        const uint8_t seg_d_;
        const uint8_t seg_e_;
        const uint8_t seg_f_;
        const uint8_t seg_g_;
        const uint8_t seg_period_;
    };

}