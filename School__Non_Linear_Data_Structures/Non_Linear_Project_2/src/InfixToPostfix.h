//J Andrew McCormick
//EECS 2150 Non-Linear Data Structures
//Project #2
//
//This is the header file for the Infix to Postfix converter 

#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H

#include <string>
#include "Stack.h"

std::string convertInfixToPostfix(std::string infixExpression, Stack<void *> *stack);

#endif
