#include "memory.h"


map<string, string> Memory::getMemory()
{
    return memory;
}

void Memory::setCell(string address, string value)
{
   
    memory[address] = value ;
    
}

string Memory::getCell(string address)
{
   
       return memory[address] ;
}

