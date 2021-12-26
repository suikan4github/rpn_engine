#include "console.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <type_traits>

using rpn_engine::Op;

static const int kFullMantissa = 9;
static const int kUpperMostDigit = 7;

rpn_engine::Console::Console() : engine_(StackStrategy<std::complex<double>>(kDepthOfStack)),
                                 is_func_key_pressed_(false),
                                 display_mode_(DisplayMode::fixed),
                                 is_editing_(false),
                                 is_pushable_(false),
                                 mantissa_cursor_(1),
                                 is_editing_float_(false),
                                 is_hex_mode_(false)
{
    PostExecutionProcess();
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

bool rpn_engine::Console::GetIsHexMode()
{
    return is_hex_mode_;
}

void rpn_engine::Console::SetIsHexMode(bool state)
{
    is_hex_mode_ = state;
}

void rpn_engine::Console::GetText(char display_text[])
{
    std::strcpy(display_text, text_buffer_);
}

int32_t rpn_engine::Console::GetDecimalPointPosition()
{
    return decimal_point_position_;
}

void rpn_engine::Console::PreExecutionProcess()
{
    StackElement value;

    if (is_editing_) // if editing, convert text to value and set it to stack.
    {
        if (is_hex_mode_)
        {
            int32_t hexvalue;
            std::sscanf(mantissa_buffer_, "%X", &hexvalue); // Convert nominal literal to int32_t.
            value = hexvalue;
        }
        else
        {

            double mantissa;
            int exponent = 0;
            char temp_buffer[12];

            if (is_editing_float_)
            {
                std::sscanf(exponent_buffer_, "%d", &exponent);
            }

            // Convert the mantissa_buffer and decimal point to the one "nominal" literal with decimal point
            // The format of mantissa is "smmmmmmmm" where s is sign, m is digits.
            // We want to nominal format "smmm.mmmmm" where "." is decimal point The decimal point position
            // is calculated from variable decimal_point_position_
            int current_decimal_position = 8;  // initial point is left most ( sign )
            int current_destination_index = 0; // initial index of destination string.
            // from lest most to right most ( 9 digits)
            for (int index = 0; index < 9; index++)
            {
                temp_buffer[current_destination_index++] = mantissa_buffer_[index]; // copy one digit

                if (current_decimal_position == decimal_point_position_) // If decimal point is needed
                    temp_buffer[current_destination_index++] = '.';      // add point
                current_decimal_position--;                              // Forwarding pointer
            }

            temp_buffer[current_destination_index] = '\0'; // terminate the string.

            std::sscanf(temp_buffer, "%lf", &mantissa); // Convert nominal literal to float.
            value = mantissa * std::pow(10, exponent);  // adjust exponent

        } // ? hexmode
        engine_.Push(value);
        is_editing_ = false; // end of editing
        is_pushable_ = true; // after editing, stack is pushable.
    }                        // ? editing
}

void rpn_engine::Console::PostExecutionProcess()
{
    if (is_hex_mode_) // if hex mode
        RenderHexMode();
    else // decimal mode
    {
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
            assert(false); // program logic error
        }
    } // hex / decimal mode
}

void rpn_engine::Console::HandleNonEditingOp(rpn_engine::Op opcode)
{
    PreExecutionProcess();

    switch (opcode)
    {
    case Op::change_display:
        // Display mode rotates fixed->scientific->engineering->fixed for each time
        // change_display command is issued.
        if (display_mode_ == DisplayMode::fixed)
            display_mode_ = DisplayMode::scientific;
        else if (display_mode_ == DisplayMode::scientific)
            display_mode_ = DisplayMode::engineering;
        else
            display_mode_ = DisplayMode::fixed;
        is_pushable_ = true;
        break;
    case Op::pi:
        if (!is_pushable_)         // If stack is not pushbale,
            engine_.Pop();         // discard stack top.
        engine_.Operation(opcode); // And then, push Pi
        is_pushable_ = true;
        break;
    case Op::clx:
        engine_.SetX(0.0);
        is_pushable_ = false; // Only clx and enter makes NOT pushable
        break;
    case Op::enter:
        engine_.Operation(Op::duplicate);
        is_pushable_ = false; // Only clx and enter makes NOT pushable
        break;
    case Op::hex: // change to hex mode
        SetIsHexMode(true);
        is_pushable_ = true;
        break;
    case Op::dec: // change to decimal mode
        SetIsHexMode(false);
        is_pushable_ = true;
        break;
    default: // all other opcode should be passed through to the engine.
        engine_.Operation(opcode);
        is_pushable_ = true;
        break;
    }

    PostExecutionProcess();
}

