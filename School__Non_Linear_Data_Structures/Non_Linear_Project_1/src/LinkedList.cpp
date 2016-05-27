//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #1

#include "LinkedList.h"
#include "Symbols.h"

using namespace std;

//Constructor, handles initializing head pointer to null
LinkedList::LinkedList()
{
	this->head = nullptr;
}

//Destructor:  Handles deleting the linked list
LinkedList::~LinkedList()
{
	Node *currentNode = head;
	Node *nextNode;
	nextNode = currentNode;
	while (nextNode != nullptr)
	{
		nextNode = currentNode->link;
		delete currentNode->symbol;
		currentNode->link = nullptr;
		delete currentNode;
		currentNode = nextNode;
	}
	head = nullptr;	
}

//When an initialization is requested from the input file, we create a new node in our linked list
//as an additional feature, we are going to create our linked list in alphabetical order
void LinkedList::createNode(string identifier, int valueFromString)
{
	//create a new node in memory and initialize the Symbols object;
	Node *node = new Node();
	node->symbol = new Symbols(identifier, valueFromString);
	//set its link to null
	node->link = nullptr;

	//if it is the first node in the linked list
	if (head == nullptr)
	{
		//set the head to point to the node
		head = node;	
	}	
	else
	{
		//otherwise, we need to keep track of our current node and previously visited node.
		Node *currentNode;
		Node *previousNode;

		//at first, we will set them both equal to the head
		currentNode = head;
		previousNode = head;

		//we will continue going through the list until one of the following conditions is met.
		while (true)
		{
			//we will get the result of the comparison between the head identifier and the identifier of the first
			int result = head->symbol->lookup(identifier);

			//if the value of identifier is less than the value of the current node we are on
			if (result > 0)
			{
				//then if we are on the first node in the list, it becomes the new first node
				if (currentNode == previousNode)
				{
					node->link = currentNode;
					head = node;
					return;
				}				
				//otherwise, it goes before the node we are currently on
				else
				{
					node->link = currentNode;
					previousNode->link = node;
					return;
				}
			}
			//if the value of identifier is greater than the current node we are on
			else if (result < 0)
			{
				//then if we are at the endo of the list, it becomes the last node in the list
				if (currentNode->link == nullptr)
				{
					currentNode->link = node;
					return;
				}	
				//otherwise, we navigate to the next node and loop again
				else
				{	
					previousNode = currentNode;
					currentNode = currentNode->link;
				}
			}
			//if the value of the identifier isnt greater or less than it is equal and we have a problem
			else
			{
				cout << "You are trying to initialize an identifier that already exists!" << endl;
			}
		}
	}
}
