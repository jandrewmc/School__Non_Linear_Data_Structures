//J Andrew McCormick
//EECS 2150 Non-Linear Data Structures
//Project #2

#ifndef TREE_H
#define TREE_H

#include "Stack.h"
#include "Node.h"

//Tree class template.
template <class T>
class Tree
{
	public:
		Tree(Stack<void *> *stack);

		void addOperatorNode(T token);
		void addNumericNode(T token);

	private:
		Stack<void *> *stack;
};

//constructor with void pointer stack passed in
template <class T>
Tree<T>::Tree(Stack<void *> *stack)
{
	this->stack = stack;
}

//if the token to be added is an operator
template <class T>
void Tree<T>::addOperatorNode(T token)
{
	TreeNode<T> *newNode = new TreeNode<T>();

	newNode->info = token;

	TreeNode<T> *child;

	child = (TreeNode<T> *)stack->top();
	stack->pop();

	//the top item on the stack is the right child
	newNode->right = child;

	child = (TreeNode<T> *)stack->top();
	stack->pop();

	//the next item is the left child
	newNode->left = child;

	//the result should be pushed onto the stack
	stack->push(newNode);
}

//if the token to be added is a number
template <class T>
void Tree<T>::addNumericNode(T token)
{
	TreeNode<T> *newNode = new TreeNode<T>();

	newNode->info = token;

	//add it to the stack as a new tree node
	stack->push(newNode);
}

#endif

