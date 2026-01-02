#ifndef _CU_H
#define _CU_H
#include "headers.h"
#include "register.h"
#include "memory.h"
class CU
{
public:
void Load (string idxReg , string MemAddress , Register &R , Memory &M) ;
void Load (string idxReg , string value , Register &R ) ;
void Store (string idxReg , string MemAddress, Register &R , Memory & M ) ;
void Move (string idxReg1 , string idxReg2 , Register &R  ) ;
int Jump (string idxReg1 , string MemAddress, Register &R , string & PC  ) ;
bool Halt () ;
    
};
#endif 