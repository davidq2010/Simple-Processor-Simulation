#ifndef ASM_PARSER_H_
#define ASM_PARSER_H_

#include "Instruction.h"
#include "RegisterTable.h"
#include "Opcode.h"

#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdexcept>
#include <vector>

using namespace std;

class ASMParser{
 public:
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
  vector<Instruction> operator() (string filename);

 private:
  vector<Instruction> myInstructions;      // list of Instructions
  bool myFormatCorrect;

  RegisterTable registers;                 // encodings for registers
  OpcodeTable opcodes;                     // encodings of opcodes

  // Decomposes a line of assembly code into strings for the opcode field and operands, 
  // checking for syntax errors and counting the number of operands.
  void getTokens(string line, string &opcode, string *operand, int &num_operands);

  // Given an Opcode, a string representing the operands, and the number of operands, 
  // breaks operands apart and stores fields into Instruction.
  bool getOperands(Instruction &i, Opcode o, string *operand, int operand_count);


  // Helper functions
  bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };
  bool isDigit(char c)         { return (c >= '0' && c <= '9'); };
  bool isSign(char c)          { return (c == '-' || c == '+'); };
  
  // Returns true if s represents a valid decimal integer
  bool isNumberString(string s);

  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
  unsigned long cvtNumString2Number(string s);

  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
  string encode(Instruction i);

  string encodeRType(Instruction& i);

  string encodeIType(Instruction& i);
  
  string encodeJType(Instruction& i);

  // Helper function convert a number to binary string
  string numberToBinary(unsigned long n, int len) {
  	string s = bitset<32>(n).to_string();
  	return s.substr(32 - len, len);
  }
};

#endif // ASM_PARSER_H_
