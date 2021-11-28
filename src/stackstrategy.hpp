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
#include <math.h>
#include <complex>
#include <type_traits>

#ifndef FRIEND_TEST
// FRIEND_TEST is provided by google test. If not provided, just igonore it.
#define FRIEND_TEST(x, y)
#endif

/**
 * @brief Engine implementation of RPN stack machine.
 * 
 */
namespace rpn_engine
{

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
     * Both monadic and diadic operation sames stack top (x) to last x register
     * before the oepration. The last x register can be push to stack by LastX() member
     * function. 
     * 
     * All functions supports complex template type. 
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
         * @brief Get the value of stack at specified position
         * 
         * @param position The distance from the stack top. 0 means the stack top. 
         * 1 means the 1 depth from the stack top. If the value exeeds the stack size, assertion fails. 
         * @return Element at the specified position.
         * @details
         * The contents of the stack is not affected. 
         */
        Element Get(unsigned int position);

        /**
         * @brief Set the given value to the stack top. 
         * 
         * @param e A value to set to the stack.
         * @details
         * In this operation, stack doesn't push/pop. Only the stack top is affected.
         */
        void SetTop(Element e);

        /**
         * @brief Push a given value to the stack
         * 
         * @param e A value to push to the stack.
         * @details
         * All contents of the stack are pushed down to the depth direction. 
         * Then, e is copied to the stack top. The vale in the stack bottom will be lost.
         */
        void Push(Element e);

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
         * @brief Copy the stack top to the Laxt X variable.
         * 
         */
        void SaveToLastX();

