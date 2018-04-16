#ifndef MEMORY_FILE_PARSER_H_
#define MEMORY_FILE_PARSER_H_

#include <string>
#include <vector>

struct MemoryData
{
  unsigned long start_address;
  std::vector<unsigned long> data;
};


class MemoryFileParser
{
  public:
    struct MemoryData operator() (std::string _memory_file);

  private:
    std::string trim(std::string str);
};

#endif // MEMORY_FILE_PARSER_H_
