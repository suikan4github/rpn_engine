#pragma once
/**
 * @file console.hpp
 * @author Seiichi "Suikan" Horie
 * @brief
 * @version 0.1
 * @date 2021-12-31
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "stackstrategy.hpp"
#include "cmath"
#include "cstdio"

namespace rpn_engine
{
    /**
     * @brief How many digits the calculator has?
     *
     */
    const int kNumberOfDigits = 9;

    /**
     * @brief How many elements in the calculation stack.
     * @details
     * Four is the popular depth as HP Calculator.
     *
     */
    const int kDepthOfStack = 4;

    /**
     * @brief Mode of the display format.
     *
     */
    enum class DisplayMode
    {
        fixed,      ///< display as : ####.####
        scientific, ///< Display as : 0.MMMM (-)EE
        engineering ///< Same as scientific, but exponent part is an integer multiple of 3.
    };

    /**
     * @brief Element type of the stack
     *
     */
    typedef std::complex<double> StackElement;

    /**
     * @brief User interface of a calculator
     * @details
     * User interface class of the RPN calculator.
     *
     * This class receives input key by  Input() function and calculate
     * by its internal stack machine. The result is obtained by the
     *  GetText() function and  GetDecimalPointPosition() function.
     *
     * There is one internal user variable which user can store / recall.
     * The stack top is stored to the user variable when Op::sto command is given.
     * The user variable value is pushed to stack when the Op::rcl command is given.
     *
     * There are 3 display mode .
     * @li Fixed mode : The number is displayed as SNNN.NNNNN where S and N are sign and number, respectively
     * @li Scientific mode. The number is displayed as SM.MMMMSEE where S,M and E are sign, mantissa and exponent, respectively.
     * @li Engineering mode. Special scientific mode which the exponent is always integer multiple of 3.
     *
     * There is an special hex mode. The hex mode override the above display mode.
     * And it always shows number as 32bit integer. The number is shown as 8digit
     * zero filled hex signed integer.
     *
     * The result is always rounded and wrapped around to the 32bit integer.
     */
    class Console
    {
    public:
        /**
         * @brief Special value to identify the decimal point is not displayed
         *
         */
        const int kDecimalPointNotDisplayed = 256;
        /**
         * @brief Construct a new Console object
         * @param initial_string A  string displayed at first. Ignored if nullptr.
         *
         */
        Console(const char *initial_string = nullptr);

        virtual ~Console();
        /**
         * @brief Get the IsFuncKeyPressed state
         *
         * @return true Funk key is pressed. Waiting for the second key.
         * @return false Funk key is not pressed.
         * @details
         * The Func key state. This is just display of the state. Internally,
         * The Console class doesn't use this state. Just the user objects are communicating each other
         * by this status.
         *
         * For example, the input objects will inform the state the display object.
         */
        bool GetIsFuncKeyPressed();

        /**
         * @brief Get the is_hex_mode_ state
         *
         * @return true Hex mode
         * @return false Decimal mode
         */
        bool GetIsHexMode();

        /**
         * @brief Input from pad.
         *
         * @param opcode which key are pressed?
         * @details
         * The opcode must be logical key. That mean, it is free from the key matrix design and
         * chattering.
         *
         * Any value from  rpn_engine::Op type are allowed.
         *
         * IN the following description, X and Y are Stack top and Stack second, respectively.
         * Stack operation Op code :
         * @li duplicate            : Not allowed.
         * @li swap                 : Swap X and Y
         * @li rotate_pop           : Rotate stack pop-ward
         * @li rotate_push          : Rotate stack push-ward
         * @li add                  : Pop X and Y, do Y+X, then push the result.
         * @li sub                  : Pop X and Y, do Y-X, then push the result.
         * @li mul                  : Pop X and Y, do Y*X, then push the result.
         * @li div                  : Pop X and Y, do Y/X, then push the result.
         * @li neg                  : Pop X, do -X, then push the result.
         * @li inv                  : Pop X, do 1/X, then push the result.
         * @li sqrt                 : Pop X, do sqrt(X), then push the result.
         * @li square               : Pop X, do X^X, then push the result.
         * @li pi                   : push Pi.
         * @li exp                  : Pop X, do exp^X, then push the result.
         * @li log                  : Pop X, do ln(X), then push the result.
         * @li power10              : Pop X, do 10^X, then push the result.
         * @li log10                : Pop X, do log(X), then push the result.
         * @li power                : Pop X and Y, do Y^X, then push the result.
         * @li sin                  : Pop X, do sin(X), then push the result.
         * @li cos                  : Pop X, do cos(X), then push the result.
         * @li tan                  : Pop X, do tan(X), then push the result.
         * @li asin                 : Pop X, do asin(X), then push the result.
         * @li acos                 : Pop X, do acos(X), then push the result.
         * @li atan                 : Pop X, do atan(X), then push the result.
         * @li complex              : Pop X and Y, do Y+Xi, then push the result.
         * @li decomplex            : Pop X, push re(X) and then push im(X).
         * @li conjugate            : Pop X, conjugate(X) and then push the result.
         * @li to_polar             : Pop X, convert that complex number to polar cordinatin, then push the result.
         * @li to_cartesian         : Pop X, convert that complex number to cartesian cordinatin, then push the result.
         * @li swap_re_im :         : Pop X, do im(X)+re(X)i, then push the result.
         * @li bit_add              : Pop X and Y, convert them to integer, do Y+X, then push the result.
         * @li bit_sub              : Pop X and Y, convert them to integer, do Y-X, then push the result.
         * @li bit_mul              : Pop X and Y, convert them to integer, do Y*X, then push the result.
         * @li bit_div              : Pop X and Y, convert them to integer, do Y/X, then push the result.
         * @li bit_neg              : Pop X, convert it to integer, do -X, then push the result.
         * @li bit_or               : Pop X and Y, convert them to integer, do Y or X for all bits, then push the result.
         * @li bit_xor              : Pop X and Y, convert them to integer, do Y xor X for all bits, then push the result.
         * @li bit_and              : Pop X and Y, convert them to integer, do Y and X for all bits, then push the result.
         * @li logical_shift_right  : Pop X and Y, convert them to integer, do Y << X, then push the result.
         * @li logical_shift_left   : Pop X and Y, convert them to integer, do Y >> X, then push the result.
         * @li bit_not              : Pop X, convert it to integer, invert 1/0 for all bits, then push the result.
         * @li change_display       : Change the display mode. Fixed -> Scientific -> Engineering -> Fixed.
         * @li enter                : In the editing mode, terminate it and push the value. And then, set pushable mode.
         * @li clx                  : Clear the X. And set it non-pushable mode.
         * @li undo                 : Retrive the previous stack state
         * @li hex                  : Get into Hex mode.
         * @li dec                  : Leave Hex mode
         * @li sto                  : Store current X to the user variable.
         * @li rcl                  : Recall the user variable and push it.
         * @li func                 : Toggle Func mode.
         * @li nop                  : Do nothing
         *
         * Editing op code :
         * @li num_0                : In the editing mode, place "0". Outside editing mode, get into the editing mode then place.
         * @li num_1                : In the editing mode, place "1". Outside editing mode, get into the editing mode then place.
         * @li num_2                : In the editing mode, place "2". Outside editing mode, get into the editing mode then place.
         * @li num_3                : In the editing mode, place "3". Outside editing mode, get into the editing mode then place.
         * @li num_4                : In the editing mode, place "4". Outside editing mode, get into the editing mode then place.
         * @li num_5                : In the editing mode, place "5". Outside editing mode, get into the editing mode then place.
         * @li num_6                : In the editing mode, place "6". Outside editing mode, get into the editing mode then place.
         * @li num_7                : In the editing mode, place "7". Outside editing mode, get into the editing mode then place.
         * @li num_8                : In the editing mode, place "8". Outside editing mode, get into the editing mode then place.
         * @li num_9                : In the editing mode, place "9". Outside editing mode, get into the editing mode then place.
         * @li num_a                : Hex mode only. In the editing mode, place "A". Outside editing mode, get into the editing mode then place.
         * @li num_b                : Hex mode only. In the editing mode, place "B". Outside editing mode, get into the editing mode then place.
         * @li num_c                : Hex mode only. In the editing mode, place "C". Outside editing mode, get into the editing mode then place.
         * @li num_d                : Hex mode only. In the editing mode, place "D". Outside editing mode, get into the editing mode then place.
         * @li num_e                : Hex mode only. In the editing mode, place "E". Outside editing mode, get into the editing mode then place.
         * @li num_f                : Hex mode only. In the editing mode, place "F". Outside editing mode, get into the editing mode then place.
         * @li period               : In the editing mode, place decimal point.
         * @li eex                  : In the editing mode, get into the exponent input mode.
         * @li del                  : In the editing mode, delete 1 char. Outside the editing mode, work as clx op code.
         * @li chs                  : In the editing mode, toggle the sign. Outside the editing mode, work as neg op code.
         */
        void Input(rpn_engine::Op opcode);

        /**
         * @brief Get the Text representation for display.
         *
         * @param display_text Returns kNumberOfDigits character string value with null termination.
         * @details
         * The initial value of the display_text[] is ignored.
         *
         * This function stores the string to be stored. The presentation of each digits are
         * not number but character. That mean, '0' represents the 0 as number. The actual values are:
         * @li '0' .. '9'
         * @li ' '
         * @li '-'
         *
         * The display_text will not contain the decimal point. It is given by  GetDecimalPointPosition().
         *
         * Note display_text[0] and display_text[8] are left most and right most digit, respectively.
         */
        void GetText(char display_text[]);

        /**
         * @brief Get the Decimal Point Position
         *
         * @return int8_t -1 as no decimal point. 0 as right of the digit 0 ( right most)
         */
        int32_t GetDecimalPointPosition();

    private:
        StackStrategy<StackElement> engine_;
        bool is_func_key_pressed_;
        DisplayMode display_mode_;
        bool is_editing_;
        bool is_pushable_;
        int mantissa_cursor_;
        bool is_editing_float_;
        bool is_hex_mode_;
        // Needs the number of digits + one character for null termination
        char text_buffer_[kNumberOfDigits + 1];
        // 0..8 : right of digit N. kDecimalPointNotDisplayed : do not display
        int32_t decimal_point_position_;
        // store the mantissa text during editing.
        char mantissa_buffer_[kNumberOfDigits + 1];
        // store the exponent text during editing.
        char exponent_buffer_[kNumberOfDigits + 1];
        // User variable to store the data .
        StackElement user_variable_;

        /**
         * @brief Set the IsFuncKeyPressed state
         *
         * @param state new state of the key pressed state
         * @details
         * Change the internal state of "key perssed" information. THe change informaiton can be
         * ready by the  GetIsFuncKeyPressed() member function.
         */
        void SetIsFuncKeyPressed(bool state);

        /**
         * @brief Set the is_hex_mode_ state
         *
         * @param state New state of the hex mode.
         */
        void SetIsHexMode(bool state);

        /**
         * @brief Preparing non-editing opecode execution.
         * @details Flush the editing buffer to stack and make stack ready to operate.
         * set is_editing_ to false.
         * set is_pushable_ to true.
         */
        void
        PreExecutionProcess();

        /**
         * @brief Finalizing execution
         * @details Set is_pushable_ to true. And then, get the stack top and
         * convert it to text style.
         *
         * The text format follows  display_mode_. The position of decimal point
         * is stored to decimal_point_position_
         */
        void PostExecutionProcess();

        /**
         * @brief Handle opcode for "operation"
         *
         * @param opcode Instruction to execute
         * @details Handles opcode for "operation". For example, add, sub, mul...
         */
        void HandleNonEditingOp(rpn_engine::Op opcode);

        /**
         * @brief Handle opcode for number input
         *
         * @param opcode
         */
        void HandleEditingOp(rpn_engine::Op opcode);

        /**
         * @brief Convert the number of stack top to the text presentation in the fixed mode.
         * @details
         * The result is stored in the text_buffer_ and decimal_point_position_.
         * If the number is bigger than or smaller than the one which
         * 8digit fixed number can represent, the number is rendered as
         * the scientific mode.
         */
        void RenderFixedMode();

        /**
         * @brief Convert the numver of the stack top to the text presentation in the scientific mode.
         * @param engineering_mode true : engineering mode, false : scientific mode.
         */
        void RenderScientificMode(bool engineering_mode);

        /**
         * @brief Convert the number of stack top to the hex representation.
         * @details
         * Before conversion, the value is rounded to integer .
         * The value is displayed as 32bit integer in hex format.
         *
         */
        void RenderHexMode();
    };
}