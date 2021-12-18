/**
 * @file stackstrategy.hpp
 * @author Seiichi "Suikan" Horie
 * @brief Generic Stack machine header file.
 * @version 0.1
 * @date 2021-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <cassert>
#include <cmath>
#include <complex>
#include <type_traits>

#ifndef FRIEND_TEST
// FRIEND_TEST is provided by google test. If not provided, just ignore it.
#define FRIEND_TEST(x, y)
#endif

/**
 * @brief Engine implementation of RPN stack machine.
 *
 */
namespace rpn_engine
{

    /**
     * @brief enum class to specify the operation on stack
     *
     */
    enum class Op
    {
        duplicate,           ///< Get stack top and push
        swap,                ///< Swap stack top and second
        rotate_pop,          ///< Rotate stack to pop wise
        rotate_push,         ///< Rotate stack to push wise
        add,                 ///< Pop X, Y, do X+Y, then push
        sub,                 ///< Pop X, Y, do Y-X, then push
        mul,                 ///< Pop X, Y, do X*Y, then push
        div,                 ///< Pop X, Y, do Y/X, then push
        neg,                 ///< Pop X, do -X, then push
        inv,                 ///< Pop X, do 1/X, then push
        sqrt,                ///< Pop X, do sqrt(X), then push
        square,              ///< Pop X, do X*X, then push
        pi,                  ///< Push 3.141592...
        exp,                 ///< Pop X, do e^X, then push
        log,                 ///< Pop X, do log(x), then push
        log10,               ///< Pop X, do log10(X), then push
        power10,             ///< Pop X, do 10^X, then push
        power,               ///< Pop X, Y, do X^Y, then push
        sin,                 ///< Pop X, do sin X, then push
        cos,                 ///< Pop X, do cos X, then push
        tan,                 ///< Pop X, do tan X, then push
        asin,                ///< Pop X, do asin X, then push
        acos,                ///< Pop X, do acos X, then push
        atan,                ///< Pop X, do atan X, then push
        complex,             ///< Pop X, Y, do Y+Xj, then push
        decomplex,           ///< Pop X, Push Re(X), Push Im(X)
        conjugate,           ///< Pop X, Push (Conjugate X)
        to_polar,            ///< Pop X, Push (Cartesian to Polar X)
        to_cartesian,        ///< Pop X, Push (Polar to Cartesian X)
        swap_re_im,          ///< Pop X, Push Im(X)+Re(X)*j
        bit_add,             ///< Pop X, Y, do Y + X, then push
        bit_sub,             ///< Pop X, Y, do Y - X, then push
        bitmul,              ///< Pop X, Y, do  X * Y, then push
        bit_div,             ///< Pop X, Y, do Y / X, then push
        bit_neg,             ///< Pop X, do  -X, then push
        bit_or,              ///< Pop X, Y, do Y | X, then push
        bit_xor,             ///< Pop X, Y, do Y ^ X, then push
        bit_and,             ///< Pop X, Y, do Y & X, then push
        logical_shift_right, ///< Pop X, Y, do Y >> X, then push
        logical_shift_left,  ///< Pop X, Y, do Y << X, then push
        bit_not,             ///< Pop X,  do  ~X, then push
        num_0,               ///< Constant for key input. Do not feed to Stack engine.
        num_1,               ///< Constant for key input. Do not feed to Stack engine.
        num_2,               ///< Constant for key input. Do not feed to Stack engine.
        num_3,               ///< Constant for key input. Do not feed to Stack engine.
        num_4,               ///< Constant for key input. Do not feed to Stack engine.
        num_5,               ///< Constant for key input. Do not feed to Stack engine.
        num_6,               ///< Constant for key input. Do not feed to Stack engine.
        num_7,               ///< Constant for key input. Do not feed to Stack engine.
        num_8,               ///< Constant for key input. Do not feed to Stack engine.
        num_9,               ///< Constant for key input. Do not feed to Stack engine.
        num_a,               ///< Constant for key input. Do not feed to Stack engine.
        num_b,               ///< Constant for key input. Do not feed to Stack engine.
        num_c,               ///< Constant for key input. Do not feed to Stack engine.
        num_d,               ///< Constant for key input. Do not feed to Stack engine.
        num_e,               ///< Constant for key input. Do not feed to Stack engine.
        num_f,               ///< Constant for key input. Do not feed to Stack engine.
        period,              ///< Constant for key input. Do not feed to Stack engine.
        clx,                 ///< Clear X register. Do not feed to Stack engine.
        del,                 ///< Delete one char or clx. Do not feed to Stack engine.
        undo,                ///< Undo the previous operation. Do not feed to Stack engine.
        change_display,      ///< Change the display mode ( fix, sci, end). Do not feed to Stack engine.
        eex,                 ///< Delimiter for exponent intput. Do not feed to Stack engine.
    };

