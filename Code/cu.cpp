#include "cu.h"
// Control Unit --> CU

// Load a value from a specified memory address into a register cell
void CU::Load(string idxReg, string MemAddress, Register &R, Memory &M)
{
    R.setCell(idxReg, M.getCell(MemAddress)); // Set the register cell at idxReg with the memory cell at MemAddress
}

// Load a direct value into a specified register cell
void CU::Load(string idxReg, string value, Register &R)
{
    R.setCell(idxReg, value); // Set the register cell at idxReg with  value
}

// Store the value from a specified register cell into a memory address
void CU::Store(string idxReg, string MemAddress, Register &R, Memory &M)
{
    if(MemAddress == "00") 
    {
        M.setCell(MemAddress, R.getCell(idxReg)); // Set the memory cell at MemAddress with the value in register cell idxReg
        cout << "Displaying Memory cell At Address 00: " << M.getCell("00") << endl ; 
    }
    else 
    {
        M.setCell(MemAddress, R.getCell(idxReg)); 
    }
}

// Move the value from one register cell to another within the register
void CU::Move(string idxReg1, string idxReg2, Register &R)
{
    R.setCell(idxReg2, R.getCell(idxReg1)); // Copy the value from idxReg1 to idxReg2 in the register
}

// Conditional jump based on the value in the specified register cell
int CU::Jump(string idxReg, string MemAddress, Register &R, string &PC)
{
    // If the value in register cell "0" equals the value in idxReg, perform the jump
    if (R.getCell("0") == R.getCell(idxReg))
    {
        int temp = hexToDec(PC);       // Convert the current PC to decimal for calculation
        PC = MemAddress;               // Set the program counter (PC) to the new memory address
        int res = hexToDec(PC) - temp; // Calculate the offset from the original PC
        return res;                    // Return the jump offset
    }
    return 0; // No jump performed if condition is not met
}

// Halt operation, returns true to indicate the halt condition
bool CU::Halt()
{
    return true; // Indicates that the system should halt
}
