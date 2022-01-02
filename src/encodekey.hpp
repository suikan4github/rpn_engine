#pragma once
/**
 * @file encodekey.hpp
 * @author Seiichi "Suikan" Horie
 * @brief
 * @version 0.1
 * @date 2022-01-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "stackstrategy.hpp"

namespace rpn_engine
{
    /**
     * @brief
     *
     * @param row
     * @param col
     * @param is_func_key_pressed
     * @param is_hex_mode
     * @return Op
     */
    Op EncodeKey(unsigned int row, unsigned int col, bool is_func_key_pressed, bool is_hex_mode);
}