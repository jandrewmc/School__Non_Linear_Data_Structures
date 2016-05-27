//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #2
//
//This is the main file that orchestrates the whole program

#include <fstream>
#include "InfixToPostfix.h"
#include "PostfixEvaluator.h"

using namespace std;

//This function will return the file name entered for the input file
//if the file doesn't exist, it will ask for one until it gets a valid
//file name
string getInputFilename()
{
	ifstream myfile;
	string filename;
	while (true)
	{
		cout << "Please enter the input file name: ";
		cin >> filename;

		myfile.open(filename);

		//if the file is good, leave the loop
		if(myfile.good()) 
		{
			break;	
		}
		else
		{
			cout << "You entered an invalid file name!" << endl;	
		}
	}
	myfile.close();
	return filename;
}

//This function will return the file name entered for the output file
//if the file name matches an existing file, it will ask for a new filename 
string getOutputFilename()
{
	string filename;
	while (true)
	{
		cout << "Please enter a name for the output file: ";
		cin >> filename;

		if(ifstream(filename)) cout << "file already exists!" << endl;
		else break;
	}
	return filename;
}

//This function handles getting the input from a file
void handleInput()
{
	//we create variables for a stack and a string
	Stack<void *> stack;
	string line;

	//we get the input file
	ifstream infile;
	infile.open(getInputFilename());

	//and get the output file ready
	ofstream outfile(getOutputFilename());

	//while the input file is open
	while (infile.is_open())
	{
		//get the next line
		getline(infile, line);		

		//leave the loop if we reach the end of the file
		if(infile.eof())
			break;

		//add a string terminator to the input
		line += '$';

		//create an error flag that gets set if we ever attempt to divide by zero
		int divZeroError = 0;

		//get the infix expression
		string value = convertInfixToPostfix(line, &stack);

		//evaluate the infix expression
		int result = evaluatePostfixExpression(&stack, value, divZeroError);

		//if we attempted a divide by zero, output that we cannot do that
		if (divZeroError == 1)
		{
			outfile << "Cannot divide by 0" << endl;
			continue;
		}

		//write the result to the output file
		outfile << result << endl;
	}

	infile.close();
	outfile.close();
}

//main method that calls handle input
int main()
{
	handleInput();

	return 0;
}

