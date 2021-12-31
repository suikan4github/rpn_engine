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
     * @brief
     * @details
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
     */
    class SegmentDecoder
    {
    public:
        /**
         * @brief Construct a new Segment Decoder object
         *
         * @param seg_a
         * @param seg_b
         * @param seg_c
         * @param seg_d
         * @param seg_e
         * @param seg_f
         * @param seg_g
         * @param seg_period
         *
         */
        SegmentDecoder(uint8_t seg_a, uint8_t seg_b, uint8_t seg_c, uint8_t seg_d, uint8_t seg_e, uint8_t seg_f, uint8_t seg_g, uint8_t seg_period);
        SegmentDecoder() = delete; // Forbid the default constructor

        /**
         * @brief
         *
         * @param c
         * @return uint8_t
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