#ifndef AND_CPP_
#define AND_CPP_

#include "ANDGate.h"

ANDGate::
ANDGate() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}


void
ANDGate::
setInput(int _line_id, bool _bit)
{
  m_inputs[_line_id] = _bit;
  m_updated_inputs[_line_id] = true;
  if (allInputsUpdated())
    updateOutput();
}


bool
ANDGate::
getOutput(int _line_id)
{
  return m_outputs[_line_id];
}


void
ANDGate::
updateOutput()
{
  m_outputs[0] = m_inputs[0] & m_inputs[1];

  fireAllOutputs();
}

bool
ANDGate::
allInputsUpdated()
{
  for (int i = 0; i < m_num_inputs; i++)
    if (!m_updated_inputs[i])
      return false;
  return true;
}


#endif // ANDGate_CPP_
