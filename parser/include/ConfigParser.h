#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <string>
#include <unordered_map>
#include <fstream>

struct Configs
{
  enum OutputMode{SINGLE_STEP, BATCH};

  std::string program_input;
  std::string register_file_input;
  OutputMode output_mode;
  bool        debug_mode;
  bool        print_memory_contents;
  bool        write_to_file;
  std::string output_file;
};

class ConfigParser
{

  public:

    struct Configs operator() (std::string _configFile);

  private:

    void readFileAndFillParams(
      std::unordered_map<std::string, std::string>& _paramMap,
      std::ifstream& _ifs);

    void setConfigs(struct Configs& _configStruct,
                    const std::unordered_map<std::string, std::string>&
                    _paramMap);

};
#endif
