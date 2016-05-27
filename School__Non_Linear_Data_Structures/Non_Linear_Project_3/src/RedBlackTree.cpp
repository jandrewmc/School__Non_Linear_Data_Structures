//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #3

#include "RedBlackTree.h"

using namespace std;

//this is the red black tree constructor
//and it creates a nil node as the sentinel
//node for the tree
RedBlackTree::RedBlackTree()
{
	Node *node = new Node();
	node->symbol = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->color = 'B';
	root = node;
	nil = node;	
	node->p = nil;
}

//destructor deletes the RBT (red black
//tree)
RedBlackTree::~RedBlackTree()
{
	deletePostOrder(root);
}

//deletes the tree post order
void RedBlackTree::deletePostOrder(Node *node)
{
	if (node != nil)
	{
		deletePostOrder(node->left);
		deletePostOrder(node->right);
		delete node->symbol;
		delete node;
	}
}

//this is the method called from the  main method
//and handles each item from the input file
void RedBlackTree::processString(string input)
{
	char *cStringOfInput = new char[input.length() + 1];
	strcpy(cStringOfInput, input.c_str());

	//break apart the string on tokens
	string identifier(strtok(cStringOfInput, " \t"));
	string operation(strtok(NULL, " \t"));
	string value(strtok(NULL, " \t"));

	//convert the value to an int
	int valueFromInput = stoi(value, nullptr, 0);

	//if it is an identifier
	if (operation.compare("=") == 0)
	{	
		//create the node
		Node *node = new Node();
		node->symbol = new Symbols(identifier, valueFromInput);
		node->left = nullptr;
		node->right = nullptr;

		//insert node into tree
		insert(node);	
	}
	else
	{
		//if it isnt an identifier, it is a mathematical
		//operation.  perform the operation
		performOperation(identifier, operation, valueFromInput);
	}

	delete [] cStringOfInput;
}

//this handles the red black tree node insertion
void RedBlackTree::insert(Node *z)
{
	Node *y = nil;
	Node *x = root;
	while (x != nil)
	{
		y = x;
		if (z->symbol->lookup(x->symbol->getIdentifier()) < 0)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	z->p = y;
	if (y == nil)
	{
		root = z;
	}
	else if (z->symbol->lookup(y->symbol->getIdentifier()) < 0)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = 'R';
	insertFixup(z);
}

//this handles the fixup for the insert
void RedBlackTree::insertFixup(Node *z)
{
	while (z->p->color == 'R')	
	{
		if (z->p == z->p->p->left)
		{
			Node *y = z->p->p->right;
			if (y->color == 'R')
			{
				z->p->color = 'B';
				y->color = 'B';
				z->p->p->color = 'R';
				z = z->p->p;
			}
			else if (z == z->p->right)
			{
				z = z->p;
				leftRotate(z);
			}
			else
			{
				z->p->color = 'B';
				z->p->p->color = 'R';
				rightRotate(z->p->p);
			}
		}
		else
		{
			Node *y = z->p->p->left;
			if (y->color == 'R')
			{
				z->p->color = 'B';
				y->color = 'B';
				z->p->p->color = 'R';
				z = z->p->p;
			}
			else if (z == z->p->left)
			{
				z = z->p;
				rightRotate(z);
			}
			else
			{
				z->p->color = 'B';
				z->p->p->color = 'R';
				leftRotate(z->p->p);
			}
		}
	}
	root->color = 'B';
}

//this handles the left rotate
void RedBlackTree::leftRotate(Node *x)
{
	Node *y = x->right;
	x->right = y->left;
	if (y->left != nil)
	{
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == nil)
	{
		root = y;
	}
	else if (x == x->p->left)
	{
		x->p->left = y;
	}
	else
	{
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

//this handles the right rotate
void RedBlackTree::rightRotate(Node *x)
{
	Node *y = x->left;
	x->left = y->right;

	if (y->right != nil)
	{
		y->right->p = x;
	}
	y->p = x->p;
	if (x->p == nil)
	{
		root = y;
	}
	else if (x == x->p->right)
	{
		x->p->right = y;
	}
	else
	{
		x->p->left = y;
	}
	y->right = x;
	x->p = y;
}

//this method looks up the node and performs the operation
void RedBlackTree::performOperation(string identifier, string operation, int value)
{
	Node *node = root;

	while (node->symbol->lookup(identifier) != 0)
	{
		if (node->symbol->lookup(identifier) < 0)
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}

	node->symbol->performOperation(operation, value);
}

//public facing method for printing the tree in order
//this exists to keep the root of the tree private
void RedBlackTree::printTreeInOrder(ofstream &out)
{
	printTreeInOrder(root, out);
}

//this prints the tree to file in order
void RedBlackTree::printTreeInOrder(Node *node, ofstream &out)
{
	if (node != nil)
	{
		printTreeInOrder(node->left, out);
		out << node->symbol->toString() << endl;
		printTreeInOrder(node->right, out);
	}
}
