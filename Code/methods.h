#ifndef _METHODS_H
#define _METHODS_H
#include "headers.h"
using namespace std ;

/// Get Instruction from File  Functions
string GetPath();
string GetFileContent();
bool CheckInst(string Inst);
vector<string> ExtractInst(string Content );
/// Converters Functions
int stringToInt(const string &str);
string decToHex(int dec);
int hexToDec(string hex);
string hexToBin(const string &hex);
string binToHex(const string &bin);
char ConvertDigit(int i) ;
///Operations On Binary Functions
string addBin(string bin1, string bin2);
string subBin(const string &bin1, const string &bin2);
/// Functions To Generate The Machine Components 
void GenerateMemory(map<string , string > &m ) ;
void GenerateRegister(map<string , string > &r ) ;
/// Functions For Menu
char GetChoice(const string &Message, const string &Choices, char Start, char End) ;
bool IsPowerOf2(int num);
bool IsStartValid(string &str) ;
bool isHex(string &str) ;
#endif