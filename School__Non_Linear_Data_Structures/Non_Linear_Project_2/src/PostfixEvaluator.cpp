
#include "PostfixEvaluator.h"
#include "Tree.h"

using namespace std;

//this function will check to see if the token is an operator
static bool isOperator(char token)
{
	return (token == '+') || (token == '-') || (token == '*') || (token == '/');
}

//this evaluates the tree in order
long eval(TreeNode<char *> *root, int &divZeroError)
{
	long op1;
	long op2;
	switch (root->info[0])
	{
		case '+':
			return eval(root->left, divZeroError) + eval(root->right, divZeroError);
		case '-':
			return eval(root->left, divZeroError) - eval(root->right, divZeroError);
		case '*':
			return eval(root->left, divZeroError) * eval(root->right, divZeroError);
		case '/':
			//here we set the divide by zero flag if we attempt to divide by zero
			//since the result will be thrown out, we just return zero and don't
			//actually compute the divide by zero
			op1 = eval(root->left, divZeroError);
			op2 = eval(root->right, divZeroError);
			if (op2 == 0)
			{
				divZeroError = 1;
				return 0;
			}
			return op1 / op2;
		default:
			return atoi(root->info);
	}
}

//this function deletes the tree
void postOrderDelete(TreeNode<char *> *root)
{
	if (root != nullptr)
	{
		postOrderDelete(root->left);
		postOrderDelete(root->right);
		delete root->left;
		delete root->right;
	}
}

//this function creates the binary tree from the postfix expression
long evaluatePostfixExpression(Stack<void *> *stack, string &postfixExpression, int &divZeroError)
{
	Tree<char *> tree(stack);

	char *s = (char *)postfixExpression.c_str();

	//get each token separated by a space
	char *token = strtok(s, " ");

	while (token != NULL)
	{
		if (isOperator(*token))
		{
			tree.addOperatorNode(token);	
		}
		else
		{
			tree.addNumericNode(token);
		}
		//get next token
		token = strtok(NULL, " ");
	}

	//the top item on the stack is the root of the tree
	TreeNode<char *> *root = (TreeNode<char *> *)stack->top();
	stack->pop();

	//evaluate tree
	int result = eval(root, divZeroError);

	//once evaluated, delete the tree
	postOrderDelete(root);
	delete root;

	return result;
}
