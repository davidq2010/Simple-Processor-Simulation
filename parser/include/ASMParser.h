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


class ASMParser{
 public:
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
  vector<Instruction> operator() (std::string _file_name);

 private:
  std::vector<Instruction> myInstructions; // list of Instructions

  RegisterTable registers;                 // encodings for registers
  OpcodeTable opcodes;                     // encodings of opcodes

  // Decomposes a line of assembly code into strings for the opcode field and operands,
  // checking for syntax errors and counting the number of operands.
  void getTokens(std::string line, std::string &opcode,
                 std::string *operand, int &num_operands);

  // Given an Opcode, a string representing the operands, and the number of operands,
  // breaks operands apart and stores fields into Instruction.
  bool getOperands(Instruction &i, Opcode o, std::string *operand, int operand_count, unsigned long inst_address);


  // Helper functions
  bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };
  bool isDigit(char c)         { return (c >= '0' && c <= '9'); };
  bool isSign(char c)          { return (c == '-' || c == '+'); };

  // Returns true if s represents a valid decimal integer
  bool isNumberString(std::string s);

  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
  unsigned long cvtNumString2Number(std::string s);

  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
  std::string encode(Instruction i);

  std::string encodeRType(Instruction& i);

  std::string encodeIType(Instruction& i);

  std::string encodeJType(Instruction& i);

  // Helper function convert a number to binary string
  std::string numberToBinary(unsigned long n, int len) {
  	std::string s = bitset<32>(n).to_string();
  	return s.substr(32 - len, len);
  }

  std::string trim(std::string str)
  {
    const auto str_begin = str.find_first_not_of(" \t");
    if (str_begin == std::string::npos)
      return ""; // no content

    const auto str_end = str.find_last_not_of(" \t");

    return str.substr(str_begin, str_end - str_begin + 1);
  }

};

#endif // ASM_PARSER_H_
