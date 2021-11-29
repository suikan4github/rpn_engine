#include "antichattering.hpp"
#include <assert.h>
rpn_engine::AntiChattering::AntiChattering(unsigned int hl_threashold_,
                                           unsigned int lh_threashold_,
                                           KeyPerssedCallBackFunction *func,
                                           unsigned int raw,
                                           unsigned int col) : state_(ksLL),
                                                               count_(0),
                                                               raw_(raw),
                                                               col_(col),
                                                               key_pressed_call_back_(func)
{
    assert(nullptr != key_pressed_call_back_);
    assert(hl_threashold_ > 0);
    assert(lh_threashold_ > 0);
}

rpn_engine::AntiChattering::~AntiChattering()
{
}

void rpn_engine::AntiChattering::Input(KeyLevel kl)
{
}