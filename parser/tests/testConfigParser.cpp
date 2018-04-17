#include "ConfigParser.h"
#include <iostream>

using namespace std;

void printConfigs(struct Configs _configs);

int main(int argc, char** argv)
{
  if(argc != 2) {
    cout << "Usage: " << argv[0] << " [configFile]" << endl;
    return 0;
  }

  ConfigParser parser;

  struct Configs configs = parser(argv[1]);

  printConfigs(configs);

  return 0;
}

void printConfigs(struct Configs _configs)
{
  cout
  << "ProgramInput: " << _configs.program_input << endl
  << "RegisterFileInput: " << _configs.register_file_input << endl
  << "MemoryContentIput: " << _configs.memory_contents_input << endl
  << "OutputMode: " << _configs.output_mode << endl
  << "DebugMode: " << _configs.debug_mode << endl
  << "PrintMemContents: " << _configs.print_memory_contents << endl
  << "WriteToFile: " << _configs.write_to_file << endl
  << "OutputFile: " << _configs.output_file << endl;
}
