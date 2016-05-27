//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #1

#include "Symbols.h"

using namespace std;

//constructor that initializes identifier and value
Symbols::Symbols(string identifier, int value)
{
	this->identifier = identifier;
	this->value = value;
}

//This performes the operations based on the string operation 
//passed from the caller.
void Symbols::performOperation(string operation, int value)
{
	if (operation.compare("+=") == 0)
	{
		this->value += value;
	}
	else if (operation.compare("-=") == 0)
	{
		this->value -= value;
	}
	else if (operation.compare("*=") == 0)
	{
		this->value *= value;
	}
	else if (operation.compare("/=") == 0)
	{
		this->value /= value;
	}
	else
	{
		cout << "Error:  Didn't handle operation" << endl;
	}
}

//this returns the value of the method parameter compared to the identifier
//of the node we are working on. 
int Symbols::lookup(string str)
{
	return identifier.compare(str);
}
		
//output the string value of this object.
string Symbols::toString()
{
	return identifier + " = " + to_string(value);
}
