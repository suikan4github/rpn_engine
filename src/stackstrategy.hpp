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
        virtual ~StackStrategy();

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

    private:
        const unsigned int stack_size_;
        /**
         * @brief The enetity of stack.
         * @details
         * The stack_[0] is the stack top. Index is allowed from 0 to stack_size_-1.
         */
        Element *const stack_;
    };
} // rpn_engine

// constructor
template <class Element>
rpn_engine::StackStrategy<Element>::StackStrategy(unsigned int stack_size) : stack_size_(stack_size),
                                                                             stack_(new Element[stack_size_])
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
