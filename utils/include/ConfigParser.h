#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <string>
#include <unordered_map>
#include <fstream>

struct Configs
{
  enum OutputMode{SINGLE_STEP, BATCH};

  std::string program_input;
  std::string memory_contents_input;
  std::string register_file_input;
  OutputMode  output_mode;
  bool        debug_mode;
  bool        print_memory_contents;
  bool        write_to_file;
  std::string output_file;
};

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Parser
/// @brief Arithmetic and logic unit. Can perform the following opperations on
/// two 32-bit signed integers: ADD (ADDI), SUB, SLT, BEQ. The operations can be
/// specified using 4-bit opcode:
///   0010  Add
///   0110  Subtract
///   0111  Set on less than
///
/// @details
/// Input lines:
///   operand0  [31 - 0 ]   First number
///   operand1  [63 - 32]   Second number
///   control   [67 - 64]   Specifies which operation to perform
///
/// Output lines
///   result    [31 - 0 ]   ALU result
///   zero      [32]        set if result == 0
/// When the control lines don't match exactly any of the instruction supported,
/// ALU's behavior is undefined.
////////////////////////////////////////////////////////////////////////////////
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
