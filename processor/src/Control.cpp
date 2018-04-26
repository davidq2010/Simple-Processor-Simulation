#include "Control.h"

const Control::opcodeMap Control::OPCODE_TABLE
({
  // R-Type instructions
  {std::bitset<NUM_INPUTS>("000000"), std::bitset<NUM_OUTPUTS>("1001000001")},

  // ADDI
  {std::bitset<NUM_INPUTS>("001000"), std::bitset<NUM_OUTPUTS>("1100000000")},

  // LW
  {std::bitset<NUM_INPUTS>("100011"), std::bitset<NUM_OUTPUTS>("1100011000")},

  // SW (RegDst/MemToReg don't matter)
  {std::bitset<NUM_INPUTS>("101011"), std::bitset<NUM_OUTPUTS>("0110000000")},

  // BEQ (RegDst/MemToReg don't matter)
  {std::bitset<NUM_INPUTS>("000100"), std::bitset<NUM_OUTPUTS>("0000100100")},

  // J (No other fields matter but jump)
  {std::bitset<NUM_INPUTS>("000010"), std::bitset<NUM_OUTPUTS>("0000000010")}
 });


Control::
Control() : AbstractProcessorComponent<NUM_INPUTS, NUM_OUTPUTS>() {}


void
Control::
updateOutputs()
{
  // Check if the input bits match an opcode. If it does, output the correct bit
  // to the correct wire.

  // Look up the output bits for that inputs std::bitset and put into m_outputs
  m_outputs = OPCODE_TABLE.at(m_inputs);

  // Log
  m_logger->log("--------------------------------------------------");
  m_logger->log("Control");
  m_logger->log("  Input:");
  m_logger->log("  Opcode", m_inputs.to_ulong());
  m_logger->log("  Output:");
  m_logger->log("  RegDst"  , m_outputs[0]);
  m_logger->log("  Jump"    , m_outputs[1]);
  m_logger->log("  Branch"  , m_outputs[2]);
  m_logger->log("  MemRead" , m_outputs[3]);
  m_logger->log("  MemToReg", m_outputs[4]);
  m_logger->log("  ALUOp0"  , m_outputs[5]);
  m_logger->log("  ALUOp1"  , m_outputs[6]);
  m_logger->log("  MemWrite", m_outputs[7]);
  m_logger->log("  ALUSrc"  , m_outputs[8]);
  m_logger->log("  RegWrite", m_outputs[9]);
}
