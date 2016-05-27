//J Andrew McCormick
//EECS 2150 - Non-Linear Data Structures
//Program 2
//
//This is the header file for the postfix evaluator

#ifndef POSTFIXEVALUATOR_H
#define POSTFIXEVALUATOR_H

#include <string>
#include "Stack.h"
#include "Tree.h"

long evaluatePostfixExpression(Stack<void *> *stack, std::string &postfixExpression, int &divZeroError);

#endif
