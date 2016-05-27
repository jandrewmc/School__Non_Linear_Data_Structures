
#include "InfixToPostfix.h"

using namespace std;

//check to see if the currentChar is a left parenthesis
bool isLeftParen(char currentChar)
{
	return currentChar == '(';
}

//check to see if the current character is a right parenthesis
bool isRightParen(char currentChar)
{
	return currentChar == ')';
}

//check to see if the current character is an operator
static bool isOperator(char currentChar)
{
	return (currentChar == '+') || (currentChar == '-') || (currentChar == '*') || (currentChar == '/');
}

//if the current character is a right parenthesis
void processRightParen(Stack<void *> *&stack, string &finalExpression)
{
	//get the top token on the stack
	char *topToken = (char *) stack->top();

	//while it isnt a left parenthesis
	while (!isLeftParen(*topToken))
	{
		//add it to the postfix expression
		finalExpression += *topToken;
		finalExpression += " ";

		//pop the stack
		stack->pop();	

		//and get the next token on the stack
		topToken = (char *) stack->top();
	}

	//pop the stack when done
	stack->pop();
}

//if the current character is an operator
void processOperator(char *currentOperator, Stack<void *> *stack, string &finalExpression)
{
	//get the top token on the stack
	char *topToken = (char *) stack->top();

	//while the stack is not empty and the token is not a left parenthesis
	while (!stack->isEmpty() && !isLeftParen(*topToken))
	{
		//append top token to the postfix expression
		finalExpression += *topToken;
		finalExpression += " ";

		//pop the stack
		stack->pop();

		//get the next token
		topToken = (char *) stack->top();
	}

	//when done, append the operator to the stack
	stack->push(currentOperator);
}

//check to see if the current character is whitespace
bool isWhitespace(char currentChar)
{
	return (currentChar == ' ') || (currentChar == '\t');
}

//this function will convert the infix string to a postfix expression
string convertInfixToPostfix(string infixExpression, Stack<void *> *stack)
{
	const char *curC = infixExpression.c_str();
	string finalExpression = "";

	long value = 0;	

	//while the current character is not a new line character
	for (; *curC != '$'; curC++)
	{
		//skip character if it is whitespace
		if (isWhitespace(*curC)) continue;

		//if the current character is a left parenthesis, push it onto the stack
		if (isLeftParen(*curC))
		{
			stack->push((void *)curC);
		}
		else if (isRightParen(*curC))
		{
			processRightParen(stack, finalExpression);
		}
		else if (isOperator(*curC))
		{
			processOperator((char *)curC, stack, finalExpression);
		}
		else
		{
			//character, by character, build the value of the number in the infix expression
			value *= 10;
			value += (*curC - '0');

			//if the next character is not a digit
			if (!isdigit(*(curC + 1)))
			{
				finalExpression += to_string(value);
				finalExpression += " ";
				value = 0;
			}
		}
	}
	return finalExpression;
}

