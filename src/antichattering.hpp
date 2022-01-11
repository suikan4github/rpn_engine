#pragma once
/**
 * @file antichattering.hpp
 * @author Seiichi "Suikan" Horie
 * @brief Automaton to kill the chattering of the switch.
 * @version 0.1
 * @date 2021-11-29
 *
 * @copyright Copyright (c) 2021
 *
 */

namespace rpn_engine
{
    /**
     * @brief Key signal level for  AntiChattering class.
     *
     */
    enum class KeyLevel
    {
        low, ///< Key signal is Low.
        high ///< Key signal is high.
    };

    /**
     * @brief Call back function for  AntiChattering
     *
     * @param raw Raw postion of key matrix
     * @param col Col postion of key matrix
     *
     */
    typedef void KeyPerssedCallBackFunction(unsigned raw, unsigned col);

    /**
     * @brief Anti Chattering state machine .
     * @details
     * This class clean up the chattering singal from switch / key.
     *
     * The  Input() member function assumes it is invoked periodically with
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
         * @brief Input to the state machine
         *
         * @param key_level KeyLevel::high or kksLow
         * @details
         * Drives internal state machine. This member function have to be called
         * periodically.
         *
         * When the internal state machine tansits from L to H, the
         * call buck function registered by the constructor will be called.
         */
        void Input(KeyLevel const key_level);

    private:
        enum State
        {
            ksLL, ///< Low state.
            ksHH  ///< High state
        };

        State state_;        // Internal state machine
        unsigned int count_; // continuous count of same key input

        KeyPerssedCallBackFunction *key_pressed_call_back_;
        unsigned int const raw_; // raw in the key matrix
        unsigned int const col_; // col in the key matrix
                                 // Invoked when state transit to ksHH

        unsigned int const hl_threashold_; // How many continuous L is needed to transit from H to L
        unsigned int const lh_threashold_; // How many continuous L is needed to transit from L to H
    };
}