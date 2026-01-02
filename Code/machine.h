#ifndef MACHINE_H
#define MACHINE_H // Include guard to prevent multiple inclusions of this header file


#include "cpu.h"
#include "memory.h"
#include "headers.h"
#include "methods.h"

// The Machine class represents the main processing unit, containing memory, a CPU, and instructions
class Machine 
{
  private:
    Memory memoryMachine;           // An instance of the Memory class to manage machine memory
    CPU cpu;                        // An instance of the CPU class to manage CPU-related operations
    vector<string> Instructions;    // A vector to store the machine's instructions
    string StartIterate;            // Stores the starting address for iteration
    int InstSize ;

public:
  void loadMemory(vector<string> Instructions);
  void loadProgram();
  // Outputs the current state of the machine's memory and CPU registers
  void stateOut();

  // Friend function: Allows DisplayMemory to access The Memory of Machine
  friend void DisplayMemory(Memory Mem);

  // Runs the machine with the provided instructions
   void RunMachine();
   void setInstructions(vector<string>  Inst) ;
   //string getStartIterate () ;
   bool IsHalt; // A flag indicating whether the machine has halted (true if halted)
};

#endif // MACHINE_H
