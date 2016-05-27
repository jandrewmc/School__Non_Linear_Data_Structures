//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #2

#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>

//This defines the template for a generic Stack.
template <class T>
class Stack
{
	public:
		Stack();
		~Stack();

		void push(T info);
		void pop();
		T top();
		bool isEmpty();

	private:
		LLNode<T> *topOfStack;
};

//set the top of the stack to null when constructed
template <class T>
Stack<T>::Stack()
{
	this->topOfStack = nullptr;
}

//the deconstructor goes throught the stack and destroys all remaining items on the stack
template <class T>
Stack<T>::~Stack()
{
	while (!isEmpty())
	{
		LLNode<T> *currentTop = topOfStack;
		topOfStack = topOfStack->link;

		currentTop->link = nullptr;
		delete currentTop;
	}
}

//If a push to the stack is requested
template <class T>
void Stack<T>::push(T info)
{
	LLNode<T> *newNode = new LLNode<T>();
	newNode->info = info;

	//if the stack is currently empty, set the top of the stack to the new node
	if (topOfStack == nullptr)
	{
		topOfStack = newNode;
	}
	//otherwise, have the new node link to the top of the stack and set the top 
	//of the stack to the new node.
	else
	{
		newNode->link = topOfStack;
		topOfStack = newNode;
	}
}

//if a pop is attempted
template <class T>
void Stack<T>::pop()
{
	//make sure the stack is not empty
	if (isEmpty())
	{
		std::cout << "pop attempted on an empty stack" << std::endl;
		return;
	}

	//remove the top item of the stack
	LLNode<T> *currentTop = topOfStack;
	topOfStack = currentTop->link;

	currentTop->link = nullptr;
	//and delete that node
	delete currentTop;
}

//if a top is attempted
template <class T>
T Stack<T>::top()
{
	//make sure the stack is not empty
	if (isEmpty())
	{
		std::cout << "top attempted on an empty stack" << std::endl;
		return NULL;
	}
	//return the info from the top of the stack
	return topOfStack->info;
}

//check to see if the stack is empty
template <class T>
bool Stack<T>::isEmpty()
{
	return topOfStack == nullptr;
}

#endif
