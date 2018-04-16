#include "MemoryFileParser.h"
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
  if (argc != 2) 
  {
    cerr << "Usage: " << argv[0] << " [memory_file_name]" << endl;
    return 0;
  }

  MemoryFileParser parser;
  struct MemoryData data = parser(argv[1]);
  cout << "Starting address:" << hex << showbase << data.start_address << endl << endl;
  for (auto i : data.data) 
  {
    cout << i << endl;
  }

  return 0;
}
