//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #1
//
//This is the header file for the Linked List Class

#ifndef LINKEDLIST_H  
#define LINKEDLIST_H

#include <string>
#include "Symbols.h"

struct Node
{
	Symbols *symbol;
	Node *link;
};

class LinkedList
{
	public:
		LinkedList();
		~LinkedList();
		Node *head;
		void createNode(std::string identifier, int valueFromString);
};

#endif
