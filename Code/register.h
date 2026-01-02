#pragma once 

#include "headers.h"
using namespace std;

class Register
{
private:
	// A map to store register values, where each key is the register address
	// (as a string), and each value is the data stored in that register
	map<string, string> reg;

public:
	// Constructor: Initializes the register by calling the GenerateRegister function And Set Every sell to "00"
	Register() { GenerateRegister(reg); }

	// Sets the value of a specific register cell at the given register address
	void setCell(string RegAddress, string value);

	// Retrieves the value of a specific register cell at the given register address
	string getCell(string RegAddress);

	// Getter function to retrieve the entire register map
	map<string, string> getReg();
};
