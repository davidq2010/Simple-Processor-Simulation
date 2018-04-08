#ifndef ALU_CPP_
#define ALU_CPP_

#include "ALU.h"

const std::bitset<ALU::NUM_INPUTS> ALU::FULL_BIT_MASK_32 (0xFFFFFFFFul);

const std::bitset<ALU::NUM_INPUTS> ALU::CONTROL_BIT_MASK (0xFul);

ALU::
ALU(std::string _name) : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS), m_name(_name) {}


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
  logger.log("--------------------------------------------------");
  logger.log(m_name);
  logger.log("  Input:");

  unsigned long a =
    ((m_inputs >> inputStartID(0)) & FULL_BIT_MASK_32).to_ulong();
  unsigned long b =
    ((m_inputs >> inputStartID(1)) & FULL_BIT_MASK_32).to_ulong();

  unsigned long control =
    ((m_inputs >> controlStartID()) & CONTROL_BIT_MASK).to_ulong();

  logger.log("  A", a);
  logger.log("  B", b);
  logger.log("  control", std::bitset<4>(control).to_string());

  unsigned long result;
  switch (control)
  {
    case 0b0010:
      result = a + b;
      logger.log("  action", "ADD");
      break;
    case 0b0110:
      result = a - b;
      logger.log("  action", "SUB");
      break;
    case 0b0111:
      result = ((a >> 31) == (b >> 31))? (a < b) : (a >> 31);
      logger.log("  action", "SLT");
      break;
    default: result = -1;
  }

  bool zero = (result == 0);

  // put the values into m_outputs
  m_outputs = result;
  m_outputs[zeroID()] = zero;

  // log output
  logger.log("  Output:");
  logger.log("  result", result);
  logger.log("  zero", zero);

  // update
  m_updated_inputs.reset();
  fireAllOutputs();
}


#endif // ALU_CPP_
