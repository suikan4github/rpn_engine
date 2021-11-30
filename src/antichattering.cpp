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
    switch (state_)
    {
    case ksLL: // Bottom state
        if (key_level == kklLow)
            ; // stay current state.
        else  // kklHigh
        {
            count_++;
            state_ = ksLH; // Go to intermediate state
        }
        break;
    case ksLH: // Intermediate state
        if (key_level == kklLow)
        {
            count_ = 0;
            state_ = ksLL; // Go back to the bottom state.
        }
        else // kklHigh
        {
            count_++;
            if (count_ >= lh_threashold_)
            {
                state_ = ksHH; // Go to top state
                count_ = 0;    // clear count;
                // Notify the key is H after anti chattering process.
                key_pressed_call_back_(raw_, col_);
            }
        }

        break;
    case ksHL: // Intermediate state
        if (key_level == kklLow)
        {
            count_++;
            if (count_ >= hl_threashold_)
            {
                state_ = ksLL; // Go to bottom state
                count_ = 0;    // clear count;
            }
        }
        else // kklHigh
        {
            count_ = 0;
            state_ = ksHH; // Go back to the top state.
        }
        break;
    case ksHH: // Top state
        if (key_level == kklLow)
        {
            count_++;
            state_ = ksHL; // Go to intermediate state
        }
        else  // kklHigh
            ; // stay current state.
        break;
    default:
        assert(true); // program logic error
    }
}