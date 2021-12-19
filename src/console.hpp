
#include "stackstrategy.hpp"
#include "cmath"

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
     * @brief User interface of a calculator
     *
     */
    class Console
    {
    public:
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
         * @param key which key are pressed?
         * @details
         * The key must be logical key. That mean, it is free from the key matrix design and
         * chattering.
         *
         * Any value from @ref rpn_engine::Op type are allowed.
         */
        void Input(rpn_engine::Op key);

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
        int8_t GetDecimalPointPosition();

    private:
        FRIEND_TEST(Console, ModeTest);

        StackStrategy<std::complex<double>> engine_;
        bool is_func_key_pressed_;
        DisplayMode display_mode_;
        bool is_editing_;
        bool is_pushable_;
        // Needs the number of digits + one character for null termination
        char text_buffer_[kNumberOfDigits + 1];
    };
}