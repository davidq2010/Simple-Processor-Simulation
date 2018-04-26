#ifndef ALU_H_
#define ALU_H_

#include <bitset>
#include <string>
#include "AbstractProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
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
class ALU : public AbstractProcessorComponent<68, 33>
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{

    static const int NUM_INPUTS = 68;
    static const int NUM_OUTPUTS = 33;

    ///< Input line IDs
    static const int A_START_ID = 0;
    static const int B_START_ID = 32;
    static const int CONTROL_START_ID = 64;

    ///< Output line ID (for ZERO output line)
    static const int ZERO_ID = 32;

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{
    ///
    /// @param _name Name of component for logging purposes
    ALU(std::string _name);

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    /// @param _inputNum 0 or 1, depending which operand you want
    /// @return The first or second operand
    int operandStartID(bool _inputNum)
    {
      return _inputNum? B_START_ID : A_START_ID;
    }

    int controlStartID() { return CONTROL_START_ID; }

    int zeroID()  { return ZERO_ID; }

    /// @brief Updates output bits depending on ALU control code
    void updateOutputs();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    ///< Bitmask
    static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_32;

    static const std::bitset<NUM_INPUTS> CONTROL_BIT_MASK;

    std::string m_name;   ///< name of the component, for logging
};

#endif // ALU_H_
