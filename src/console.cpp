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

void rpn_engine::Console::RenderFixedMode()
{
    //    const double kBoundaryOfScientific = 99999999.5; // 8 digits of 9 and rounding bias.
    const double kBoundaryOfScientific = 100000000; // 8 digits of 9 + one
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
        int int_value = 0;

        if (int(value + 0.5) > kBoundaryOfScientific)
            ; // scientific mode
        else if (kBoundaryOfScientific > (value * 1e7 + 0.5))
        {
            exponent = 7;
            int_value = value * 1e7 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e6 + 0.5))
        {
            exponent = 6;
            int_value = value * 1e6 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e5 + 0.5))
        {
            exponent = 5;
            int_value = value * 1e5 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e4 + 0.5))
        {
            exponent = 4;
            int_value = value * 1e4 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e3 + 0.5))
        {
            exponent = 3;
            int_value = value * 1e3 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e2 + 0.5))
        {
            exponent = 2;
            int_value = value * 1e2 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e1 + 0.5))
        {
            exponent = 1;
            int_value = value * 1e1 + 0.5;
        }
        else if (kBoundaryOfScientific > (value * 1e0 + 0.5))
        {
            exponent = 0;
            int_value = value * 1e0 + 0.5;
        }

        // text_buffer_[0] is space for sign
        std::sprintf(&text_buffer_[1], "%08d", int_value);
        // set sign or blank
        text_buffer_[0] = minus ? '-' : ' ';
        decimal_point_position_ = exponent;
    }
}

void rpn_engine::Console::RenderScientificMode()
{
}