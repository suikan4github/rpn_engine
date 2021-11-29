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

#include <functional>

namespace rpn_engine
{
    enum KeyLevel
    {
        kklL,
        kklH
    };

    typedef std::function<void(unsigned raw, unsigned col)> KeyPerssedCallBackFunction;

    class AntiChattering
    {
    public:
        /**
         * @brief Construct a new Anti Chattering object
         * @param hl_threashold
         * @param lh_threashold
         * @param func
         * @param raw 
         * @param col 
         */
        AntiChattering(
            unsigned int hl_threashold_,
            unsigned int lh_threashold_,
            KeyPerssedCallBackFunction func,
            unsigned int raw,
            unsigned int col);
        virtual ~AntiChattering();

        /**
         * @brief 
         * 
         * @param raw 
         * @param col 
         */
        void Input(KeyLevel kl);

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

        unsigned int raw_; // raw in the key matrix
        unsigned int col_; // col in the key matrix
                           // Invoked when state transit to ksHH
        KeyPerssedCallBackFunction key_pressed_call_back_;
    };
}