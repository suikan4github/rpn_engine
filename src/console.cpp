#include "console.hpp"
#include <iostream>

using rpn_engine::Op;

rpn_engine::Console::Console() : engine_(StackStrategy<std::complex<double>>(kDepthOfStack)),
                                 is_func_key_pressed_(false),
                                 display_mode_(DisplayMode::fixed),
                                 is_editing_(false),
                                 is_pushable_(false)
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

void rpn_engine::Console::PreExecutionProcess()
{
    StackElement value;

    if (is_editing_) // if editing, convert text to value and set it to stack.
    {
        assert(false); // to do : Create value to push.
        engine_.Push(value);
        is_editing_ = false; // ed of editing
        is_pushable_ = true; // after editing, stack is pushable.
    }
}

void rpn_engine::Console::PostExecutionProcess()
{
    is_pushable_ = true;

    switch (display_mode_)
    {
    case rpn_engine::DisplayMode::fixed:
        RenderFixedMode();
        break;
    case rpn_engine::DisplayMode::scientific:
        break;
    case rpn_engine::DisplayMode::engineering:
        break;
    default:
        assert(false);
    }
}

void rpn_engine::Console::HandleNonEditingOp(rpn_engine::Op opcode)
{
    PreExecutionProcess();

    switch (opcode)
    {
    case Op::change_display:
        // Rotate the display mode for each time "display_mode" key pushed.
        if (display_mode_ == DisplayMode::fixed)
            display_mode_ = DisplayMode::scientific;
        else if (display_mode_ == DisplayMode::scientific)
            display_mode_ = DisplayMode::engineering;
        else
            display_mode_ = DisplayMode::fixed;

        break;
    case Op::pi:
        if (!is_pushable_)         // If stack is not pushbale,
            engine_.Pop();         // discard stack top.
        engine_.Operation(opcode); // And then, push Pi
        break;
    default:
        engine_.Operation(opcode);
        break;
    }

    PostExecutionProcess();
}

void rpn_engine::Console::HandleEditingOp(rpn_engine::Op opcode)
{
}

void rpn_engine::Console::Input(Op opcode)
{
    if ((Op::undo >= opcode) && (opcode >= Op::duplicate))
        HandleNonEditingOp(opcode);
    else
        HandleEditingOp(opcode);
    ;
}

#include <iomanip>
void rpn_engine::Console::RenderFixedMode()
{
    const double kBoundaryOfScientific = 99999999.5; // 8 digits of 9 and rounding bias.
    // Get top of stack
    StackElement x = engine_.Get(0);
    // We display only real part.
    auto value = x.real();
    int exponent; // The display value in the text_buffer_[] is integer. So, we need exponent.

    // record the sign of value.
    bool minus = value < 0.0;
    if (minus)
        value = -value;

    if (value >= kBoundaryOfScientific) // if too large,
        assert(false);                  // display in the scientific format
    else
    {
        // extract the exponent.
        if (value >= 9999999.95)
            exponent = 0;
        else if (value >= 999999.995)
            exponent = 1;
        else if (value >= 99999.9995)
            exponent = 2;
        else if (value >= 9999.99995)
            exponent = 3;
        else if (value >= 999.999995)
            exponent = 4;
        else if (value >= 99.9999995)
            exponent = 5;
        else if (value >= 9.99999995)
            exponent = 6;
        else if (value >= 0.00000005)
            exponent = 7;
        else
            exponent = 7; // display in the scientific format

        // Let's normalize
        for (int i = 0; i < exponent; i++)
            value *= 10;

        // round it
        int int_value = value + 0.5;

        // text_buffer_[0] is space for sign
        std::sprintf(&text_buffer_[1], "%08d", int_value);
        // set sign or blank
        text_buffer_[0] = minus ? '-' : ' ';
        decimal_point_position_ = exponent;
    }
}