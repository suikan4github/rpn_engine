/**
 * @file antichattering.hpp
 * @author your name (you@domain.com)
 * @brief Automaton to kill the chattering of the switch.
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

namespace rpn_engine
{
    enum KeyLevel
    {
        kklLow,
        kklHigh
    };
    typedef void KeyPerssedCallBackFunction(unsigned raw, unsigned col);

    /**
     * @brief Anti Chattering state machine .
     * @details
     * This class clean up the chattering singal from switch / key. 
     * 
     * The @Input() member function assumes it is invoked periodically with 
     * the level of key input. For each time invoked, the internal state 
     * machine changes its state by the input key. And then, when the 
     * internal state machine recognizes the "Key pressed", this class
     * calls the call back function which is specified by the parameter of 
     * constructor.  
     */
    class AntiChattering
    {
    public:
        /**
         * @brief Construct a new Anti Chattering object
         * @param hl_threashold The parameter represents how many continuous L is need to tansit from H to L. Must be greater than 1. 
         * @param lh_threashold  The parameter represents how many continuous L is need to tansit from H to L. Must be greater than 1. 
         * @param func The call back function. Invoked when the internal state machine recognize L -> H.
         * @param raw The raw # of key matrix. Passed to the parameter of func( raw, col)
         * @param col The col # of key matrix. Passed to the parameter of func( raw, col)
         */
        AntiChattering(
            unsigned int hl_threashold,
            unsigned int lh_threashold,
            KeyPerssedCallBackFunction *func,
            unsigned int raw,
            unsigned int col);
        virtual ~AntiChattering();

        /**
         * @brief 
         * 
         * @param raw 
         * @param col 
         */
        void Input(KeyLevel const key_level);

    private:
        enum State
        {
            ksLL, ///< Low state.
            ksLH, ///< Low state but got "H" input. next continousl lh_threashold "H" will make transition to HH.
            ksHL, ///< High state but got "L" input. next continousl hl_threashold "L" will make transition to LL.
            ksHH  ///< High state
        };

        State state_;
        unsigned int count_; // continuous count of same key input

        KeyPerssedCallBackFunction *key_pressed_call_back_;
        unsigned int const raw_; // raw in the key matrix
        unsigned int const col_; // col in the key matrix
                                 // Invoked when state transit to ksHH

        unsigned int const hl_threashold_;
        unsigned int const lh_threashold_;
    };
}