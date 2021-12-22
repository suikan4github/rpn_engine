#include "console.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

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
        RenderScientificMode(false);
        break;
    case rpn_engine::DisplayMode::engineering:
        RenderScientificMode(true);
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
        RenderScientificMode(false);    // display in the scientific format
    else if (5e-8 > value)              // if too small
        RenderScientificMode(false);    // display in the scientific format
    else
    {
        int int_value = 0;

        if (int(value + 0.5) > kBoundaryOfScientific)
            RenderScientificMode(false); // display in the scientific format
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
        else
            assert(false);

        // text_buffer_[0] is space for sign
        std::sprintf(&text_buffer_[1], "%08d", int_value);
        // set sign or blank
        text_buffer_[0] = minus ? '-' : ' ';
        decimal_point_position_ = exponent;
    }
}

void rpn_engine::Console::RenderScientificMode(bool engineering_mode)
{
    const int kBufferSize = 20;
    const int kExponentPos = 10;
    const char kFormatSpec[] = "%+-15.7e";
    const char kExponentMark = 'e';
    const char kDisplayFormatSpec[] = "%+03d";
    // temporally rendering area
    char buffer[kBufferSize];

    // Get top of stack
    StackElement x = engine_.Get(0);
    // We display only real part.
    auto value = x.real();

    // Convert to a text format as #.#######e#####
    std::snprintf(buffer, kBufferSize, kFormatSpec, value);
    // Check wether the format is OK.
    assert(buffer[kExponentPos] == kExponentMark);

    // Get a exponent part of #.#######e#####
    int exponent = std::atoi(&buffer[kExponentPos + 1]);

    decimal_point_position_ = 7; // right of the upper most digit

    if (exponent > 99) // if the number exceed the max display number
        if (value > 0)
            std::strcpy(text_buffer_, "+99999+99"); // sign of max number
        else
            std::strcpy(text_buffer_, "-99999+99"); // sign of max number

    else if (-99 > exponent)                    // if the number is lower than the min display number
        std::strcpy(text_buffer_, " 00000000"); // flash to zero
    else                                        // the number is in the normal range
    {
        int i = 0;
        int j = 0;
        text_buffer_[i++] = buffer[j++]; // Sign
        text_buffer_[i++] = buffer[j++]; // upper most
        j++;                             // skip decimal point
        text_buffer_[i++] = buffer[j++]; // 2nd upper digit
        text_buffer_[i++] = buffer[j++]; // 3rd upper digit
        text_buffer_[i++] = buffer[j++]; // 4th upper digit
        text_buffer_[i++] = buffer[j++]; // 5th upper digit

        if (engineering_mode)
        {
            int old_exponent = exponent;
            // align exponent as integer multiple of 3.
            exponent /= 3;
            exponent *= 3;
            // calculate the offset from the engineering exponent.
            int offset_exponent = old_exponent - exponent;

            // adjust the decimal point for engineering point.
            if (0 > offset_exponent) // that means the exponent is minus and offset is not zero
            {
                exponent -= 3;                         // this is required only when the old_exponent is not the integer multiple of 3
                offset_exponent = 3 + offset_exponent; // adjust for the minus exponent
            }
            decimal_point_position_ -= offset_exponent;
        }

        std::snprintf(&text_buffer_[i], 4, kDisplayFormatSpec, exponent);
    }
}