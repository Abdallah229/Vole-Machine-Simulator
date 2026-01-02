#include"methods.h"
#include"headers.h"
#include"register.h"
#include <bitset>

class ALU {
public:
    void add(string idx1, string idx2, string idx3, Register& reg);
    void floatingAdd(string idx1, string idx2, string idx3, Register& reg);
    void Or(string idx1, string idx2, string idx3, Register& reg);
    void And(string idx1, string idx2, string idx3, Register& reg);
    void Xor(string idx1, string idx2, string idx3, Register& reg);
    void rotate(string idx1, string idx3, Register& reg);
};