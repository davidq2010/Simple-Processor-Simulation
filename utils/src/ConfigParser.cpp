#include "ConfigParser.h"
#include <sstream>
#include <stdexcept>

using namespace std;

struct Configs
ConfigParser::
operator() (string _configFile)
{
  // Try to open file
  ifstream ifs(_configFile);

  if(!ifs.is_open())
    throw invalid_argument("File does not exist");

  unordered_map<string, string> paramMap;
  readFileAndFillParams(paramMap, ifs);  // Fills paramMap

  ifs.close();

  struct Configs configs;
  try {
    setConfigs(configs, paramMap); // Sets variables in configStruct
  } catch(out_of_range& e) {
    throw invalid_argument("Missing parameters");
  }

  return configs;
}


void
ConfigParser::
readFileAndFillParams(unordered_map<string, string>& _paramMap, ifstream& _ifs)
{
  string line;
  while(getline(_ifs, line)) // The line from filestream goes into string line
  {
    // Ignore comments in config file
    size_t index_of_comment = line.find_first_of('#');
    if(index_of_comment != string::npos)
      line = line.substr(0, index_of_comment);

    size_t index_of_equal = line.find_first_of('=');
    if(index_of_equal == string::npos)
      continue;

    string key = line.substr(0, index_of_equal);
    string value = line.substr(index_of_equal + 1,
                               line.size() - index_of_equal - 1);

    _paramMap.emplace(key, value);
  }
}


void
ConfigParser::
setConfigs(struct Configs& _configs,
           const unordered_map<string, string>& _paramMap)
{
  _configs.program_input          = _paramMap.at("program_input");
  _configs.memory_contents_input  = _paramMap.at("memory_contents_input");
  _configs.register_file_input    = _paramMap.at("register_file_input");
  _configs.output_mode            = _paramMap.at("output_mode") == "batch" ?
                                        Configs::BATCH : Configs::SINGLE_STEP;
  _configs.debug_mode             = _paramMap.at("debug_mode") == "true";
  _configs.print_memory_contents  = _paramMap.at("print_memory_contents")
                                        == "true";
  _configs.write_to_file          = _paramMap.at("write_to_file") == "true";
  _configs.output_file            = _paramMap.at("output_file");
}
