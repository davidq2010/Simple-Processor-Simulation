#include "ASMParser.h"
#include "ConfigParser.h"
#include "MemoryFileParser.h"

#include "Processor.h"

#include <bitset>
#include <iostream>
#include <stdexcept>
#include <string>


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

  // Translate input program to binary code
  ASMParser assembler;
  std::vector<Instruction>   instructions = assembler(configs.program_input);
  std::vector<unsigned long> binary_code;
  binary_code.reserve(instructions.size());
  for (auto& i : instructions)
    binary_code.push_back( std::bitset<32>(i.getEncoding()).to_ulong() );

  // read memory input file
  MemoryFileParser mem_parser;
  struct MemoryContent mem_content = mem_parser(configs.memory_contents_input);

  // read register input file
  struct MemoryContent reg_content = mem_parser(configs.register_file_input);

  //----------------------------------------------------------------------------
  // Init logger
  std::ostream* out_stream = &std::cout;
  std::ofstream file_out_stream;
  if (configs.write_to_file)
  {
    file_out_stream.open(configs.output_file);
    out_stream = &file_out_stream;
  }

  if (!out_stream->good()) {
    std::cerr << "Failed to set up logging stream" << std::endl;
    exit(1);
  }

  Logger logger(*out_stream);
  logger.setPrintOption(Logger::DEBUG, configs.debug_mode);
  logger.setPrintOption(Logger::MEMORY, configs.print_memory_contents);

  //----------------------------------------------------------------------------
  // Init processor
  Processor processor(binary_code,
                      reg_content.data,
                      mem_content.data,
                      mem_content.start_address);
  processor.setLogger(&logger);

  //----------------------------------------------------------------------------
  // Run
  int i = 1;
  while (!processor.isFinished()) {
    logger.log("====================================================================");
    logger.log(string("Cycle ") + to_string(i));
    try {
      processor.step();
    } catch(std::out_of_range& ex) {
      logger.log("Error: out_of_range");
      logger.log(ex.what());
      break;
    }
    i++;
  }

  file_out_stream.close();
  return 0;
}
