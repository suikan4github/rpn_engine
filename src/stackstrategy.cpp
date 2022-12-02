#include "stackstrategy.hpp"

// constructor

rpn_engine::StackStrategy::StackStrategy(unsigned int stack_size) : stack_size_(stack_size),
                                                                             stack_(new std::complex<double>[stack_size_]),
                                                                             undo_buffer_(new std::complex<double>[stack_size_]),
                                                                             undo_saving_enabled_(true)
{
    assert(stack_size_ >= 2);
    // allocate stack
    assert(stack_ != nullptr);

    // initialize stack
    for (unsigned int i = 0; i < stack_size_; i++)
        stack_[i] = 0;
    // initialize undo buffer
    for (unsigned int i = 0; i < stack_size_; i++)
        undo_buffer_[i] = 0;
}


rpn_engine::StackStrategy::~StackStrategy()
{
    if (stack_ != nullptr)
        delete[] stack_;
    if (undo_buffer_ != nullptr)
        delete[] undo_buffer_;
}


std::complex<double> rpn_engine::StackStrategy::Get(unsigned int postion)
{
    assert(stack_size_ > postion);
    return stack_[postion];
}


void rpn_engine::StackStrategy::SetX(const std::complex<double> &e)
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    stack_[0] = e;
}


void rpn_engine::StackStrategy::Push(const std::complex<double> &e)
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // copy stack[0..stack_size-2] to stack[1..stack_size_-1]
    for (unsigned int i = stack_size_ - 1; i > 0; i--)
        stack_[i] = stack_[i - 1];

    // Then store e to the stack top.
    stack_[0] = e;
}


std::complex<double> rpn_engine::StackStrategy::Pop()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // preserve the last top value.
    std::complex<double> last_top = stack_[0];

    // copy stack[1..stack_size-1] to stack[0..stack_size_-2]
    // stop bottom is duplicated
    for (unsigned int i = 0; i < stack_size_ - 1; i++)
        stack_[i] = stack_[i + 1];

    // return the preserved value.
    return last_top;
}


void rpn_engine::StackStrategy::Duplicate()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // To duplicate, pop the stack and push it twice.
    std::complex<double> x = Pop();
    Push(x);
    Push(x);
}


void rpn_engine::StackStrategy::Swap()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // To swap x and y, pop the stack, stack second and push them reverse.
    std::complex<double> x = Pop();
    std::complex<double> y = Pop();
    Push(x);
    Push(y);
}


void rpn_engine::StackStrategy::RotatePop()
{
    // Rotate the stack contents to the pop wise. To make it happen,
    // Pop the top at first. Then, copy it to the bottom.
    std::complex<double> x = Pop();
    stack_[stack_size_ - 1] = x;
}


void rpn_engine::StackStrategy::RotatePush()
{
    // Rotate the stack contents to the push wise. To make it happen,
    // Get the bottom value and push it
    std::complex<double> x = Get(stack_size_ - 1);
    Push(x);
}


void rpn_engine::StackStrategy::SaveToUndoBuffer()
{
    if (undo_saving_enabled_)
    {
        // Store Stack state to the undo buffer.
        for (unsigned int i = 0; i < stack_size_; i++)
            undo_buffer_[i] = stack_[i];
    }
}


rpn_engine::StackStrategy::DisableUndoSaving::DisableUndoSaving(rpn_engine::StackStrategy *parent) : parent_(parent),
                                                                                                                       last_state_(parent->undo_saving_enabled_)
{

    // disable the undo.
    parent_->undo_saving_enabled_ = false;
}


rpn_engine::StackStrategy::DisableUndoSaving::~DisableUndoSaving()
{
    // restore previous state
    parent_->undo_saving_enabled_ = last_state_;
}


void rpn_engine::StackStrategy::Undo()
{
    // Retrieve the last stack state
    for (unsigned int i = 0; i < stack_size_; i++)
        stack_[i] = undo_buffer_[i];
}


void rpn_engine::StackStrategy::Add()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    std::complex<double> y = Pop();
    // do the operation
    Push(y + x);
}


void rpn_engine::StackStrategy::Subtract()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    std::complex<double> y = Pop();
    // do the operation
    Push(y - x);
}


void rpn_engine::StackStrategy::Multiply()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    std::complex<double> y = Pop();
    // do the operation
    Push(y * x);
}


void rpn_engine::StackStrategy::Divide()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    std::complex<double> y = Pop();
    // do the operation
    Push(y / x);
}


void rpn_engine::StackStrategy::Negate()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(-x);
}


void rpn_engine::StackStrategy::Inverse()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(1.0 / x);
}


void rpn_engine::StackStrategy::Sqrt()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::sqrt(x));
}


void rpn_engine::StackStrategy::Square()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(x * x);
}


void rpn_engine::StackStrategy::Pi()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // do the operation
    Push(rpn_engine::pi);
}


