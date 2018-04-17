#include "ASMParser.h"
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

/* This file reads in a MIPS assembly file specified at the command line.
 * If the file is correct syntactically, each instruction in the file
 * will be translated into its 32 bit MIPS binary encoding and printed
 * to stdout, one per line.
 *
 */

int main(int argc, char *argv[])
{
  ASMParser parser;

  if(argc < 2){
    cerr << "Need to specify an assembly file to translate."<<endl;
    exit(1);
  }

  vector<Instruction> instructions = parser(argv[1]);

  cout << hex << showbase;
  for (auto& i : instructions)
  {  
  // cout << i.getString() << endl;
    cout << bitset<32>(i.getEncoding()).to_ulong() << endl;
  }
}
