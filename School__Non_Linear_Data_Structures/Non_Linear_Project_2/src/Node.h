//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project 2

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//template for tree node
template <typename T>
struct TreeNode
{
	T info;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
};

//template for linked list node
template <typename T>
struct LLNode
{
	T info;
	LLNode *link;
};

#endif
