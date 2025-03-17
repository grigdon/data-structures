#include "bet.h"

// *****************
// private functions
// *****************

// prints infix expression of tree
void BET::printInfixExpression(BinaryNode* n) {
    if (n == nullptr) 
        return;

    if (getPrecedence(n->data) == 0) { // if the node is an operand, print the data
        std::cout << n->data;
        return;
    }
    std::string currentOperator = n->data; // store current operator
    int currentPrecedence = getPrecedence(currentOperator);

    if (n->left != nullptr) { // print left subtree, if it exists
        bool needParenthesis = false;
        if (getPrecedence(n->left->data) == 1 || getPrecedence(n->left->data) == 2) { // if an operator
            int leftPrecedence = getPrecedence(n->left->data);
            if (leftPrecedence < currentPrecedence ||
               (leftPrecedence == currentPrecedence && getPrecedence(currentOperator) == 0)) {
                needParenthesis = true;
            }
        }
        if (needParenthesis) std::cout << "(";
        printInfixExpression(n->left);
        if (needParenthesis) std::cout << ")";
    }
    
    std::cout << " " << currentOperator << " ";

    if (n->right != nullptr) { // print right subtree, if it exists
        bool needParenthesis = false;
        if (getPrecedence(n->right->data) == 1 ||getPrecedence(n->right->data) == 2) { // if an operator
            int rightPrecedence = getPrecedence(n->right->data);
            if (rightPrecedence < currentPrecedence ||
               (rightPrecedence == currentPrecedence && getPrecedence(currentOperator) != 0)) {
                needParenthesis = true;
            }
        }
        if (needParenthesis) std::cout << "(";
        printInfixExpression(n->right);
        if (needParenthesis) std::cout << ")";
    }
}

// returns whether a token is an operator
int BET::getPrecedence(const std::string& token) const {
    if (token == "*" || token == "/") return 2; // * or / are precedence 2
    if (token == "+" || token == "-") return 1; // + or - are precedence 1
    else { return 0;} // operands are precedence 0
}

// deletes all nodes in subtree pointed to by "t"
void BET::makeEmpty(BinaryNode*& t) {
    if (t != nullptr) {
        makeEmpty(t->left); // recursively clears left and right subtrees
        makeEmpty(t->right);
        t = nullptr; 
        delete t;  // deletes node
    }
}

// clones all nodes in subtree pointed to by "t"
BET::BinaryNode* BET::clone(BinaryNode* t) const {
    if (t == nullptr)
        return nullptr;
    return new BinaryNode(t->data, clone(t->left), clone(t->right)); // recursively clones nodes
}

// prints the tree's postfix expression
void BET::printPostfixExpression(BinaryNode* n) {
    if (n != nullptr) {
        printPostfixExpression(n->left); 
        printPostfixExpression(n->right);
        std::cout << n->data << " ";
    }
}

// returns size of subtree pointed to by "t"
size_t BET::size(BinaryNode* t) {
    if (t == nullptr) {
        return 0;
    }
    else {
        return 1 + size(t->left) + size(t->right); // recursively counts the size of the tree
    }
}

// returns number of leaf nodes pointed to by "t"
size_t BET::leaf_nodes(BinaryNode* t) {
    if (t == nullptr) {
        return 0;
    }
    if (t->left == nullptr && t->right == nullptr) // checks if t is a leaf
        return 1; // adds one to the count
    return leaf_nodes(t->left) + leaf_nodes(t->right); // recursively counts the number of leaves
}

// ****************
// public functions
// ****************

// default zero-parameter constructor
BET::BET() : root(nullptr) {}

// one-parameter constructor
BET::BET(const std::string postfix) {
    buildFromPostfix(postfix);
}

// copy constructor
BET::BET(const BET& rhs) : root(nullptr) {
    root = clone(rhs.root);
}

// destructor
BET::~BET() {
    makeEmpty(root); //
}

// builds binary tree from postfix expression
bool BET::buildFromPostfix(const std::string postfix) {
    std::stack<BinaryNode*> stack; // stack of nodes
    std::stringstream tokens(postfix); // stringstream object for separating operators and operands
    std::string currentToken; // current operator/operand

    makeEmpty(root); // clear the current binary tree 

    while (tokens >> currentToken) {
        if (std::isdigit(currentToken[0]) || std::isalpha(currentToken[0])) { // if an operand
            stack.push(new BinaryNode(currentToken)); // push new node into stack
        }
        else if (currentToken == "+" || currentToken == "-" || currentToken == "*" || currentToken == "/") { // if an operator
            if (stack.size() < 2) {
                std::cout << "Error: Invalid postfix expression.\n";
                return false;
            }
            BinaryNode* right = stack.top(); // set previous two stack entries as left and right nodes
            stack.pop();
            BinaryNode* left = stack.top();
            stack.pop();
            stack.push(new BinaryNode(currentToken, left, right)); // create new node for operation
        }
        else {
            std::cout << "Error: Invalid postfix expression.\n";
            return false;
        }
    }

    if (stack.size() != 1) {
        std::cout << "Error: Invalid postfix expression.\n";
        return false;
    }

    root = stack.top(); // set current tree as top stack element
    stack.pop(); // clear the stack
    return true;
}

// assignment operator
const BET& BET::operator=(const BET& rhs) {
    if (this != &rhs) {
        makeEmpty(root);
        root = clone(rhs.root);
    }
    return *this;
}

// calls private print function
void BET::printInfixExpression() {
    printInfixExpression(root);
    std::cout << "\n";
}

// calls private print function
void BET::printPostfixExpression() {
    printPostfixExpression(root);
    std::cout << "\n";
}

// calls private size function
size_t BET::size() {
    return size(root);
}

// calls private leaf node function 
size_t BET::leaf_nodes() {
    return leaf_nodes(root);
}

// returns whether tree is empty 
bool BET::empty() {
    return root == nullptr;
}