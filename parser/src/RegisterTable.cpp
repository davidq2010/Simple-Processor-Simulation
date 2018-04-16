#include "RegisterTable.h"

using namespace std;

RegisterTable::RegisterTable()
{
  int i = 0;

  myRegisters[i].name = "$0";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$1";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$2";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$3";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$4";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$5";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$6";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$7";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$8";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$9";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$10";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$11";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$12";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$13";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$14";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$15";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$16";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$17";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$18";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$19";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$20";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$21";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$22";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$23";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$24";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$25";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$26";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$27";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$28";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$29";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$30";  myRegisters[i].number = i; i++;
  myRegisters[i].name = "$31";  myRegisters[i].number = i; i++;

  myRegisters[i].name = "$zero";  myRegisters[i].number = 0; i++;
  myRegisters[i].name = "$v0";  myRegisters[i].number = 2; i++;
  myRegisters[i].name = "$v1";  myRegisters[i].number = 3; i++;
  myRegisters[i].name = "$a0";  myRegisters[i].number = 4; i++;

  myRegisters[i].name = "$a1";  myRegisters[i].number = 5; i++;
  myRegisters[i].name = "$a2";  myRegisters[i].number = 6; i++;
  myRegisters[i].name = "$a3";  myRegisters[i].number = 7; i++;
  myRegisters[i].name = "$t0";  myRegisters[i].number = 8; i++;

  myRegisters[i].name = "$t1";  myRegisters[i].number = 9; i++;
  myRegisters[i].name = "$t2";  myRegisters[i].number = 10; i++;
  myRegisters[i].name = "$t3";  myRegisters[i].number = 11; i++;
  myRegisters[i].name = "$t4";  myRegisters[i].number = 12; i++;

  myRegisters[i].name = "$t5";  myRegisters[i].number = 13; i++;
  myRegisters[i].name = "$t6";  myRegisters[i].number = 14; i++;
  myRegisters[i].name = "$t7";  myRegisters[i].number = 15; i++;
  myRegisters[i].name = "$s0";  myRegisters[i].number = 16; i++;

  myRegisters[i].name = "$s1";  myRegisters[i].number = 17; i++;
  myRegisters[i].name = "$s2";  myRegisters[i].number = 18; i++;
  myRegisters[i].name = "$s3";  myRegisters[i].number = 19; i++;
  myRegisters[i].name = "$s4";  myRegisters[i].number = 20; i++;

  myRegisters[i].name = "$s5";  myRegisters[i].number = 21; i++;
  myRegisters[i].name = "$s6";  myRegisters[i].number = 22; i++;
  myRegisters[i].name = "$s7";  myRegisters[i].number = 23; i++;
  myRegisters[i].name = "$t8";  myRegisters[i].number = 24; i++;

  myRegisters[i].name = "$t9";  myRegisters[i].number = 25; i++;
  myRegisters[i].name = "$gp";  myRegisters[i].number = 28; i++;
  myRegisters[i].name = "$sp";  myRegisters[i].number = 29; i++;
  myRegisters[i].name = "$fp";  myRegisters[i].number = 30; i++;

  myRegisters[i].name = "$ra";  myRegisters[i].number = 31; i++;

}

Register RegisterTable::getNum(string reg)
  // Given a string representing a MIPS register operand, returns the number associated
  // with that register.  If string is not a valid register, returns NumRegisters.
{
  for(int i = 0; i < 2*NumRegisters; i++){
    if(myRegisters[i].name == reg){
      return myRegisters[i].number;
    }

  }
  return NumRegisters;

}
