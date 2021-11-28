/**
 * @file complexstackstrategy.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "stackstrategy.hpp"

namespace rpn_engine
{
    /**
     * @brief Complex Stack template
     * 
     * @tparam Element 
     * 
     * @details
     * This class implement the complex number specific member function. 
     */
    template <class Element>
    class ComplexStackStrategy : public StackStrategy<Element>
    {
    public:
        ComplexStackStrategy(unsigned int stack_size);
        virtual ~ComplexStackStrategy();

        /********************************** COMPLEX OPERATION *****************************/
        /**
         * @brief Make complex : Pop X, Y and then Y + Xi and Push it.
         */
        void Complex();

        /**
         * @brief Pop X and then, push X.re, push X.im;
         * 
         */
        void DeComplex();

        /**
         * @brief Pop X and then, push conj(X)
         * @details
         * The last X register is affected.
         * 
         */
        void Conjugate();

        /**
         * @brief Pop X as cartesian complex and convert it to polar notation. and then Push it.
         * @details
         * The result is : 
         * @li re : Absolute value of the complex value. 
         * @li im : Argumentation of the complex value. 
         */
        void ToPolar();

        /**
         * @brief Pop X as polar complex and convert it to the cartesian complex. And then push it. 
         * @details 
         * The parameter is : 
         * @li re : Absolute value of the complex value. 
         * @li im : Argumentation of the complex value. 
         */
        void ToCartesian();

        /********************************** BITWISE OPERATION *****************************/

        /**
         * @brief Pop X,Y and then Add them as 32bit integer. Then push it.  
         * @details
         * Both X, Y are truncated to 32bit signed integer before opration. 
         * 
         * Last X register is affected.
         */

#if 0
        virtual void BitAdd(){};
        virtual void BitSubtract();
        virtual void BitMultiply();
        virtual void BitDivide();
        virtual void BitNagate();

        virtual void BitOr();
        virtual void BitExor();
        virtual void BitAnd();
        virtual void LogicalShiftRight();
        virtual void LogicalShiftLeft();
        virtual void BitNot();
#endif
    private:
    };
} // rpn_engine

// constructor
template <class Element>
rpn_engine::ComplexStackStrategy<Element>::ComplexStackStrategy(unsigned int stack_size) : StackStrategy<Element>(stack_size){

                                                                                           };
// destructor
template <class Element>
rpn_engine::ComplexStackStrategy<Element>::~ComplexStackStrategy()
{
}

template <class Element>
void rpn_engine::ComplexStackStrategy<Element>::Complex()
{
    // Pop parameters
    auto x = this->Pop();
    auto y = this->Pop();

    y.imag(x.real());

    // y + ix
    this->Push(y);
}

template <class Element>
void rpn_engine::ComplexStackStrategy<Element>::DeComplex()
{
    // Pop parameters
    auto x = this->Pop();

    // push real, push imag
    this->Push(Element(x.real()));
    this->Push(Element(x.imag()));
}

template <class Element>
void rpn_engine::ComplexStackStrategy<Element>::Conjugate()
{
    // save X before operation
    this->SaveToLastX();

    // Pop parameters
    auto x = this->Pop();

    // push real, push imag
    this->Push(std::conj(x));
}

template <class Element>
void rpn_engine::ComplexStackStrategy<Element>::ToPolar()
{
    // Pop parameters
    auto x = this->Pop();

    // push in polar notation
    this->Push(Element(std::abs(x), std::arg(x)));
}

template <class Element>
void rpn_engine::ComplexStackStrategy<Element>::ToCartesian()
{
    // Pop parameters
    auto x = this->Pop();

    // push in cartesian nortation : abs * exp( i * arg )
    this->Push(x.real() * std::exp(Element(0, 1) * x.imag()));
}
