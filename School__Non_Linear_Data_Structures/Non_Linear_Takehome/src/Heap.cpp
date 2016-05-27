//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Takehome Project

#include "Heap.h"

using namespace std;

//Default constructor, sets default values to zero
Heap::Heap()
{
	this->heapsize = 0;
	this->length = 0;
}

//Destructor, deletes all the objects in the heap
Heap::~Heap()
{
	for (int i = 1; i <= length; i++)
	{
		delete heap[i];
	}
}

//This method takes a line from the input file
void Heap::addToHeap(string lineOfInput)
{
	char *cStringOfInput = new char[lineOfInput.length() + 1];
	strcpy(cStringOfInput, lineOfInput.c_str());
	
	//brakes the input line into its parts 
	string identifier(strtok(cStringOfInput, " \t"));
	string operation(strtok(NULL, " \t"));
	string value(strtok(NULL, " \t"));

	int valueFromString = stoi(value, nullptr, 0);

	//if the line of input is an initialization line, add it to the heap
	if (operation.compare("=") == 0)
	{
		length++;
		heap[length] = new Symbols(identifier, valueFromString);
	}
	//otherwise, perform the given operation on the correct identifier
	else
	{
		for(int index = 1; index <= length; index++)
		{
			if (heap[index]->lookup(identifier) == 0)	
			{
				heap[index]->performOperation(operation, valueFromString);
			}
		}
	}
	delete [] cStringOfInput;
}

//This method performs max heapify
void Heap::maxHeapify(int root)
{
	int leftChild = lChild(root);
	int rightChild = rChild(root);
	int largest = 0;

	//find the largest of the root and the left child
	if (leftChild <= heapsize && heap[leftChild]->lookup(heap[root]->getIdentifier()) >= 1)
	{
		largest = leftChild;
	}
	else
	{
		largest = root;
	}
	
	//take that largest and find the largest between that and the right child
	if (rightChild <= heapsize && heap[rightChild]->lookup(heap[largest]->getIdentifier()) >= 1)
	{
		largest = rightChild;
	}

	//as long as the largest isnt the root, make the largest the root and run max heapify on the largest again
 	if (largest != root)
	{
		exchange(root, largest);
		maxHeapify(largest);
	}
}

//This builds a max heap.  run max heapify on each element in half of the array
void Heap::buildMaxHeap()
{
	heapsize = length;
	for (int i = heapsize / 2; i >= 1; i--)
	{
		maxHeapify(i);
	}
}

//Heapsort.  Build a max heap, then run max heapify to sort.
void Heap::heapsort()
{
	buildMaxHeap();

	for (int i = length; i >= 2; i--)
	{
		exchange(1,i);
		heapsize--;
		maxHeapify(1);
	}
}

//swaps the contents of two indices
void Heap::exchange(int index1, int index2)
{
	Symbols *temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}

//get the left child of the given index
int Heap::lChild(int index)
{
	return 2 * index;
}

//get the right child of the given index
int Heap::rChild(int index)
{
	return 2 * index + 1;
}

//get the parent of the given index
int Heap::parent(int index)
{
	return index / 2;
}