    /**
     * @brief A generic stack.
     *
     * @tparam Element A type name as element of stack
     * @details
     * A generic stack for the RPN machine. This stack works based of the specialized machine.
     * Give a type parameter to customize it.
     *
     * The monadic operation pops one operand, calculate and push one operand.
     * The diadic operation pops two operands, calculate and push one operand.
     * Both monadic and diadic operation saves stack  to undo buffer
     * before the operation. The undo buffer can be copy back to stack by the
     * Undo() member function.
     *
     * All functions supports complex template type, if the stack is specialized by
     * std::complex<> type. On the other hand, if the stack is specialized by the
     * scalar type, following functions do nothing :
     * @li Complex
     * @li DecComplex
     * @li Conjugate
     * @li ToPolar
     * @li ToCartesian
     * @li SwapReIm
     */
    template <class Element>
    class StackStrategy
    {
    public:
        /**
         * @brief Construct a new Stack Strategy object
         *
         * @param stack_size The size of stack. Must be non-zero value.
         * @details
         * In the cae of stack_size == 0, assertion failed.
         */
        StackStrategy(unsigned int stack_size);
        ~StackStrategy();
        /********************************** BASIC OPERATION *****************************/
        /**
         * @brief Single interface for the operation.
         * @param opecode Opecode of the operation to do.
         */
        void Operation(Op opecode);

        /**
         * @brief Get the value of stack at specified position
         *
         * @param position The distance from the stack top. 0 means the stack top.
         * 1 means the 1 depth from the stack top. If the value exceeds the stack size, assertion fails.
         * @return Element at the specified position.
         * @details
         * The contents of the stack is not affected.
         */
        Element Get(unsigned int position);

        /**
         * @brief Push a given value to the stack
         *
         * @param e A value to push to the stack.
         * @details
         * All contents of the stack are pushed down to the depth direction.
         * Then, e is copied to the stack top. The vale in the stack bottom will be lost.
         */
        void Push(const Element &e);

        /**
         * @brief Pop a value from the stack top.
         *
         * @return Element The value of the stack top.
         * @details
         * The value of the stack top is returned.
         *
         * The contents of the stack are shifted to the shallow direction.
         * The stack bottom value is duplicated.
         */
        Element Pop();

        /**
         * @brief Retrieve previous stack state.
         *
         */
        void Undo();

    private:
        FRIEND_TEST(BasicStackTest, Undo);
        FRIEND_TEST(BasicBitwiseTest, To32bitValue);
        FRIEND_TEST(BasicBitwiseTest, ToElementValue);
        const unsigned int stack_size_;
        /**
         * @brief The entity of stack.
         * @details
         * The stack_[0] is the stack top. Index is allowed from 0 to stack_size_-1.
         */
        Element *const stack_;
        Element *const undo_buffer_;
        bool undo_saving_enabled_;

        /**
         * @brief Disabling to save the stack by RAII
         * @details
         * To disable the stack saving for undo, create an object of this
         * class. The constructor save the current undo enable / disable state
         * then, set it disable.
         *
         * At the exit of the scope, the object is automatically deleted and
         * destructor retrieve the previous enable / disable state.
         */
        class DisableUndoSaving
        {
        public:
            /**
             * @brief Construct a new Disable Undo Saving object
             * @details
             * Save the current enable / disable state and disable the state.
             */
            DisableUndoSaving(StackStrategy<Element> *paraent);
            /**
             * @brief Destroy the Disable Undo Saving object
             * @details
             * Retrieve the previous enable / disable state.
             */
            virtual ~DisableUndoSaving();

        private:
            StackStrategy<Element> *parent_;
            bool last_state_;
        };

        /**
         * @brief Duplicate the stack top.
         * @details
         *  x=pop; push(x); push(x);
         */
        void Duplicate();

