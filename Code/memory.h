#pragma once 

#include "headers.h"
using namespace std;

class Memory
{
private:
	// A map to store memory cells where the key is the memory address (as a string)
	// and the value is the data stored at that address
	map<string, string> memory;

public:
	// Constructor: Initializes the memory by calling the GenerateMemory function to Set Every Sell To "00"
	Memory() { GenerateMemory(memory); }

	// Getter function to retrieve the entire memory map
	map<string, string> getMemory();

	// Sets the value of a specific memory cell at the given address
	void setCell(string address, string value);

	// Retrieves the value of a specific memory cell at the given address
	string getCell(string address);
};
