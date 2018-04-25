#include "ALU.h"

// Initialize static members
const std::bitset<ALU::NUM_INPUTS> ALU::FULL_BIT_MASK_32 (0xFFFFFFFFul);

const std::bitset<ALU::NUM_INPUTS> ALU::CONTROL_BIT_MASK (0xFul);


ALU::
ALU(std::string _name) : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS),
  m_name(_name) {}


void
ALU::
setInput(int _line_id, bool _bit)
{
  m_inputs.set(_line_id, _bit);
  m_updated_inputs.set(_line_id);
  if (m_updated_inputs.all())
    updateOutput();
}


bool
ALU::
getOutput(int _line_id)
{
  return m_outputs.test(_line_id);
}


void
ALU::
updateOutput()
{
  unsigned long a =
    ((m_inputs >> operandStartID(0)) & FULL_BIT_MASK_32).to_ulong();
  unsigned long b =
    ((m_inputs >> operandStartID(1)) & FULL_BIT_MASK_32).to_ulong();

  unsigned long control =
    ((m_inputs >> controlStartID()) & CONTROL_BIT_MASK).to_ulong();

  m_logger->log("--------------------------------------------------");
  m_logger->log(m_name);
  m_logger->log("  Input:");
  m_logger->log("  operand0", a);
  m_logger->log("  operand1", b);
  m_logger->log("  control" , control);

  unsigned long result;
  std::string   action;
  switch (control)
  {
    case 0b0010:
      result = a + b;
      action = "ADD";
      break;
    case 0b0110:
      result = a - b;
      action = "SUB";
      break;
    case 0b0111:
      result = ((a >> 31) == (b >> 31))? (a < b) : (a >> 31);
      action = "SLT";
      break;
    default: result = -1;
  }
  result &= 0xFFFFFFFFul;

  bool zero = (result == 0);

  // put the values into m_outputs
  m_outputs = result;
  m_outputs[zeroID()] = zero;

  // log output
  m_logger->log("  Output:");
  m_logger->log("  action", action, Logger::DEBUG);
  m_logger->log("  result", result);
  m_logger->log("  zero", zero);

  // update
  m_updated_inputs.reset();
  fireAllOutputs();
}
