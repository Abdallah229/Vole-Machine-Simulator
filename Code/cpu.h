#ifndef CPU_H
#define CPU_H
using namespace std;
#include "headers.h"
#include "memory.h"
#include "register.h"
#include "cu.h"
#include "methods.h"
#include "alu.h"

#include <string>
#include <regex>

class CPU
{
    private:
        CU cu;
        ALU alu;
        Register reg;
        string programCounter = "00";
        bool skip = false;
        string instructionRegister="";
        void fetch(Memory &memory  );
        vector<string> decode();
        void execute(vector<string> instruction, Memory &memory);
   
    public:
        void control(Memory &memory  );
        void print();
        void DisplayRegister() ;
        Register GetRegister() ;
        void setPc(string pc) ; 
        bool IsHalt  ;
        int IsJump  ;
        CPU(){ IsHalt = false , IsJump = 0 ; }
       
};
#endif // CPU_H