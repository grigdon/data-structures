#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h"
#include <deque>
#include <iostream>

using namespace cop4530;

    template <typename T>
    Stack<T>::Stack() : stack() {}

    template <typename T>
    Stack<T>::~Stack() {
        clear();
    }

    template <typename T>
    Stack<T>::Stack(const Stack<T>& rhs) : stack(rhs.stack) {}

    template <typename T>
    Stack<T>::Stack(Stack<T>&& rhs) : stack(std::move(rhs.stack)) {}

    template <typename T>
    Stack<T>& Stack<T>::operator= (const Stack <T>& rhs) {
        stack = rhs.stack;
        return *this;
    }

    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack<T> && rhs){
        stack = std::move(rhs.stack);
        return *this;
    }
    template <typename T>
    bool Stack<T>::empty() const {
        return stack.empty();
    }

    template <typename T>
    void Stack<T>::clear() {
        stack.clear();
    }
    template <typename T>
    void Stack<T>::push(const T& x) {
        stack.push_back(x);
    }

    template <typename T>
    void Stack<T>::push(T && x) {
        stack.push_back(std::move(x));
    }

    template <typename T>
    void Stack<T>::pop() {
        if(!empty()) {
            stack.pop_back();
        }
    }

    template <typename T>
    T& Stack<T>::top() {
        return stack.back();    
    }

    template <typename T>
    const T& Stack<T>::top() const {
        return stack.back();
    }

    template <typename T>
    int Stack<T>::size() const { 
        return stack.size();
    }

    template <typename T>
    void Stack<T>::print(std::ostream& os, char ofc) const {
        for(auto it = stack.cbegin(); it != stack.cend(); ++it){
            os << *it << ofc;
        }
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& rhs) {
        rhs.print(os); 
        return os;
    }


    template <typename T>
    bool operator== (const Stack<T>& lhs, const Stack<T>& rhs) {
        auto Lhs = lhs;
        auto Rhs = rhs;

        while(!Lhs.empty() && !Rhs.empty()) {

            if(Lhs.top() != Rhs.top()) {
                return false;
            }

            Lhs.pop();
            Rhs.pop();
        }

        return true;
    }

    template <typename T>
    bool operator!= (const Stack<T>& lhs, const Stack<T>& rhs) {
        return !(lhs==rhs);
    }

    template <typename T>
    bool operator<= (const Stack<T>& lhs, const Stack<T>& rhs) {
        auto Lhs = lhs;
        auto Rhs = rhs;

        while(!Lhs.empty()) {

            if(Lhs.top() > Rhs.top() ) {
                return false;
            }

            Lhs.pop();
            Rhs.pop();
        }
        
        return true;
    }

#endif