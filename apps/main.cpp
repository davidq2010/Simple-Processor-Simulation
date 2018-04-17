#include "ASMParser.h"
#include "ConfigParser.h"
#include "MemoryFileParser.h"

#include "Processor.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " [config_file]"
    return 0;
  }

  //----------------------------------------------------------------------------
  // Parsing input files
  ConfigParser config_parser;
  struct Configs configs = config_parser(argv[1]);

  ASMParser asembler;


  return 0;
}