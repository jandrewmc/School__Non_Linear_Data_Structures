//EECS 2150 - Non-Linear Data Structures
//J Andrew McCormick
//Project #1
//
//This is the header file for the Symbols class

#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>
#include <iostream>

class Symbols
{
	private:
		int value;
		std::string identifier;

	public:
		Symbols(std::string identifier, int value);
		void performOperation(std::string operation, int value);
		int lookup(std::string str);
		std::string toString();
};

#endif
