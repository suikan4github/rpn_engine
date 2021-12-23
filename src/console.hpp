
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
     *
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
         *
         */
        Console();

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
         * @brief Set the IsFuncKeyPressed state
         *
         * @param state new state of the key pressed state
         * @details
         * Change the internal state of "key perssed" information. THe change informaiton can be
         * ready by the @ref GetIsFuncKeyPressed() member function.
         */
        void SetIsFuncKeyPressed(bool state);

        /**
         * @brief Input from pad.
         *
         * @param opcode which key are pressed?
         * @details
         * The opcode must be logical key. That mean, it is free from the key matrix design and
         * chattering.
         *
         * Any value from @ref rpn_engine::Op type are allowed.
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
         * The display_text will not contain the decimal point. It is given by @ref GetDecimalPointPosition().
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
        FRIEND_TEST(Console, Mode);
        FRIEND_TEST(Console, PrimitivePi);
        FRIEND_TEST(Console, FixedMode);
        FRIEND_TEST(Console, ScientificMode);
        FRIEND_TEST(Console, EngineeringMode);

        StackStrategy<StackElement> engine_;
        bool is_func_key_pressed_;
        DisplayMode display_mode_;
        bool is_editing_;
        bool is_pushable_;
        int mantissa_cursor_;
        bool is_editing_float_;
        // Needs the number of digits + one character for null termination
        char text_buffer_[kNumberOfDigits + 1];
        // 0..8 : right of digit N. kDecimalPointNotDisplayed : do not display
        int32_t decimal_point_position_;
        // store the mantissa text during editing.
        char mantissa_buffer_[kNumberOfDigits + 1];
        // store the exponent text during editing.
        char exponent_buffer_[kNumberOfDigits + 1];

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
    };
}