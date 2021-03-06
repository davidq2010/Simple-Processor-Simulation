#include "MemoryFileParser.h"
#include <fstream>
#include <stdexcept>

using namespace std;

struct MemoryContent
MemoryFileParser::
operator() (string _memory_file)
{
  // Try to open file
  ifstream ifs(_memory_file);
  if(!ifs)
    throw invalid_argument( string("File does not exist: ") + _memory_file );

  // Parse file into MemoryContent struct
  struct MemoryContent memory;
  string line;
  bool is_first_line = true;

  while(getline(ifs, line))
  {
    // Ignore comments in memory file
    size_t index_of_comment = line.find_first_of('#');
    if(index_of_comment != string::npos)
      line = line.substr(0, index_of_comment);

    // split string at ":"
    size_t index_of_colon = line.find_first_of(':');
    if(index_of_colon == string::npos)
      continue;

    string address = line.substr(0, index_of_colon);
    string data = line.substr(index_of_colon + 1,
                               line.size() - index_of_colon - 1);
    address = trim(address);
    data = trim(data);
    if (address.size() == 0 || data.size() == 0)
      continue;

    if (is_first_line)
    {
      memory.start_address = std::stoul(address, 0, 16);
      is_first_line = false;
    }

    memory.data.push_back(std::stoul(data, 0, 16));
  }

  return memory;
}


string
MemoryFileParser::
trim(string str)
{
  const auto str_begin = str.find_first_not_of(" \t");
  if (str_begin == std::string::npos)
    return ""; // no content

  const auto str_end = str.find_last_not_of(" \t");

  return str.substr(str_begin, str_end - str_begin + 1);
}
