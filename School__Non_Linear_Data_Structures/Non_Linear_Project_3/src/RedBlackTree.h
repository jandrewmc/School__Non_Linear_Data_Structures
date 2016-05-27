//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project 3
//
//This is the header file for the Symbols class

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Symbols.h"

class RedBlackTree
{
	struct Node
	{
		char color;
		Symbols *symbol;
		Node *left;
		Node *right;
		Node *p;
	};

	private:
		Node *nil;
		Node *root;
		void performOperation(std::string identifier, std::string operation, int value);
		void insert(Node *z);
		void insertFixup(Node *z);
		void leftRotate(Node *x);
		void rightRotate(Node *x);
		void deletePostOrder(Node *node);
		void printTreeInOrder(Node *node, std::ofstream &out);
				
	public:
		RedBlackTree();
		~RedBlackTree();
		void processString(std::string input);
		void printTreeInOrder(std::ofstream &out);

};

#endif
