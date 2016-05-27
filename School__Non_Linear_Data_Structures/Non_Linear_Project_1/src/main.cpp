//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #1

#include <fstream>
#include "Symbols.h"
#include "LinkedList.h"

using namespace std;

const int MAX_INPUT_SIZE = 100;

void handleInput(string *&inputStringsArray);
void handleProcessing(string *&inputStringsArray, LinkedList *&list);
void handleOutput(LinkedList *&list);

void processArithmetic(string identifier, string operation, int valueFromString, LinkedList *&list);

//Main handles initializing the array of strings that will hold the input
//as well as initializing a pointer to the head of the linked list.
//There are 3 required phases to this project: input, processing, output
//each of the method calls in the main method correspond obviously to
//each of these phases.
int main()
{
	string *inputStringsArray = new string[MAX_INPUT_SIZE];
	LinkedList *list = new LinkedList();

	handleInput(inputStringsArray);	
	handleProcessing(inputStringsArray, list);
	handleOutput(list);	

	return 0;
}

//This handles outputting the data to a file. It asks the user to enter an 
//output file name.  It creates the file and outputs the data starting with
//the first node in the linked list and finishing with the last. 
void handleOutput(LinkedList *&list)
{
	//this will make sure you aren't overwriting a file that already exists
	string fileName;
	while (true)
	{
		cout << "Please enter a name for the output file: ";
		cin >> fileName;
		if(ifstream(fileName)) cout << "file already exists!" << endl;
		else break;
	}

	ofstream out(fileName);
	Node *currentNode;
	currentNode = list->head;
		
	//output to file from first node to last node.
	while (currentNode != nullptr)
	{
		out << currentNode->symbol->toString() << endl;
		currentNode = currentNode->link;
	}
//	out << "</end/>" << endl;
	out.close();
	delete list;
}

//This handles going through each line that was given as input and either
//a) creating a new node in the linked list for an initialization value
//or b) performing an arithmetic operation if the value has already
//been initialized.  We are assuming that the input text file has initialized
//an identifier before performing an arithmetic operation on it.
void handleProcessing(string *&inputStringsArray, LinkedList *&list)
{
	//start with the first line of input
	int index = 0;
	string lineOfInput = inputStringsArray[index];

	//here, we process each line until we reach the end of the file.
	while(lineOfInput.compare("</end/>") != 0)
	{
		//to use strtok, our line of input needs to be a cString
		char *cStringOfInput = new char[lineOfInput.length() + 1];
		strcpy(cStringOfInput, lineOfInput.c_str());
		
		//we assume the identifier, operator, and value are separated by a space or a tab
		string identifier(strtok(cStringOfInput, " \t"));
		string operation(strtok(NULL, " \t"));
		string value(strtok(NULL, " \t"));
		
		//convert value to an integer
		int valueFromString = stoi(value, nullptr, 0);

		if (operation.compare("=") == 0)
		{
			//create node if operation is an equals sign
			list->createNode(identifier, valueFromString);	
		}
		else
		{
			//if the operation is not =, it is an arithmetic operation
			processArithmetic(identifier, operation, valueFromString, list);
		}
		
		//place the next string from the input into lineOfInput 
		index++;
		lineOfInput = inputStringsArray[index];
	}
}

//Here we process any arithmetic operation that was in the file
void processArithmetic(string identifier, string operation, int valueFromString, LinkedList *&list)
{
	Node *currentNode;
	currentNode = list->head;
	
	//starting at the first node in the linked list	
	while (currentNode != nullptr)
	{
		//look for the identifier in the linked lsit
		if (currentNode->symbol->lookup(identifier) == 0)
		{
			//when it is found, perform the operation
			currentNode->symbol->performOperation(operation, valueFromString);
			//and leave the method
			return;
		}
		//if it wasn't found, go to the next node.
		currentNode = currentNode->link;
	}
	//if we get here, there was a problem in the input file
	cout << "You attempted to perform an arithmetic operation on an identifier that wasn't initialized!";
}

//Using ifstream, we will take in a text file whos name is entered at the
//command prompt, we will input each line as a new element in an array, that
//is passed in from the main method, and when the </end/> is reached, we are 
//done getting input.
void handleInput(string *&inputStringsArray)
{
	ifstream myfile;	
	string line;

	//if the file doesn't exist, you will be prompted to enter a different file name
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

	//populate the array with lines from the input file until the end is reached
	//or the maximum size is reached.
	while (myfile.is_open() && index < MAX_INPUT_SIZE)
	{
		getline(myfile,line);
		
		inputStringsArray[index] = line;

		if (line.compare("</end/>") == 0) break;
		
		index++;
	}
	
	myfile.close();
}