void rpn_engine::Console::HandleEditingOp(rpn_engine::Op opcode)
{

    if (opcode == Op::chs && !is_editing_) // The chs during non editing mode
    {
        if (is_hex_mode_)
            HandleNonEditingOp(Op ::bit_neg); // is translated as bit negate operation
        else
            HandleNonEditingOp(Op ::neg); // is translated as negate operation
    }
    else
    {

        if (!is_editing_) // if not editing
        {                 // do preparation.
            is_editing_float_ = false;
            mantissa_cursor_ = 1;                                // digit 7
            std::strcpy(mantissa_buffer_, " 0       ");          // fill by 9 spaces.Sign and 8 digits
            std::strcpy(exponent_buffer_, " 00");                // fill by 3 space. Sing and 2 digits
            decimal_point_position_ = kDecimalPointNotDisplayed; // -1 means, do not display the decimal point.

            is_editing_ = true;
        }
        switch (opcode)
        {
        case Op::num_0:
        case Op::num_1:
        case Op::num_2:
        case Op::num_3:
        case Op::num_4:
        case Op::num_5:
        case Op::num_6:
        case Op::num_7:
        case Op::num_8:
        case Op::num_9:
            if (is_editing_float_)
            {
                exponent_buffer_[1] = exponent_buffer_[2]; // shift up the exponent digit;
                // calculate the character to put to the right most digit of exponent.
                exponent_buffer_[2] = static_cast<std::underlying_type<Op>::type>(opcode) -
                                      static_cast<std::underlying_type<Op>::type>(Op::num_0) +
                                      '0';
            }
            else if (kFullMantissa > mantissa_cursor_) // if still space to write
            {
                mantissa_buffer_[mantissa_cursor_] = static_cast<std::underlying_type<Op>::type>(opcode) -
                                                     static_cast<std::underlying_type<Op>::type>(Op::num_0) +
                                                     '0';
                mantissa_cursor_++; // move cursor forward
            }
            break;
        case Op::num_a:
        case Op::num_b:
        case Op::num_c:
        case Op::num_d:
        case Op::num_e:
        case Op::num_f:
            if (is_editing_float_)
                assert(false);                         // logic error
            else if (kFullMantissa > mantissa_cursor_) // if still space to write
            {
                mantissa_buffer_[mantissa_cursor_] = static_cast<std::underlying_type<Op>::type>(opcode) -
                                                     static_cast<std::underlying_type<Op>::type>(Op::num_a) +
                                                     'A';
                mantissa_cursor_++; // move cursor forward
            }
            break;
        case Op::eex:
            if (is_hex_mode_)
                ; // do nothing
            else  // if not hex mode.
            {
                // if it is not float editing mode and ready to enter to the float editing mode
                if (!is_editing_float_ &&
                    (kFullMantissa - 4 >= mantissa_cursor_ || decimal_point_position_ != kDecimalPointNotDisplayed))
                {
                    if (!std::strcmp(mantissa_buffer_, " 00000000") || // If the mantissa is 0
                        !std::strcmp(mantissa_buffer_, " 0000000 ") ||
                        !std::strcmp(mantissa_buffer_, " 000000  ") ||
                        !std::strcmp(mantissa_buffer_, " 00000   ") ||
                        !std::strcmp(mantissa_buffer_, " 0000    ") ||
                        !std::strcmp(mantissa_buffer_, " 000     ") ||
                        !std::strcmp(mantissa_buffer_, " 00      ") ||
                        !std::strcmp(mantissa_buffer_, " 0       "))
                    {
                        std::strcpy(mantissa_buffer_, " 1       ");          // enforce it 1
                        decimal_point_position_ = kDecimalPointNotDisplayed; // do not display "."
                    }
                    is_editing_float_ = true;
                }
            }
            break;
        case Op::period:
            if (is_hex_mode_)
                ; // do nothing
            else  // if not hex mode.
            {
                if (is_editing_float_)
                    ;                                                          // do nothing
                else if (decimal_point_position_ != kDecimalPointNotDisplayed) // if decimal point already exist
                    ;                                                          // do nothing
                else
                {
                    if (mantissa_cursor_ == 1)                                          // if the cursor is left most digits
                        decimal_point_position_ = kUpperMostDigit;                      // place decimal point to its right
                    else if (kFullMantissa >= mantissa_cursor_ && mantissa_cursor_ > 1) // if not, place decimal point to its left
                        decimal_point_position_ = kFullMantissa - mantissa_cursor_;     // 2->7, 3->6, ...
                    else
                        assert(false); // program logic error
                }
            }
            break;
        case Op::del:
            if (is_editing_float_)
            {
                if (!std::strcmp(exponent_buffer_, " 00"))
                    is_editing_float_ = false;
                else if (!std::strcmp(exponent_buffer_, "-00"))
                    exponent_buffer_[0] = ' '; // delete minus sign
                else
                { // 1/10 the eponent
                    exponent_buffer_[2] = exponent_buffer_[1];
                    exponent_buffer_[1] = '0';
                }
            }
            else // not float
            {
                if (mantissa_cursor_ == 2) // if deleting right most digit
                {
                    HandleNonEditingOp(Op::clx); // delete X. And then, set is_editing = false implicitly.
                    return;                      // HandleNonEditingOp() render the text_buffer_. So ,we can leave now.
                }
                else
                {
                    mantissa_cursor_--;
                    mantissa_buffer_[mantissa_cursor_] = ' '; // delete one digit
                }
            }
            break;
        case Op::chs:
            if (is_hex_mode_)
                ; // do nothing
            else  // if not hex mode.
            {

                if (is_editing_float_)                                              // If floating input mode
                    exponent_buffer_[0] = (exponent_buffer_[0] == '-') ? ' ' : '-'; // change sign of exponent
                else                                                                // If fixed point input mode
                    mantissa_buffer_[0] = (mantissa_buffer_[0] == '-') ? ' ' : '-'; // change sign of mantissa
            }
            break;
        default:
            assert(false); // unimplemented error
        }
        std::strcpy(text_buffer_, mantissa_buffer_);
        if (is_editing_float_)
            std::strcpy(&text_buffer_[6], exponent_buffer_);
    }
}

