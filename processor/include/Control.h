#ifndef CONTROL_H_
#define CONTROL_H_

#include <bitset>
#include <unordered_map>
#include "AbstractProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Main Control Unit will use input from instruction opcode to determine
/// what signals to send to the following output processor components:
///
/// Input lines:
///   Opcode    [5-0]  Instruction opcode
///
/// Output lines
///   RegDst    [0]
///   Jump      [1]
///   Branch    [2]
///   MemRead   [3]
///   MemToReg  [4]
///   ALUOp     [5-6]
///   MemWrite  [7]
///   ALUSrc    [8]
///   RegWrite  [9]
///
/// When the control lines don't match exactly any of the instruction supported,
/// Control Unit has undefined behavior.
////////////////////////////////////////////////////////////////////////////////
class Control : public AbstractProcessorComponent<6, 10>
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{
    static const int NUM_INPUTS  = 6;
    static const int NUM_OUTPUTS = 10;

    static const int OPCODE_ID = 0; ///< Input line ID
    static const int RESULT_ID = 0; ///< Output line ID

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{

    Control();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    int opcodeID()  { return OPCODE_ID; }

    int resultID()  { return RESULT_ID; }

    void updateOutputs();
    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    typedef std::unordered_map<std::bitset<NUM_INPUTS>,std::bitset<NUM_OUTPUTS>>
    opcodeMap;

    static const opcodeMap OPCODE_TABLE;  ///< Hashmap mapping input opcode bits
                                          ///< to which output line to fireW
};

#endif