        /**
         * @brief Swap the X and Y (top and second).
         * @details
         *  x=pop; y=pop; push(x); push(y);
         */
        void Swap();

        /**
         * @brief Rotate down the stack.
         * @details
         *  Pop the stack top and insert it to the stack bottom;
         */
        void RotatePop();

        /**
         * @brief Rotate up the stack.
         * @details
         * Get the stack bottom and push it to the top;
         */
        void RotatePush();

        /**
         * @brief Copy the stack to the Undo variable.
         *
         */
        void SaveToUndoBuffer();

        /********************************** MATHMATICAL OPERATION *****************************/

        /**
         * @brief Pop X, Y and then push Y+X
         *
         */
        void Add();

        /**
         * @brief Pop X, Y and then push Y-X
         *
         */
        void Subtract();

        /**
         * @brief Pop X, Y and then push Y*X
         *
         */
        void Multiply();

        /**
         * @brief Pop X, Y and then push Y/X
         *
         */
        void Divide();

        /**
         * @brief Pop X and then push -X
         *
         */
        void Nagate();

        /**
         * @brief Pop X and then push 1/X
         *
         */
        void Inverse();

        /**
         * @brief Pop X and then push square root of X
         *
         */
        void Sqrt();

        /**
         * @brief Pop X and then push X * X
         *
         */
        void Square();

        /**
         * @brief Push pi
         * @details
         * Push pi to the stack.
         */
        void Pi();

        /********************************** TRANSCENDENTAL OPERATION *****************************/

        /**
         * @brief Pop X and then push Exponential of X.
         *
         */
        void Exp();

        /**
         * @brief Pop X and then push Natural Logarithm of X
         *
         */
        void Log();

        /**
         * @brief Pop X and then push 10 based logarithm of X
         *
         */
        void Log10();

        /**
         * @brief Pop X and then push X'th power of 10
         *
         */
        void Power10();

        /**
         * @brief Pop X, Y and then push Y^X
         *
         */
        void Power();

        /**
         * @brief Pop X and then push Sine(x).
         *
         */
        void Sin();

        /**
         * @brief Pop X and then push CoSine(x)
         *
         */
        void Cos();

        /**
         * @brief Pop X and then push Tangent(x)
         *
         */
        void Tan();

        /**
         * @brief Pop X and then push arcsin(x)
         *
         */
        void Asin();

        /**
         * @brief Pop X and then push Acos(x)
         *
         */
        void Acos();

        /**
         * @brief Pop X and then push Atan(x)
         *
         */
        void Atan();

        /********************************** COMPLEX OPERATION *****************************/

        /**
         * @fn void Complex()
         * @brief Make complex : Pop X, Y and then Y + Xi and Push it.
         * @details
         * If the stack is implemented with scalar element, this function does nothing
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void Complex()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII   // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();
            auto y = this->Pop();

            y.imag(x.real());

            // y + ix
            this->Push(y);
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        void Complex()
        {
            // In the case of scalar, do nothing
        }

        /**
         * @fn void DeComplex()
         * @brief Pop X and then, push X.re, push X.im;
         * @details
         * If the stack is implemented with scalar element, this function does nothing
         *
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void DeComplex()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push real, push imag
            this->Push(Element(x.real()));
            this->Push(Element(x.imag()));
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        void DeComplex()
        {
            // In the case of scalar, do nothing
        }

        /**
         *
         * @fn void Conjugate()
         * @brief Pop X and then, push conj(X)
         * @details
         * The Undo buffer is affected.
         *
         * If the stack is implemented with scalar element, this function does nothing
         *
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void Conjugate()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push real, push imag
            this->Push(std::conj(x));
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        void Conjugate()
        {
            // In the case of scalar, do nothing
        }

        /**
         * @fn void ToPolar()
         * @brief Pop X as cartesian complex and convert it to polar notation. and then Push it.
         * @details
         * The result is :
         * @li re : Absolute value of the complex value.
         * @li im : Argumentation of the complex value.
         * If the stack is implemented with scalar element, this function does nothing
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void ToPolar()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push in polar notation
            this->Push(Element(std::abs(x), std::arg(x)));
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        void ToPolar()
        {
            // In the case of scalar, do nothing
        }

        /**
         * @fn void ToCartesian()
         * @brief Pop X as polar complex and convert it to the cartesian complex. And then push it.
         * @details
         * The parameter is :
         * @li re : Absolute value of the complex value.
         * @li im : Argumentation of the complex value.
         * If the stack is implemented with scalar element, this function does nothing
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void ToCartesian()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push in cartesian nortation : abs * exp( i * arg )
            this->Push(x.real() * std::exp(Element(0, 1) * x.imag()));
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        void ToCartesian()
        {
            // In the case of scalar, do nothing
        }

        /**
         * @fn void SwapReIm()
         * @brief Pop X, swat the re, im part and then  push it.
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void SwapReIm()
        {

            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push in cartesian nortation : abs * exp( i * arg )
            this->Push(Element(x.imag(), x.real()));
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        void SwapReIm()
        {
            // In the case of scalar, do nothing
        }

        /********************************** BITWISE OPERATION *****************************/

