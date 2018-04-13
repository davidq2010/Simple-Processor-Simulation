#include "ASMParser.h"
#include <iostream>

using namespace std;

/* This file reads in a MIPS assembly file specified at the command line.
 * If the file is correct syntactically, each instruction in the file
 * will be translated into its 32 bit MIPS binary encoding and printed
 * to stdout, one per line.
 *
 */

int main(int argc, char *argv[])
{
  ASMParser *parser;

  if(argc < 2){
    cerr << "Need to specify an assembly file to translate."<<endl;
    exit(1);
  }

  parser = new ASMParser(argv[1]);

  if(parser->isFormatCorrect() == false){
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;

  //Iterate through instructions, printing each encoding.
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED){
    // cout << i.getString() << endl;
    cout << i.getEncoding() << endl;
    i = parser->getNextInstruction();
  }
  
  delete parser;
}