        /**
         * @brief push Last X.
         * 
         */
        void LastX();

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
         * @brief Pop X and then push sqare root of X
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
         * Pi() doesn't save the last X.
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
         * If the stack is implemented with sclar element, this funciton does notihing
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void Complex()
        {
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
         * If the stack is implemented with sclar element, this funciton does notihing
         * 
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void DeComplex()
        {
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
         * The last X register is affected.
         * 
         * If the stack is implemented with sclar element, this funciton does notihing
         * 
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void Conjugate()
        {
            // save X before operation
            this->SaveToLastX();

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
         * If the stack is implemented with sclar element, this funciton does notihing
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void ToPolar()
        {
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
         * If the stack is implemented with sclar element, this funciton does notihing
         */
        template <class E = Element,
                  typename std::enable_if<!std::is_scalar<E>::value, int>::type = 0>
        // Implementation when the template is specialized by std::complex<> type.
        void ToCartesian()
        {
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

        /********************************** BITWISE OPERATION *****************************/

        /**
         * @brief Pop X,Y and then Add them as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitAdd();

        /**
         * @brief Pop X,Y and then Y-X  as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitSubtract();

        /**
         * @brief Pop X,Y and then multiply them as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitMultiply();

        /**
         * @brief Pop X,Y and then Y/X  as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitDivide();

        /**
         * @brief Pop X and then -X as 32bit integer. Then push it.  
         * @details
         * X is truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitNagate();

        /**
         * @brief Pop X,Y and then Y bitwise OR X  as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitOr();

        /**
         * @brief Pop X,Y and then Y bitwise XOR X  as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitExor();

        /**
         * @brief Pop X,Y and then Y bitwise AND X  as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */
        void BitAnd();

        /**
         * @brief Pop X,Y and then Y >> X  as 32bit UNSIGNED integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit unsigned integer before opration. 
         * 
         * Last X register is affected.
         */
        void LogicalShiftRight();

        /**
         * @brief Pop X,Y and then Y << X  as 32bit UNSIGNED integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit unsigned integer before opration. 
         * 
         * Last X register is affected.
         */
        void LogicalShiftLeft();

        /**
         * @brief Pop X and then bitwise NOT of X as 32bit integer. Then push it.  
         * @details
         * X is truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */

        void BitNot();

    private:
        FRIEND_TEST(BasicBitwiseTest, To32bitValue);
        FRIEND_TEST(BasicBitwiseTest, ToElementValue);
        const unsigned int stack_size_;
        /**
         * @brief The enetity of stack.
         * @details
         * The stack_[0] is the stack top. Index is allowed from 0 to stack_size_-1.
         */
        Element *const stack_;
        Element last_x_;

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
                                                                             last_x_(0)
{
    assert(stack_size_ >= 2);
    // allocate stack
    assert(stack_ != nullptr);

    // initialize stack
    for (int i = 0; i < stack_size_; i++)
        stack_[i] = 0;
}

template <class Element>
rpn_engine::StackStrategy<Element>::~StackStrategy()
{
    if (stack_ != nullptr)
        delete[] stack_;
}

template <class Element>
Element rpn_engine::StackStrategy<Element>::Get(unsigned int postion)
{
    assert(stack_size_ > postion);
    return stack_[postion];
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Push(Element e)
{
    // copy stack[0..stack_size-2] to stack[1..stack_size_-1]
    for (unsigned int i = stack_size_ - 1; i > 0; i--)
        stack_[i] = stack_[i - 1];

    // Then store e to the stack top.
    stack_[0] = e;
}

template <class Element>
Element rpn_engine::StackStrategy<Element>::Pop()
{
    // preserve the last top value.
    Element last_top = stack_[0];

    // copy stack[1..stack_size-1] to stack[0..stack_size_-2]
    // stap bottom is duplicated
    for (unsigned int i = 0; i < stack_size_ - 1; i++)
        stack_[i] = stack_[i + 1];

    // return the preserved value.
    return last_top;
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Duplicate()
{
    // To duplicate, pop the stack and push it twice.
    Element x = Pop();
    Push(x);
    Push(x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Swap()
{
    // To swap x and y, pop the stack, stack second and push them reverse.
    Element x = Pop();
    Element y = Pop();
    Push(x);
    Push(y);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::RotatePop()
{
    // Roate the stack contents to the pop wise. To make it happen,
    // Pop the top at first. Then, copy it to the bottom.
    Element x = Pop();
    stack_[stack_size_ - 1] = x;
}

template <class Element>
void rpn_engine::StackStrategy<Element>::RotatePush()
{
    // Roate the stack contents to the push wise. To make it happen,
    // Get the bottom value and push it
    Element x = Get(stack_size_ - 1);
    Push(x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::SetTop(Element e)
{
    // Store e to the stack top.
    stack_[0] = e;
}

template <class Element>
void rpn_engine::StackStrategy<Element>::SaveToLastX()
{
    // Store X to the LastX.
    last_x_ = Get(0);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::LastX()
{
    // The value of lastX.
    Push(last_x_);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Add()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y + x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Subtract()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y - x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Multiply()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y * x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Divide()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(y / x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Nagate()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(-x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Inverse()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(1 / x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Sqrt()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::sqrt(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Square()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(x * x);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Pi()
{
    // Pi() doesn't save the Last x

    // do the operation
    Push(M_PI);
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Exp()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::exp(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Log()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::log(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Log10()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::log10(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Power10()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::pow(10, x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Power()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    Element y = Pop();
    // do the operation
    Push(std::pow(y, x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Sin()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::sin(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Cos()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::cos(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Tan()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::tan(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Asin()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::asin(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Acos()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    Element x = Pop();
    // do the operation
    Push(std::acos(x));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::Atan()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    auto x = To32bitValue(Pop());

    // do the operation
    uint32_t r = -x;
    Push(ToElementValue(r));
}

template <class Element>
void rpn_engine::StackStrategy<Element>::BitOr()
{
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

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
    // Save LastX before mathumatical operation
    SaveToLastX();

    // Get parameters
    auto x = To32bitValue(Pop());

    // do the operation
    uint32_t r = ~x;
    Push(ToElementValue(r));
}