        /**
         * @brief Pop X,Y and then Add them as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitAdd();

        /**
         * @brief Pop X,Y and then Y-X  as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitSubtract();

        /**
         * @brief Pop X,Y and then multiply them as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitMultiply();

        /**
         * @brief Pop X,Y and then Y/X  as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitDivide();

        /**
         * @brief Pop X and then -X as 32bit integer. Then push it.
         * @details
         * X is truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitNagate();

        /**
         * @brief Pop X,Y and then Y bitwise OR X  as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitOr();

        /**
         * @brief Pop X,Y and then Y bitwise XOR X  as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitExor();

        /**
         * @brief Pop X,Y and then Y bitwise AND X  as 32bit integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */
        void BitAnd();

        /**
         * @brief Pop X,Y and then Y >> X  as 32bit UNSIGNED integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit unsigned integer before operation.
         *
         * Undo buffer is affected.
         */
        void LogicalShiftRight();

        /**
         * @brief Pop X,Y and then Y << X  as 32bit UNSIGNED integer. Then push it.
         * @details
         * Both X, Y are truncated to 32bit unsigned integer before operation.
         *
         * Undo buffer is affected.
         */
        void LogicalShiftLeft();

        /**
         * @brief Pop X and then bitwise NOT of X as 32bit integer. Then push it.
         * @details
         * X is truncated to 32bit signed integer before operation.
         *
         * Undo buffer is affected.
         */

        void BitNot();

        /**
         * @fn int32_t To32bitValue(Element x)
         * @brief Convert parameter to int32_t
         *
         * @param x Value to convert.
         * @return int32_t Converted value.
         * @details
         * Truncate given value to signed 64bit integer. Then, extract lower 32bit value.
         * The truncation is round to zero
         *
         * Note that in case the given X exceed the range of the 64bit signed integer,
         * The result is unpredictable.
         */

        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        int32_t To32bitValue(Element x)
        {
            // The double value is truncated to 64bit integer. Then,
            // 32bit LSB is extracted.
            int64_t intermediate_value = x.real();
            return intermediate_value;
        }

        template <class E = Element,
                  typename std::enable_if<std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by scarlar type.
        int32_t To32bitValue(Element x)
        {
            // The double value is truncated to 64bit integer. Then,
            // 32bit LSB is extracted.
            int64_t intermediate_value = x;
            return intermediate_value;
        }

        /**
         * @brief Convert parameter to Element
         *
         * @param x
         * @return Element
         */
        Element ToElementValue(int32_t x);
    };
} // rpn_engine

// constructor
template <class Element>
rpn_engine::StackStrategy<Element>::StackStrategy(unsigned int stack_size) : stack_size_(stack_size),
                                                                             stack_(new Element[stack_size_]),
                                                                             undo_buffer_(new Element[stack_size_]),
                                                                             undo_saving_enabled_(true)
{
    assert(stack_size_ >= 2);
    // allocate stack
    assert(stack_ != nullptr);

    // initialize stack
    for (int i = 0; i < stack_size_; i++)
        stack_[i] = 0;
    // initialize undo buffer
    for (int i = 0; i < stack_size_; i++)
        undo_buffer_[i] = 0;
}

template <class Element>
rpn_engine::StackStrategy<Element>::~StackStrategy()
{
    if (stack_ != nullptr)
        delete[] stack_;
    if (undo_buffer_ != nullptr)
        delete[] undo_buffer_;
}

