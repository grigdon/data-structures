#ifndef STACK_H
#define STACK_H

#include <deque>
#include <iostream>

namespace cop4530 {
    template <typename T>
    class Stack {
    private:
        std::deque<T> stack; // underlying data structure for the stack

    public:
        Stack(); // zero-argument constructor
        ~Stack(); // destructor
        Stack(const Stack<T>& rhs); // copy constructor
        Stack(Stack<T>&& rhs); // move constructor 
        Stack<T>& operator= (const Stack<T>& rhs); // copy assignment operator
        Stack<T>& operator= (Stack<T>&& rhs); // move assignment operator
        bool empty() const; // returns whether stack is empty
        void clear(); // deletes all elements in stack
        void push(const T& x); // adds x to stack (copy version)
        void push(T&& x); // adds x to stack (move version)
        void pop(); // removes item on top of stack
        T& top(); // mutator that returns a reference to the top of the stack
        const T& top() const; // accessor that returns the value of the top of the stack
        int size() const; // returns number of elements in stack
        void print(std::ostream& os, char ofc = ' ') const; // prints elements in stack to os (ofc is delimiter)
    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& rhs); // invokes print() method

    template <typename T>
    bool operator== (const Stack<T>& lhs, const Stack<T>& rhs); // equality comparator

    template <typename T>
    bool operator!= (const Stack<T>& lhs, const Stack<T>& rhs); // inequality comparator

    template <typename T>
    bool operator<= (const Stack<T>& lhs, const Stack<T>& rhs); // less than or equal to comparator

    
    #include "stack.hpp" // include stack.hpp implementation

} // end of namespace cop4530

#endif 
