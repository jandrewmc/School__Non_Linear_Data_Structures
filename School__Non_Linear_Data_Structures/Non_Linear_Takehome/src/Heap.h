//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Takehome Project
//
//This is the header file for the Heap class

#ifndef HEAP_H
#define HEAP_H

#include "Symbols.h"

class Heap
{
	private:
		int heapsize;
		void exchange(int index1, int index2);
		int lChild(int index);
		int rChild(int index);
		int parent(int index);

	public:
		Symbols *heap[101];
		int length;

		Heap();
		~Heap();
		void addToHeap(std::string lineOfInput);	
		void maxHeapify(int index);
		void buildMaxHeap();
		void heapsort();
};

#endif
