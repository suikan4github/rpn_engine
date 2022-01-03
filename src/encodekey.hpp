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
     * @brief Encode the key matrix data to opcode.
     *
     * @param row Row line position. 0 .. 8.
     * @param col Col line position. 0 .. 2.
     * @param is_func_key_pressed true of false.
     * @param is_hex_mode true or false.
     * @return Encoded op code result.
     * @details
     * Encode key matrix data to the opcode. Based on the row and col.
     * The LI2026A allows 9 lines row and 3 lines cols.
     *
     * The logical key map in decimal mode is as following :
     *
     * col1 | col2    | col3       | col4    | col5
     * :---:|:-------:|:----------:|:-------:|:----:
     * swap | complex | rotate pop | display | F
     * 7    |  8      |  9         | /       | del
     * 4    | 5       | 6          | *       | eex
     * 1    | 2       | 3          | -       | sqrt
     * 0    | .       | chs        | +       | enter
     *
     * The logical key map in decimal mode with F key is as following :
     *
     * col1       |    col2    | col3        | col4      | col5
     * :---------:|:----------:|:-----------:|:---------:|:----:
     * swap re im | de-complex | rotate push |  N.A.     | F
     * exp        | 10^x       | conjgate    | 1/x       | clx
     * log        | log10      | hex mode    | y^x       | pi
     * sin        | cos        | tan         | cartesian | x^2
     * asin       | acos       | atan        | polar     | undo
     *
     * The logical key map in hexadecimal mode is as following :
     *
     * col1 | col2    | col3       | col4    | col5
     * :---:|:-------:|:----------:|:-------:|:----:
     * swap | N.A.    | rotate pop | N.A.    | F
     * 7    |  8      |  9         | /       | del
     * 4    | 5       | 6          | *       |N.A.
     * 1    | 2       | 3          | -       |N.A.
     * 0    | .       | chs        | +       | enter
     *
     * The logical key map in hexadecimal mode with F key is as following :
     *
     * col1               |    col2            | col3        | col4    | col5
     * :-----------------:|:------------------:|:-----------:|:-------:|:----:
     * N.A.               | N.A.               | rotate push | N.A.    | F
     * logical shift left | logical sift right |  N.A.       | N.A.    | clx
     * e                  | f                  | dec mode    | bit and | N.A.
     * b                  | c                  | d           | bit xor | N.A.
     * a                  | N.A.               | not         | bit or  | undo

     */
    Op EncodeKey(unsigned int row, unsigned int col, bool is_func_key_pressed, bool is_hex_mode);
}