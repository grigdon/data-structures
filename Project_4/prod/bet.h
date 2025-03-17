#ifndef BET_H
#define BET_H
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <cctype>

class BET {
    private:
        struct BinaryNode {
            std::string data;
            BinaryNode* left; // left binary node
            BinaryNode* right; // right binary node

            BinaryNode(const std::string & d, BinaryNode *l = nullptr, BinaryNode *r = nullptr) // zero-parameter constructor
                : data{d}, left{l}, right{r} {}

            BinaryNode(const std::string && d, BinaryNode *l = nullptr, BinaryNode *r = nullptr) // move constructor
                : data{std::move(d)}, left{l}, right {r} {}

        }; // end of struct

        BinaryNode* root; // root node

        void printInfixExpression(BinaryNode *n); // prints infix expression of tree
        int getPrecedence(const std::string& token) const; // returns the precedence of a token
        void makeEmpty(BinaryNode* &t); // deletes all nodes in subtree pointed to by "t"
        BinaryNode * clone(BinaryNode *t) const; // clones all nodes in subtree pointed to by "t"
        void printPostfixExpression(BinaryNode *n); // prints the tree's postfix expression
        size_t size(BinaryNode *t); // returns size of subtree pointed to by "t"
        size_t leaf_nodes(BinaryNode *t); // returns number of leaf nodes pointed to by "t"
public:
    BET(); // default zero-parameter constructor
    BET(const std::string postfix); // one-parameter constructor
    BET(const BET &rhs); // copy constructor
    ~BET(); // destructor
    bool buildFromPostfix(const std::string postfix); // builds binary tree from postfix expression
    const BET & operator=(const BET &rhs); // assignment operator
    void printInfixExpression(); // calls private print function
    void printPostfixExpression(); // calls private print function
    size_t size(); // calls private size function
    size_t leaf_nodes(); // calls private size function
    bool empty(); // returns whether tree is empty

}; // end of BET class 

#include "bet.hpp" // include implementation file

#endif