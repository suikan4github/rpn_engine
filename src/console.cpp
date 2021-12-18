#include "console.hpp"

rpn_engine::Console::Console() : engine_(StackStrategy<std::complex<double>>(4)),
                                 is_func_key_pressed_(false),
                                 display_mode_(DisplayMode::fixed)
{
}

rpn_engine::Console::~Console()
{
}

bool rpn_engine::Console::GetIsFuncKeyPressed()
{
    return is_func_key_pressed_;
}

void rpn_engine::Console::SetIsFuncKeyPressed(bool state)
{
    is_func_key_pressed_ = state;
}

void rpn_engine::Console::Input(Op key)
{
    switch (key)
    {
    case Op::change_display:
        if (display_mode_ == DisplayMode::fixed)
            display_mode_ = DisplayMode::scientific;
        else if (display_mode_ == DisplayMode::scientific)
            display_mode_ = DisplayMode::engineering;
        else
            display_mode_ = DisplayMode::fixed;
        break;
    default:
        assert(false);
    }
}
