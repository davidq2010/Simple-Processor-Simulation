#ifndef INSTRUCTION_MEMORY_H_
#define INSTRUCTION_MEMORY_H_

#include <bitset>
#include <vector>
#include "ProcessorComponent.h"
#include "ProcessorSpec.h"

using namespace processorspec;

////////////////////////////////////////////////////////////////////////////////
/// Instruction memory unit. Allow reading instruction using 32-bit address
/// Input lines:
///   address   [31 - 0]  Address of instruction to read
/// Output lines
///   inst      [31 - 0]  Instruction
////////////////////////////////////////////////////////////////////////////////

class InstructionMemory : public ProcessorComponent
{
  public:
    //------------------------------------------------------------------------
    // Constants

    static const int NUM_INPUTS = 32;
    static const int NUM_OUTPUTS = 32;

    static const unsigned long START_ADDRESS = 0x400000;

    InstructionMemory();

    InstructionMemory(std::vector<unsigned long> _data);

    InstructionMemory(unsigned long* _data, int _n_data);

    ~InstructionMemory();

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id);


    //------------------------------------------------------------------------
    // Data access

    unsigned long getData(unsigned long _address);

    void setData(unsigned long _address, unsigned long _data);

    void resetData(std::vector<unsigned long> _data);

  private:
    //------------------------------------------------------------------------
    // IO related
    std::bitset<NUM_INPUTS> m_inputs; /// Input bits

    std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

    std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated

    void updateOutputs();

    //------------------------------------------------------------------------
    // Data
    std::vector<unsigned long> m_data;
};

#endif // INSTRUCTION_MEMORY_H_