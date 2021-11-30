#include "antichattering.hpp"
#include <assert.h>
rpn_engine::AntiChattering::AntiChattering(unsigned int hl_threashold,
                                           unsigned int lh_threashold,
                                           KeyPerssedCallBackFunction *func,
                                           unsigned int raw,
                                           unsigned int col) : state_(ksLL),
                                                               count_(0),
                                                               key_pressed_call_back_(func),
                                                               raw_(raw),
                                                               col_(col),
                                                               hl_threashold_(hl_threashold),
                                                               lh_threashold_(lh_threashold)
{
    assert(nullptr != key_pressed_call_back_);
    assert(hl_threashold_ > 1);
    assert(lh_threashold_ > 1);
}

rpn_engine::AntiChattering::~AntiChattering()
{
}

#include <iostream>
void rpn_engine::AntiChattering::Input(KeyLevel const key_level)
{
    // Actual implementation of internal state machine
    switch (state_)
    {
        // In the LL state, needs continuous lh_threshold_ "H" to transit to HH state.
    case ksLL: // Bottom state
        if (key_level == kklLow)
            count_ = 0; // Clear the continuous "H" count
        else            // kklHigh
        {
            count_++; // count how many continuous "H" came
            if (count_ >= lh_threashold_)
            {
                state_ = ksHH; // Transit to HH state
                count_ = 0;    // clear count;
                // Notify the key is H after anti chattering process.
                key_pressed_call_back_(raw_, col_);
            }
        }
        break;
        // In the HH state, needs continuous hl_threshold_ "L" to transit to LL state.
    case ksHH: // Top state
        if (key_level == kklLow)
        {
            count_++; // count how many continuous "L" came
            if (count_ >= hl_threashold_)
            {
                state_ = ksLL; // Transit to LL state
                count_ = 0;    // clear count;
            }
        }
        else // kklHigh
        {
            count_ = 0; // Clear the continuous "L" count
        }
        break;
    default:
        assert(true); // program logic error
    }
}