#ifndef INSTRUCTION_MEMORY_H_
#define INSTRUCTION_MEMORY_H_

#include <bitset>
#include <vector>
#include "ProcessorComponent.h"
//#include "ProcessorSpec.h"

//using namespace processorspec;

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Instruction memory unit. Allow reading instructions of 32-bits
/// address
///
/// Input lines:
///   address   [31 - 0]  Address of instruction to read
/// Output lines
///   inst      [31 - 0]  Instruction
////////////////////////////////////////////////////////////////////////////////
class InstructionMemory : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{

    static const int NUM_INPUTS = 32;   ///< Address is 32 bits
    static const int NUM_OUTPUTS = 32;  ///< Instruction will be 32 bits

    static const unsigned long START_ADDRESS = 0x400000;  ///< Assign correct
                                                          ///< start address

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{

    InstructionMemory();

    /// @param _data Vector of binary-encoded ASM instructions
    InstructionMemory(std::vector<unsigned long> _data);

    /// @deprecated
    InstructionMemory(unsigned long* _data, int _n_data);

    ~InstructionMemory();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    void setInput(int _line_id, bool _bit);

    void setData(unsigned long _address, unsigned long _data);

    void resetData(std::vector<unsigned long> _data);

    bool getOutput(int _line_id);

    /// @brief Gets data from _address and returns as ul. Guarantees data won't
    /// be altered.
    /// @param _address Address from which to retrieve data
    /// @return Data in instruction memory at _address
    unsigned long getData(unsigned long _address) const;

    /// @return the last instruction address + 4
    unsigned long getLastAddress() const;

    /// @brief The output is a 32-bit instruction
    void updateOutputs();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


  private:
    std::bitset<NUM_INPUTS> m_inputs;   ///< Input bits

    std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

    std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated

    std::vector<unsigned long> m_data;  ///< Vector of instructions
};

#endif // INSTRUCTION_MEMORY_H_