template <class Element>
Element rpn_engine::StackStrategy<Element>::Get(unsigned int postion)
{
    assert(stack_size_ > postion);
    return stack_[postion];
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Push(const Element &e)
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

template <class Element>
Element rpn_engine::StackStrategy<Element>::Pop()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // preserve the last top value.
    Element last_top = stack_[0];

    // copy stack[1..stack_size-1] to stack[0..stack_size_-2]
    // stop bottom is duplicated
    for (unsigned int i = 0; i < stack_size_ - 1; i++)
        stack_[i] = stack_[i + 1];

    // return the preserved value.
    return last_top;
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Duplicate()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // To duplicate, pop the stack and push it twice.
    Element x = Pop();
    Push(x);
    Push(x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Swap()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // To swap x and y, pop the stack, stack second and push them reverse.
    Element x = Pop();
    Element y = Pop();
    Push(x);
    Push(y);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::RotatePop()
{
    // Rotate the stack contents to the pop wise. To make it happen,
    // Pop the top at first. Then, copy it to the bottom.
    Element x = Pop();
    stack_[stack_size_ - 1] = x;
}

template <class Element>
void rpn_engine::StackStrategy<Element>::RotatePush()
{
    // Rotate the stack contents to the push wise. To make it happen,
    // Get the bottom value and push it
    Element x = Get(stack_size_ - 1);
    Push(x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::SaveToUndoBuffer()
{
    if (undo_saving_enabled_)
    {
        // Store Stack state to the undo buffer.
        for (int i = 0; i < stack_size_; i++)
            undo_buffer_[i] = stack_[i];
    }
}

template <class Element>
rpn_engine::StackStrategy<Element>::DisableUndoSaving::DisableUndoSaving(rpn_engine::StackStrategy<Element> *parent) : parent_(parent),
                                                                                                                       last_state_(parent->undo_saving_enabled_)
{

    // disable the undo.
    parent_->undo_saving_enabled_ = false;
}

template <class Element>
rpn_engine::StackStrategy<Element>::DisableUndoSaving::~DisableUndoSaving()
{
    // restore previous state
    parent_->undo_saving_enabled_ = last_state_;
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Undo()
{
    // Retrieve the last stack state
    for (int i = 0; i < stack_size_; i++)
        stack_[i] = undo_buffer_[i];
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Add()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y + x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Subtract()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y - x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Multiply()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y * x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Divide()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y / x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Nagate()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(-x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Inverse()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(1.0 / x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Sqrt()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::sqrt(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Square()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(x * x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Pi()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // do the operation
    Push(M_PI);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Exp()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::exp(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Log()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::log(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Log10()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::log10(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Power10()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::pow(10, x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Power()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(std::pow(y, x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Sin()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::sin(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Cos()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::cos(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Tan()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::tan(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Asin()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::asin(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Acos()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::acos(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Atan()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::atan(x));
}

template <class Element>
Element rpn_engine::StackStrategy<Element>::ToElementValue(int32_t x)
{
    return static_cast<Element>(x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitAdd()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = x + y;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitSubtract()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = y - x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitMultiply()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = y * x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitDivide()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = y / x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitNagate()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());

    // do the operation
    uint32_t r = -x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitOr()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = y | x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitExor()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = y ^ x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitAnd()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());
    auto y = To32bitValue(Pop());

    // do the operation
    uint32_t r = y & x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::LogicalShiftRight()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    uint32_t x = static_cast<uint32_t>(To32bitValue(Pop()));
    uint32_t y = static_cast<uint32_t>(To32bitValue(Pop()));

    // do the operation
    uint32_t r = y >> x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::LogicalShiftLeft()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    uint32_t x = static_cast<uint32_t>(To32bitValue(Pop()));
    uint32_t y = static_cast<uint32_t>(To32bitValue(Pop()));

    // do the operation
    uint32_t r = y << x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitNot()
{
    // Save stack state before mathematical operation
    SaveToUndoBuffer();
    DisableUndoSaving disable_undo(this); // Disabling by RAII

    // Get parameters
    auto x = To32bitValue(Pop());

    // do the operation
    uint32_t r = ~x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Operation(Op opecode)
{

    switch (opecode)
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
        Nagate();
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
    case Op::bitmul:
        BitMultiply();
        break;
    case Op::bit_div:
        BitDivide();
        break;
    case Op::bit_neg:
        BitNagate();
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

    default: // in case of wrong op code.
        assert(false);
    }
}