void rpn_engine::Console::Input(Op opcode)
{
    if ((Op::num_0 > opcode) && (opcode >= Op::duplicate))
        HandleNonEditingOp(opcode);
    else
        HandleEditingOp(opcode);
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

    if (value >= kBoundaryOfScientific)  // if too large,
        RenderScientificMode(false);     // display in the scientific format
    else if (5e-8 > value && value != 0) // if too small
        RenderScientificMode(false);     // display in the scientific format
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
            assert(false); // program logic error

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
    assert(buffer[kExponentPos] == kExponentMark); // program logic error

    // Get a exponent part of #.#######e#####
    int exponent = std::atoi(&buffer[kExponentPos + 1]);

    decimal_point_position_ = kUpperMostDigit; // right of the upper most digit

    if (exponent > 99) // if the number exceed the max display number
        if (value > 0)
            std::strcpy(text_buffer_, "+99999+99"); // sign of max number
        else
            std::strcpy(text_buffer_, "-99999+99"); // sign of max number

    else if (-99 > exponent)                    // if the number is lower than the min display number
        std::strcpy(text_buffer_, " 00000000"); // flash to zero
    else                                        // the number is in the normal range
    {                                           // copy the mantissa withtout decimal point
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

            // adjust the decimal point for engineering format.
            if (0 > offset_exponent) // that means the exponent is minus and offset is not zero
            {
                exponent -= 3;        // this is required only when the old_exponent is not the integer multiple of 3
                offset_exponent += 3; // adjust for the minus exponent
            }
            decimal_point_position_ -= offset_exponent;
        }
        // append exponent to mantissa
        std::snprintf(&text_buffer_[i], 4, kDisplayFormatSpec, exponent);
    }
}

void rpn_engine::Console::RenderHexMode()
{
    // get the stack top, take real part and round.
    int32_t value = std::round(engine_.Get(0).real());

    std::sprintf(text_buffer_, " %08X", value);          // display by 8 digit hex with leading zero
    decimal_point_position_ = kDecimalPointNotDisplayed; // no decimal point
}
