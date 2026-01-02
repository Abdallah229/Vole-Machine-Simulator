#include "cpu.h"
#define GREEN "\e[32m"
#define RESET "\e[0m"

void CPU::fetch(Memory & memory ){
    //read the instruction from memory
    int tempPCIR  = hexToDec(programCounter);
    tempPCIR += 1;
    string finalPCIR = decToHex(tempPCIR);
    instructionRegister = memory.getCell(programCounter) + memory.getCell(finalPCIR);
    cout << "Instruction Register : " <<instructionRegister <<endl << endl;
    int temp_PC = hexToDec(programCounter);
    temp_PC += 2;
    if (temp_PC > 256)
    {
        cout << "Memory Full !!\n";
        IsHalt = true;
    }
    programCounter = decToHex(temp_PC);
}
////////////////////////////////////////////////////////////////////////////
vector<string> CPU::decode(){
    // decode the instruction
    string opCodeHex = instructionRegister.substr(0, 1);
    string R_Hex= instructionRegister.substr(1, 1);
    string XY_Hex = instructionRegister.substr(2, 2);
    string X_Hex = instructionRegister.substr(2, 1);
    string Y_Hex = instructionRegister.substr(3, 1);
    return {opCodeHex, R_Hex, XY_Hex , X_Hex ,Y_Hex };
}
////////////////////////////////////////////////////////////////////////////

void CPU::execute(vector<string> instruction, Memory & memory){
    // Check if the CPU has faced a halt command
    if (IsHalt)
    {
        return;
    }
    // Execute the instruction
    char OpCode = instruction[0][0];
    string idxReg = instruction[1];
    string idxXY = instruction[2];    
    string idxX = instruction[3];    
    string idxY = instruction[4];
    switch (OpCode)
    {
    case '1':
        cu.Load(idxReg, idxXY, reg, memory);
        break;

    case '2':
        cu.Load(idxReg, idxXY, reg);
        break;

    case '3':
        cu.Store(idxReg, idxXY, reg, memory);
        break;

    case '4':
        if (idxReg[0] == '0')
        { // Check for valid format 0RS
            cu.Move(idxX,idxY , reg);
        }
        else
        {
              cerr << "Error: Invalid MOVE instruction format" <<   endl;
        }
        break;
    case '5':
        alu.add(idxReg, idxX, idxY, reg);       
        break; 
    case '6':
        alu.floatingAdd(idxReg, idxX, idxY, reg);       
        break;
    case '7':
        alu.Or(idxReg, idxX, idxY, reg);
        break;
    case '8':
        alu.And(idxReg, idxX, idxY, reg);
        break;
    case '9':
        alu.Xor(idxReg, idxX, idxY, reg);
        break;
    case 'A':
        if (idxX[0] == '0'){
            alu.rotate(idxReg, idxY, reg);
        }
        else
        {
            cerr << "Error: Invalid ROTATE instruction format" <<   endl;
        }
        break;
    case 'B':
        IsJump  = cu.Jump(idxReg, idxXY, reg, programCounter);
        break;
    case 'C':
        this -> IsHalt = cu.Halt()  ;
        return ;

    default:
        break;
    }
}
// orchestrate all of the processes
void CPU::control(Memory & memory  ){
    fetch(memory);
    vector<string> decoded = decode();
    execute(decoded, memory);
}
void CPU :: DisplayRegister()
{
    for (size_t i = 0; i < 16; i++)
    {
        string ch;
        if (i >= 10 && i <= 15)  ch = static_cast<char>('A' + (i - 10)); // Converts 10-15 to 'A'-'F'
        else   ch = static_cast<char>('0' + i); // Converts 0-9 to '0'-'9'
        if (reg.getCell(ch) != "00") cout << "R" << ch << "    " << GREEN << reg.getCell(ch)  <<RESET << endl;
        else cout << "R" << ch << "    " << reg.getCell(ch)  << endl;
    }
}
////////////////////////////////////////////////////////////////////////////
void CPU::print(){
    cout << "CPU is working." << endl;
}
////////////////////////////////////////////////////////////////////////////
Register CPU::GetRegister()
{
    return reg;
}

void CPU::setPc(string pc)
{
    programCounter = pc ;
}

////////////////////////////////////////////////////////////////////////////
