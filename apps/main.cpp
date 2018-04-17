#include "ASMParser.h"
#include "ConfigParser.h"
#include "MemoryFileParser.h"

#include "Processor.h"

#include <bitset>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " [config_file]";
    return 0;
  }

  //----------------------------------------------------------------------------
  // Parsing input files

  // Read config input file
  ConfigParser config_parser;
  struct Configs configs = config_parser(argv[1]);

  // Assemble the program
  ASMParser assembler;
  vector<Instruction> instructions = assembler(configs.program_input);
  vector<unsigned long> binary_code;
  binary_code.reserve(instructions.size());
  for (auto& i : instructions)
    binary_code.push_back( bitset<32>(i.getEncoding()).to_ulong() );

  // read memory input file
  MemoryFileParser mem_parser;
  struct MemoryContent mem_content = mem_parser(configs.memory_contents_input);

  // read register input file
  struct MemoryContent reg_content = mem_parser(configs.register_file_input);

  //----------------------------------------------------------------------------
  // Init processor
  Processor processor(binary_code, reg_content.data,
                      mem_content.data, mem_content.start_address);

  Logger logger;
  processor.setLogger(&logger);

  //----------------------------------------------------------------------------
  // Run

  while (true) {
    processor.step();
  }

  return 0;
}
