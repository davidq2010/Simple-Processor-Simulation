#ifndef HARDWIRED_CONSTANT_CPP_
#define HARDWIRED_CONSTANT_CPP_

#include "HardwiredConstant.h"

HardwiredConstant::
HardwiredConstant(bool* _constant, int _n_bits) : ProcessorComponent(NUM_INPUTS,
                                                                    _n_bits) {
  m_hardwiredConstant = _constant;
  m_outputs = new bool[_n_bits];
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
	m_inputs[_line_id] = _clock;
	if (_clock == 1)
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
  m_outputs = m_hardwiredConstant;

	fireAllOutputs();
}

#endif // HARDWIRE_CONSTANT
