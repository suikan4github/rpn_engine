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
        engine_.Pop(); // discard the stack top to simulate overwriting the stack top.
        engine_.Push(value);
        is_editing_ = false; // ed of editing
    }
}

void rpn_engine::Console::PostExecutionProcess()
{
    is_pushable_ = true;
}

void rpn_engine::Console::HandleNonEditingOp(rpn_engine::Op opcode)
{
    PreExecutionProcess();

    switch (opcode)
    {
    case Op::change_display:

        if (display_mode_ == DisplayMode::fixed)
            display_mode_ = DisplayMode::scientific;
        else if (display_mode_ == DisplayMode::scientific)
            display_mode_ = DisplayMode::engineering;
        else
            display_mode_ = DisplayMode::fixed;

        break;
    case Op::pi:
        engine_.Operation(opcode);
        break;
    default:
        assert(false);
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
