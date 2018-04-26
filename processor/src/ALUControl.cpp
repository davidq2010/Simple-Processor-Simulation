#include "ALUControl.h"


const std::bitset<ALUControl::NUM_INPUTS> ALUControl::ALU_OP_MASK (0b11);


ALUControl::
ALUControl() : AbstractProcessorComponent<NUM_INPUTS, NUM_OUTPUTS>() {}

void
ALUControl::
updateOutputs()
{
  unsigned long aluOp = (m_inputs >> aluOpStartID() & ALU_OP_MASK).to_ulong();
  unsigned long func  = (m_inputs >> funcStartID()).to_ulong();
  switch (aluOp)
  {
    case OP_ADD: m_outputs = OUT_ADD; break;
    case OP_SUB: m_outputs = OUT_SUB; break;
    default: switch (func)
    {
      case FUNC_ADD: m_outputs = OUT_ADD; break;
      case FUNC_SUB: m_outputs = OUT_SUB; break;
      case FUNC_SLT: m_outputs = OUT_SLT; break;
    }
  }


  // log input/output
  m_logger->log("--------------------------------------------------");
  m_logger->log("ALU CONTROL");
  m_logger->log("  Input:");
  m_logger->log("  aluOp", aluOp);
  m_logger->log("  func" , func);
  m_logger->log("  Output:");
  m_logger->log("  output", m_outputs.to_ulong());
}
