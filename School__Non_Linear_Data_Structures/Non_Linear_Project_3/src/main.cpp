//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #1

#include <fstream>
#include "RedBlackTree.h"

using namespace std;

const int MAX_INPUT_SIZE = 1000000;

//This method gets the input from the file, it asks
//for the file name from the user and adds the items
//to an array
void handleInput(string inputStringsArray[])
{
	ifstream myfile;	
	string line;

	//get a file from the user
	while (true)
	{
		cout << "Please enter the input file name: ";
		string fileName;
		cin >> fileName;
		myfile.open(fileName);
		if(myfile.good()) break;
		cout << "You entered an invalid file name!" << endl;
	}
	
	int index = 0;

	//get each line of the input file and store it in an array
	while (myfile.is_open() && index < MAX_INPUT_SIZE)
	{
		getline(myfile,line);
		
		inputStringsArray[index] = line;

		if (line.compare("</end/>") == 0) break;
		
		index++;
	}
	
	myfile.close();
}

//This method takes the array of input lines and adds them to the 
//heap. After building the heap, we run heapsort.
void handleProcessing(string inputStringsArray[], RedBlackTree *tree)
{
	int inputStringsIndex = 0;
	string lineOfInput = inputStringsArray[inputStringsIndex];

	while(lineOfInput.compare("</end/>") != 0)
	{
		//process the string using the tree
		tree->processString(lineOfInput);
		
		inputStringsIndex++;
		lineOfInput = inputStringsArray[inputStringsIndex];
	}
}

//This method outputs the sorted heap to a file whose filename
//is given by the user at the console.
void handleOutput(RedBlackTree *tree)
{
	string fileName;
	while (true)
	{
		cout << "Please enter a name for the output file: ";
		cin >> fileName;
		if(ifstream(fileName)) cout << "file already exists!" << endl;
		else break;
	}

	ofstream out(fileName);

	//print out the tree
	tree->printTreeInOrder(out);

	out.close();
}

//Main method.  Creates the array for input strings and the heap
//then handles input, processing, and output.
int main()
{
	string *inputStringsArray = new string[MAX_INPUT_SIZE];
	RedBlackTree *tree = new RedBlackTree();

	handleInput(inputStringsArray);	
	handleProcessing(inputStringsArray, tree);
	handleOutput(tree);

	delete tree;
	delete [] inputStringsArray;

	return 0;
}
