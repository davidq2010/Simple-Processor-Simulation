#ifndef MUX_CPP_
#define MUX_CPP_

#include "MUX.h"

MUX::
MUX(int _n_bits, std::string _name) 
    : ProcessorComponent(2 * _n_bits + 1, _n_bits), 
      m_name(_name)
{
  m_inputs = new bool[m_num_inputs];
  m_outputs = new bool[m_num_outputs];
  m_updated_inputs = new bool[m_num_inputs];
}


MUX::
~MUX()
{
  delete[] m_inputs;
  delete[] m_outputs;
  delete[] m_updated_inputs;
}


void
MUX::
setInput(int _line_id, bool _bit)
{
  m_inputs[_line_id] = _bit;
  m_updated_inputs[_line_id] = true;
  if (areAllInputsUpdated())
    updateOutputs();
}


bool
MUX::
getOutput(int _line_id)
{
  return m_outputs[_line_id];
}


void
MUX::
updateOutputs()
{
  // choose operand 0 or 1
  int start_id = operandStartID(m_inputs[controlID()]);
  for (int i = 0; i < m_num_outputs; i++)
    m_outputs[i] = m_inputs[i + start_id];

  // log inputs and outputs
  m_logger->log("--------------------------------------------------");
  m_logger->log(m_name);
  m_logger->log("  Input:");

  unsigned long in0 = 0;
  unsigned long in1 = 0;
  for (int i = m_num_outputs - 1; i >= 0; i--)
  {
    in0 <<= 1;
    in0 |= m_inputs[i + operandStartID(0)];
    in1 <<= 1;
    in1 |= m_inputs[i + operandStartID(1)];
  }

  m_logger->log("  operand0", in0);
  m_logger->log("  operand1", in1);
  m_logger->log("  control" , m_inputs[0]);

  m_logger->log("  Output:");
  unsigned long out = 0;
  for (int i = m_num_outputs - 1; i >= 0; i--)
  {
    out <<= 1;
    out |= m_outputs[i];
  }
  m_logger->log("  output", out);

  // clear updated inputs array
  for(int i = 0; i < m_num_inputs; m_updated_inputs[i++] = 0);
  
  // fire
  fireAllOutputs();
}

bool
MUX::
areAllInputsUpdated()
{
  for (int i = 0; i < m_num_inputs; i++)
    if (!m_updated_inputs[i])
      return false;
  return true;
}


#endif // MUX_CPP_
