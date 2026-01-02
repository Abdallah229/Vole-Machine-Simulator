#include "register.h"
void Register::setCell(string RegAddress, string  value)
{
	   reg[RegAddress] = value;
	
}

string Register::getCell(string RegAddress)
{
	
	return reg[RegAddress];
}

map<string, string> Register::getReg()
{
    return reg;
}

