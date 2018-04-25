#ifndef PROGRAM_COUNTER_H_
#define PROGRAM_COUNTER_H_

#include "ProcessorComponent.h"

// STL
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Program counter - stores a 32-bit address pointing to the instruction
/// in instruction memory to be executed.
///
/// Input:
///   address   [31 - 0]
///   clock     [32]
/// Output:
///   address   [31 - 0]
///
/// Update timing: immediately after the clock line is set to high
/// the address is fired
////////////////////////////////////////////////////////////////////////////////
class ProgramCounter : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{

    static const int NUM_INPUTS = 33;
    static const int NUM_OUTPUTS = 32;
    static const int CLOCK_ID = 32;

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{
    ProgramCounter();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    /// @brief Used to set each bit of instruction address into bitset member
    /// @details Calls fireAllOutputs() if clock bit is high
    void setInput(int _line_id, bool _bit);

    /// @brief Get a particular bit
    bool getOutput(int _line_id);

    /// @return The instruction address bitset
    unsigned long getInstructionAddress();

    int clockID() { return CLOCK_ID; }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    std::bitset<NUM_OUTPUTS> m_address; ///< Instruction address binary
};

#endif // PROGRAM_COUNTER_H_
