#include "stack.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <iomanip>

using namespace cop4530;

std::vector<std::string> convertStringToVector(const std::string& inputString);
int precedenceOfString(const std::string& inputString);
bool convertInfixToPostfix(const std::vector<std::string>& inputInfixVector, std::string& outputPostfixString);
bool evaluatePostfixExpression(const std::vector<std::string>& inputPostfixVector, std::string& outputPostfixString);
bool isNumericalInput(const std::string& inputString);

int main(void) {

    std::string inputInfixString, outputPostfixString, outputExpressionString;
    double outputExpressionDouble;

    std::cout << "Enter infix expression (exit to quit): ";

    // Allow user input the end of file is reached or user enters "exit"
    while (getline(std::cin, inputInfixString)) {
        if (inputInfixString == "exit") {
            return 0;
        }
        // convertInfixToPostfix and evaluatePostfixExpression evaluate to true if no errors were detected
        if (convertInfixToPostfix(convertStringToVector(inputInfixString), outputPostfixString)) {
            std::cout << "\nPostfix expression: " << outputPostfixString << "\n";

            if (evaluatePostfixExpression(convertStringToVector(outputPostfixString), outputExpressionString)) {
                outputExpressionDouble = stod(outputExpressionString);
                std::cout << "Postfix evaluation: " << outputPostfixString << " = " << std::defaultfloat << outputExpressionDouble;
                std::cout << "\nEnter infix expression (\"exit\" to quit): ";
            }
            else {
                std::cout << "Postfix evaluation: " << outputPostfixString << " =\n" << outputPostfixString;
                std::cout << "\nEnter infix expression (\"exit\" to quit): ";
            }
        }

        else {
            std::cout << "\n" << outputPostfixString;
            std::cout << "\nEnter infix expression (\"exit\" to quit): ";
        }
    }

    return 0;
}

// This function converts a string of space-separated tokens to a vector of strings using a stringstream object
std::vector<std::string> convertStringToVector(const std::string& inputString) {
    std::stringstream stringStream(inputString);
    std::string word = "";
    std::vector<std::string> outputVector;

    while (stringStream >> word) {
        outputVector.push_back(word);
    }
    return outputVector;
}

// This function assigns a precedence to a string using the following charting process
// It is used to sort operators ( "* and /" from "+ and -" ) and operands like 2, a_1 or ABCD
int precedenceOfString(const std::string& inputString) {
    if (inputString == "*" || inputString == "/") { // multiplication & division have priority 2
        return 2;
    }
    else if (inputString == "+" || inputString == "-") { // addition and subtraction have priority 1
        return 1;
    }
    else if (inputString != "(" && inputString != ")") { // operands have priority 0
        return 0;
    }
    else {
        return -1; // parenthesis and illegal entries have priority -1
    }
}

// Converts an infix expression into a postfix expression. outputPostfixString is used at the output and the boolean 
// return type is used to indicate whether the operation was performed successfully. 
// False indicates an error occurred. The error message will be added to the output string.
// True indicates there was no error.
bool convertInfixToPostfix(const std::vector<std::string>& inputInfixVector, std::string& outputPostfixString) {
    Stack<std::string> stack;
    outputPostfixString = "";

    for (std::vector<std::string>::const_iterator it = inputInfixVector.begin(); it != inputInfixVector.end(); ++it) {
        std::string currentItString = *it; // this is the current entry i.e., 2, +, AB, etc.
        std::string previousItString = *it; // this is the entry before the current entry

        if (it == inputInfixVector.begin() && (precedenceOfString(currentItString) == 1 || precedenceOfString(currentItString) == 2)) {
            outputPostfixString = "Error: Missing operands in the expression"; // illegal to have leading numerical operator i.e. / 100
            return false;
        }

        if (it != inputInfixVector.begin()) {
            previousItString = *(it - 1); // sets the previous iterator once at the second vector position 
        }

        if (precedenceOfString(currentItString) == 0) { // if an operand, add to output
            outputPostfixString += currentItString + " ";
        }
        else if (currentItString == "(") {
            if (it != (inputInfixVector.end() - 1)) { // if opening parenthesis, push into stack
                stack.push(currentItString);
            }
            else {
                outputPostfixString = "Error: Infix expression has mismatched parens!"; // last entry cannot be "("
                return false;
            }

        }
        else if (precedenceOfString(currentItString) == 1 || precedenceOfString(currentItString) == 2) { // if an operator ( +, -, *, / )
            if (it == (inputInfixVector.end() - 1)) { // last input cannot be an operator
                outputPostfixString = "Error: Missing operands in the expression";
                return false;
            }
            while (!stack.empty() && stack.top() != "(" && precedenceOfString(stack.top()) >= precedenceOfString(currentItString)) { // add stack elements to output according to operator precedence
                outputPostfixString += stack.top() + " ";
                stack.pop();
            }
            stack.push(currentItString); // put current element into stack after reducing stack
        }
        else if (currentItString == ")") { 
            if (precedenceOfString(previousItString) == 1 || precedenceOfString(previousItString) == 2) { // illegal to have operator adjacent to ")"
                outputPostfixString = "Error: Missing operands in the expression";
                return false;
            }
            while (!stack.empty() && stack.top() != "(") { // place and pop elements until the opening brace is found
                outputPostfixString += stack.top() + " ";
                stack.pop();
            }
            if (!stack.empty() && stack.top() == "(") { // finally remove the opening brace from the stack
                stack.pop();
            }
            else {
                outputPostfixString = "Error: Infix expression has mismatched parens!"; // missing bracket "(" 
                return false;
            }

        }
    }
    while (!stack.empty()) { // process remaining elements in the stack after main loop
        if (stack.top() != "(") {
            outputPostfixString += stack.top() + " ";
            stack.pop();
        }
        else {
            outputPostfixString = "Error: Infix expression has mismatched parens!"; // cannot have parenthesis in stack at this time
            return false;
        }
    }

    return true; // indicates no errors
}

