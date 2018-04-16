#ifndef HARDWIRED_CONSTANT_CPP_
#define HARDWIRED_CONSTANT_CPP_

#include "HardwiredConstant.h"

HardwiredConstant::
HardwiredConstant(bool* _constant, int _n_bits) 
  : ProcessorComponent(NUM_INPUTS, _n_bits) 
{
  m_outputs = new bool[_n_bits];
  for (int i = 0; i < _n_bits; i++) 
    m_outputs[i] = _constant[i];
}

HardwiredConstant::
~HardwiredConstant()
{
  delete[] m_outputs;
}


void
HardwiredConstant::
setInput(int _line_id, bool _clock)
{
  if (_clock)
    updateOutput();
}


bool
HardwiredConstant::
getOutput(int _line_id)
{
  return m_outputs[_line_id];
}


void
HardwiredConstant::
updateOutput()
{
  fireAllOutputs();
}

#endif // HARDWIRE_CONSTANT