void rpn_engine::StackStrategy::Exp()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::exp(x));
}


void rpn_engine::StackStrategy::Log()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::log(x));
}


void rpn_engine::StackStrategy::Log10()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::log10(x));
}


void rpn_engine::StackStrategy::Power10()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::pow(10, x));
}


void rpn_engine::StackStrategy::Power()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    std::complex<double> y = Pop();
    // do the operation
    Push(std::pow(y, x));
}


void rpn_engine::StackStrategy::Sin()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::sin(x));
}


void rpn_engine::StackStrategy::Cos()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::cos(x));
}


void rpn_engine::StackStrategy::Tan()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::tan(x));
}


void rpn_engine::StackStrategy::Asin()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::asin(x));
}


void rpn_engine::StackStrategy::Acos()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::acos(x));
}


void rpn_engine::StackStrategy::Atan()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    std::complex<double> x = Pop();
    // do the operation
    Push(std::atan(x));
}


std::complex<double> rpn_engine::StackStrategy::ToElementValue(int32_t x)
{
    return static_cast<std::complex<double>>(x);
}


void rpn_engine::StackStrategy::BitAdd()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = x + y;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitSubtract()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = y - x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitMultiply()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    int64_t r = y * x;
    uint64_t sign = r & (0xFFFFFFFF80000000ll); // take sign part. It is upper 32bit and MSB of lower 32bit

    if ((y & 0x80000000) == (x & 0x80000000)) // Is result must positive?
    {
        if (sign != 0)     // If sign part is non zero, overflown from signed 32 bit.
            r = INT32_MAX; // make it positive max
    }
    else // The result must be negative
    {
        if ((~sign & 0xFFFFFFFF80000000ll) != 0) // if the sign part is not all 1, overflown from signed 32bit.
            r = INT32_MIN;                       // make it negative min
    }

    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitDivide()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = y / x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitNegate()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());

    // do the operation
    uint32_t r = -x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitOr()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = y | x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitExor()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = y ^ x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitAnd()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = y & x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::LogicalShiftRight()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = (uint32_t)y >> (int32_t)x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::LogicalShiftLeft()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());
    auto y = To64bitValue(Pop());

    // do the operation
    uint32_t r = y << x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::BitNot()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To64bitValue(Pop());

    // do the operation
    uint32_t r = ~x;
    Push(ToElementValue(r));
}


void rpn_engine::StackStrategy::Operation(Op opcode)
{

    assert(opcode != Op::clx);
    assert(opcode != Op::enter);
    assert(opcode != Op::change_display);
    assert(Op::num_0 > opcode);

    switch (opcode)
    {
    case Op::duplicate:
        Duplicate();
        break;
    case Op::swap:
        Swap();
        break;
    case Op::rotate_pop:
        RotatePop();
        break;
    case Op::rotate_push:
        RotatePush();
        break;
    case Op::add:
        Add();
        break;
    case Op::sub:
        Subtract();
        break;
    case Op::mul:
        Multiply();
        break;
    case Op::div:
        Divide();
        break;
    case Op::neg:
        Negate();
        break;
    case Op::inv:
        Inverse();
        break;
    case Op::sqrt:
        Sqrt();
        break;
    case Op::square:
        Square();
        break;
    case Op::pi:
        Pi();
        break;
    case Op::exp:
        Exp();
        break;
    case Op::log:
        Log();
        break;
    case Op::log10:
        Log10();
        break;
    case Op::power10:
        Power10();
        break;
    case Op::power:
        Power();
        break;
    case Op::sin:
        Sin();
        break;
    case Op::cos:
        Cos();
        break;
    case Op::tan:
        Tan();
        break;
    case Op::asin:
        Asin();
        break;
    case Op::acos:
        Acos();
        break;
    case Op::atan:
        Atan();
        break;
    case Op::complex:
        Complex();
        break;
    case Op::decomplex:
        DeComplex();
        break;
    case Op::conjugate:
        Conjugate();
        break;
    case Op::to_polar:
        ToPolar();
        break;
    case Op::to_cartesian:
        ToCartesian();
        break;
    case Op::swap_re_im:
        SwapReIm();
        break;
    case Op::bit_add:
        BitAdd();
        break;
    case Op::bit_sub:
        BitSubtract();
        break;
    case Op::bit_mul:
        BitMultiply();
        break;
    case Op::bit_div:
        BitDivide();
        break;
    case Op::bit_neg:
        BitNegate();
        break;
    case Op::bit_or:
        BitOr();
        break;
    case Op::bit_xor:
        BitExor();
        break;
    case Op::bit_and:
        BitAnd();
        break;
    case Op::logical_shift_left:
        LogicalShiftLeft();
        break;
    case Op::logical_shift_right:
        LogicalShiftRight();
        break;
    case Op::bit_not:
        BitNot();
        break;
    case Op::undo:
        Undo();
        break;
    default: // in case of wrong op code.
        assert(false);
    }
}