#pragma once
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

/**
 * @brief Engine implementation of RPN stack machine.
 *
 */
namespace rpn_engine
{
    /**
     * @brief Define pi here to keep cross platform compatibility.
     *
     */
    constexpr double pi = 3.141592653589793238462643383279502884L;

    /**
     * @brief enum class to specify the operation on stack
     *
     * @details
     * From duplicate to nop : command for operation
     * Other : command for edit.
     *
     */
    enum class Op : unsigned int
    {
        // Calculation opcode
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
        bit_mul,             ///< Pop X, Y, do  X * Y, then push
        bit_div,             ///< Pop X, Y, do Y / X, then push
        bit_neg,             ///< Pop X, do  -X, then push
        bit_or,              ///< Pop X, Y, do Y | X, then push
        bit_xor,             ///< Pop X, Y, do Y ^ X, then push
        bit_and,             ///< Pop X, Y, do Y & X, then push
        logical_shift_right, ///< Pop X, Y, do Y >> X, then push
        logical_shift_left,  ///< Pop X, Y, do Y << X, then push
        bit_not,             ///< Pop X,  do  ~X, then push
        change_display,      ///< Change the display mode ( fix, sci, end). Do not feed to Stack engine.
        enter,               ///< Delimiter between numbers.
        clx,                 ///< Clear X register. Do not feed to Stack engine.
        undo,                ///< Undo the previous operation. Do not feed to Stack engine.
        hex,                 ///< Change to hex mode.
        dec,                 ///< Change to dec mode.
        sto,                 ///< Store to a variable
        rcl,                 ///< Recall from a variable
        func,                ///< Pressing F key.
        nop,                 ///< Do nothing
                             // Editing op code.
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
        eex,                 ///< Delimiter for exponent intput. Do not feed to Stack engine.
        del,                 ///< Delete one char or clx. Do not feed to Stack engine.
        chs,                 ///< negate the sign
    };

    /**
     * @brief A generic stack.
     *
     * @tparam std::complex<double> A type name as element of stack
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
        // Surpress the default constructor.
        StackStrategy() = delete;
        ~StackStrategy();
        /********************************** BASIC OPERATION *****************************/
        /**
         * @brief Single interface for the operation.
         * @param opcode Opecode of the operation to do.
         */
        void Operation(Op opcode);

        /**
         * @brief Get the value of stack at specified position
         *
         * @param position The distance from the stack top. 0 means the stack top.
         * 1 means the 1 depth from the stack top. If the value exceeds the stack size, assertion fails.
         * @return std::complex<double> at the specified position.
         * @details
         * The contents of the stack is not affected.
         */
        std::complex<double> Get(unsigned int position);

        /**
         * @brief Overwrite stack top
         * @param e Value to overwrite the stack top
         */
        void SetX(const std::complex<double> &e);

        /**
         * @brief Push a given value to the stack
         *
         * @param e A value to push to the stack.
         * @details
         * All contents of the stack are pushed down to the depth direction.
         * Then, e is copied to the stack top. The vale in the stack bottom will be lost.
         */
        void Push(const std::complex<double> &e);

        /**
         * @brief Pop a value from the stack top.
         *
         * @return std::complex<double> The value of the stack top.
         * @details
         * The value of the stack top is returned.
         *
         * The contents of the stack are shifted to the shallow direction.
         * The stack bottom value is duplicated.
         */
        std::complex<double> Pop();

        /**
         * @brief Retrieve previous stack state.
         *
         */
        void Undo();

    private:
        const unsigned int stack_size_;
        /**
         * @brief The entity of stack.
         * @details
         * The stack_[0] is the stack top. Index is allowed from 0 to stack_size_-1.
         */
        std::complex<double> *const stack_;
        std::complex<double> *const undo_buffer_;
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
            DisableUndoSaving(StackStrategy *paraent);
            /**
             * @brief Destroy the Disable Undo Saving object
             * @details
             * Retrieve the previous enable / disable state.
             */
            virtual ~DisableUndoSaving();

        private:
            StackStrategy *parent_;
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
        void Negate();

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


        /**
         * @fn void DeComplex()
         * @brief Pop X and then, push X.re, push X.im;
         * @details
         * If the stack is implemented with scalar element, this function does nothing
         *
         */
        void DeComplex()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push real, push imag
            this->Push(std::complex<double>(x.real()));
            this->Push(std::complex<double>(x.imag()));
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


        /**
         * @fn void ToPolar()
         * @brief Pop X as cartesian complex and convert it to polar notation. and then Push it.
         * @details
         * The result is :
         * @li re : Absolute value of the complex value.
         * @li im : Argumentation of the complex value.
         * If the stack is implemented with scalar element, this function does nothing
         */
        void ToPolar()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push in polar notation
            this->Push(std::complex<double>(std::abs(x), std::arg(x)));
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
        void ToCartesian()
        {
            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push in cartesian nortation : abs * exp( i * arg )
            this->Push(x.real() * std::exp(std::complex<double>(0, 1) * x.imag()));
        }


        /**
         * @fn void SwapReIm()
         * @brief Pop X, swat the re, im part and then  push it.
         */
        void SwapReIm()
        {

            // Save stack state before mathematical operation
            SaveToUndoBuffer();
            DisableUndoSaving disable_undo(this); // Disabling by RAII

            // Pop parameters
            auto x = this->Pop();

            // push in cartesian nortation : abs * exp( i * arg )
            this->Push(std::complex<double>(x.imag(), x.real()));
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
        void BitNegate();

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
         * @fn int32_t To64bitValue(std::complex<double> x)
         * @brief Convert parameter to int32_t
         *
         * @param x Value to convert.
         * @return int32_t Converted value.
         * @details
         * Truncate given value to signed 64bit integer. The upper 32bit is
         * sign extended.
         * Then, extract lower 32bit value
         * The truncation is round to zero.
         *
         * Note that in case the given X exceed the range of the 64bit signed integer,
         * The result is unpredictable.
         */

        int64_t To64bitValue(std::complex<double> x)
        {
            // The double value is truncated to 64bit integer. Then,
            // 32bit LSB is extracted.
            int64_t intermediate_value = x.real();
            // extend sign
            if ((intermediate_value & 0x80000000) == 0)     // is it positive number?
                intermediate_value &= 0x00000000FFFFFFFFll; // force upper bits zero
            else                                            // negative number
                intermediate_value |= 0xFFFFFFFF00000000ll; // force upper bits one.
            return intermediate_value;
        }

        /**
         * @brief Convert parameter to std::complex<double>
         *
         * @param x
         * @return std::complex<double>
         */
        std::complex<double> ToElementValue(int32_t x);
    };
} // rpn_engine

