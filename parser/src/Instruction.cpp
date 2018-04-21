#include "Instruction.h"

#include <sstream>

using std::string;

Instruction::Instruction()
{
  myOpcode = UNDEFINED;
  myRS = myRT = myRD = NumRegisters;
}

Instruction::Instruction(Opcode op, Register rs, Register rt, Register rd, unsigned long imm)
// You can specify all the fields to initialize the Instruction
{
  setValues(op, rs, rt, rd, imm);
}

void Instruction::setValues(Opcode op, Register rs, Register rt, Register rd, unsigned long imm)
// You can specify all the fields to initialize the Instruction
{

  myOpcode = op;
  if(op < 0 || op >= UNDEFINED)
    myOpcode = UNDEFINED;

  myRS = rs;
  if(rs < 0 || rs >= NumRegisters)
    myRS = NumRegisters;

  myRT = rt;
  if(rt < 0 || rt >= NumRegisters)
    myRT = NumRegisters;

  myRD = rd;
  if(rd < 0 || rd >= NumRegisters)
    myRD = NumRegisters;

  myImmediate = imm;

  //  if(!( (imm & 0xFFFF0000) << 1))  // make sure it has nothing in upper 16 bits
  //    myImmediate = imm;  

}

/*
string Instruction::getString()
// Returns a string which represents all of the fields 
{
  stringstream s ;
  s << "OP: \t" << myOpcode << "\t" << "RD: " << myRD << "\t" << 
    "RS: " << myRS << "\t" << "RT: " << "\t" << myRT << "\t" <<
    "Imm: " << myImmediate;
  
  return s.str();
  
}
*/