// This function returns whether a given string can be evaluated i.e. contains no variables
// True indicates the string can be evaluated.
// False indicates the string cannot be evaluated.
bool isNumericalInput(const std::string& inputString) {
    for (std::string::const_iterator it = inputString.begin(); it != inputString.end(); ++it) {
        if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || *it == '_') { // checks if the i-th string char is a letter or an underscore
            return false;
        }
    }
    return true;
}

// Attempts to evaluate a postfix expression. outputPostfixString is used at the output and the boolean 
// return type is used to indicate whether the operation was performed successfully. 
// False indicates an error occurred. The error message will be added to the output string.
// True indicates there was no error.
bool evaluatePostfixExpression(const std::vector<std::string>& inputPostfixVector, std::string& outputPostfixString) {
    Stack<std::string> stack; // Stack to hold operands during evaluation

    for (std::vector<std::string>::const_iterator it = inputPostfixVector.begin(); it != inputPostfixVector.end(); ++it) { // loop through the inputPostfixVector

        if (!isNumericalInput(*it)) { // check if the expression can be evaluated...i.e. contains no variables
            outputPostfixString = ""; 
            return false; 
        }
    }

    // Now evaluate the vector
    for (std::vector<std::string>::const_iterator it = inputPostfixVector.begin(); it != inputPostfixVector.end(); ++it) {
        std::string currentItString = *it; // Current token

        
        if (precedenceOfString(currentItString) == 0) { // If the token is a operand, push it onto the stack
            stack.push(currentItString);
        }
        else { // is an operator

            if(stack.size() < 2 ) { // All operators are assumed to be binary operators
                outputPostfixString = "Error: Missing operand in postfix string. Unable to evaluate postfix string!";
                return false; 
            }

            char currentOperator = currentItString[0]; // Extract the operator for switch statement
            double firstOperandDouble, secondOperandDouble, operationResultDouble; // Used for calculations

            switch (currentOperator) {
                case '+': { // Addition
                    secondOperandDouble = std::stod(stack.top()); // Convert top stack operand string to double
                    stack.pop(); // Remove it from stack
                    firstOperandDouble = std::stod(stack.top()); // Convert top stack operand string to double
                    stack.pop(); // Remove it from stack
                    operationResultDouble = firstOperandDouble + secondOperandDouble; // Calculate result
                    stack.push(std::to_string(operationResultDouble)); // Push result back into stack
                    break; 
                }
                case '-': { // Subtraction
                    secondOperandDouble = std::stod(stack.top());
                    stack.pop();
                    firstOperandDouble = std::stod(stack.top());
                    stack.pop();
                    operationResultDouble = firstOperandDouble - secondOperandDouble;
                    stack.push(std::to_string(operationResultDouble));
                    break;
                }
                case '*': { // Multiplication
                    secondOperandDouble = std::stod(stack.top());
                    stack.pop();
                    firstOperandDouble = std::stod(stack.top());
                    stack.pop();
                    operationResultDouble = firstOperandDouble * secondOperandDouble;
                    stack.push(std::to_string(operationResultDouble));
                    break;
                }
                case '/': { // Division
                    secondOperandDouble = std::stod(stack.top());
                    stack.pop();
                    firstOperandDouble = std::stod(stack.top());
                    stack.pop();
                    if (secondOperandDouble == 0) { // Check for division by zero
                        outputPostfixString = "inf"; // Return "inf" if division by zero
                        return false; // Indicate error occurred
                    }
                    operationResultDouble = firstOperandDouble / secondOperandDouble; 
                    stack.push(std::to_string(operationResultDouble)); // Push result back into stack
                    break;
                }
            } 
        } 
    } 

    outputPostfixString = stack.top(); // The final result is the only element left in the stack
    return true; // Indicate successful evaluation
}