#include "Opcode.h"

OpcodeTable::OpcodeTable()
// Initializes all the fields for every instruction in Opcode enum
{
  myArray[ADD].name = "add";    myArray[ADD].numOps = 3;    myArray[ADD].rdPos = 0;    myArray[ADD].rsPos = 1;    myArray[ADD].rtPos = 2;     myArray[ADD].immPos = -1;    myArray[ADD].instType = RTYPE;    myArray[ADD].op_field = "000000";    myArray[ADD].funct_field = "100000";
  myArray[ADDI].name = "addi";  myArray[ADDI].numOps = 3;   myArray[ADDI].rdPos = -1;   myArray[ADDI].rsPos = 1;   myArray[ADDI].rtPos = 0;   myArray[ADDI].immPos = 2;    myArray[ADDI].instType = ITYPE;   myArray[ADDI].op_field = "001000";
  myArray[MULT].name = "mult";  myArray[MULT].numOps = 2;   myArray[MULT].rdPos = -1;  myArray[MULT].rsPos = 0;   myArray[MULT].rtPos = 1;    myArray[MULT].immPos = -1;   myArray[MULT].instType = RTYPE;   myArray[MULT].op_field = "000000";   myArray[MULT].funct_field = "011000";
  myArray[MFLO].name = "mflo";  myArray[MFLO].numOps = 1;   myArray[MFLO].rdPos = 0;   myArray[MFLO].rsPos = -1;  myArray[MFLO].rtPos = -1;  myArray[MFLO].immPos = -1;   myArray[MFLO].instType = RTYPE;   myArray[MFLO].op_field = "000000";   myArray[MFLO].funct_field = "010010";
  myArray[SRA].name = "sra";    myArray[SRA].numOps = 3;    myArray[SRA].rdPos = 0;    myArray[SRA].rsPos = -1;   myArray[SRA].rtPos = 1;     myArray[SRA].immPos = 2;     myArray[SRA].instType = RTYPE;    myArray[SRA].op_field = "000000";    myArray[SRA].funct_field = "000011";
  myArray[SLT].name = "slt";    myArray[SLT].numOps = 3;    myArray[SLT].rdPos = 0;    myArray[SLT].rsPos = 1;    myArray[SLT].rtPos = 2;     myArray[SLT].immPos = -1;    myArray[SLT].instType = RTYPE;    myArray[SLT].op_field = "000000";    myArray[SLT].funct_field = "101010";
  myArray[LB].name = "lb";      myArray[LB].numOps = 3;     myArray[LB].rdPos = -1;    myArray[LB].rsPos = 2;     myArray[LB].rtPos = 0;      myArray[LB].immPos = 1;      myArray[LB].instType = ITYPE;     myArray[LB].op_field = "100000";
  myArray[J].name = "j";        myArray[J].numOps = 1;      myArray[J].rdPos = -1;      myArray[J].rsPos = -1;     myArray[J].rtPos = -1;       myArray[J].immPos = 0;    myArray[J].instType = JTYPE;      myArray[J].op_field = "000010"; myArray[J].immLabel = true;

}

Opcode OpcodeTable::getOpcode(string str)
// Given a valid MIPS assembly mnemonic, returns an Opcode which represents a
// template for that instruction.
{
  for(int i = 0; i < (int)UNDEFINED; i++){
    if(myArray[i].name == str){
      return (Opcode)i;
    }
  }
  return UNDEFINED;
}

int OpcodeTable::numOperands(Opcode o)
// Given an Opcode, returns number of expected operands.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].numOps;
}


int OpcodeTable::RSposition(Opcode o)
// Given an Opcode, returns the position of RS field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rsPos;
}

int OpcodeTable::RTposition(Opcode o)
// Given an Opcode, returns the position of RT field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rtPos;
}

int OpcodeTable::RDposition(Opcode o)
// Given an Opcode, returns the position of RD field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rdPos;
}

int OpcodeTable::IMMposition(Opcode o)
// Given an Opcode, returns the position of IMM field.  If field is not
// appropriate for this Opcode, returns -1.
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].immPos;
}

InstType OpcodeTable::getInstType(Opcode o)
// Given an Opcode, returns instruction type.
{
  if(o < 0 || o > UNDEFINED)
    return (InstType)-1;
  return myArray[o].instType;
}

string OpcodeTable::getOpcodeField(Opcode o)
// Given an Opcode, returns a string representing the binary encoding of the opcode
// field.
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].op_field;
}

string OpcodeTable::getFunctField(Opcode o)
// Given an Opcode, returns a string representing the binary encoding of the function
// field.
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].funct_field;
}

bool OpcodeTable::isIMMLabel(Opcode o)
// Given an Opcode, returns true if instruction expects a label in the instruction.
// See "J".
{
  if(o < 0 || o > UNDEFINED)
    return false;
  return myArray[o].immLabel;
}
