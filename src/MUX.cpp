#ifndef MUX_CPP_
#define MUX_CPP_

#include "MUX.h"

MUX::
MUX(int _n_bits) : ProcessorComponent(2 * _n_bits + 1, _n_bits)
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
	if (allInputsUpdated())
		updateOutput();
}

bool
MUX::
getOutput(int _line_id)
{
	return m_outputs[_line_id];
}

void
MUX::
updateOutput()
{
	int start_id = startID(m_inputs[0]);

	for (int i = 0; i < m_num_outputs; i++) {
		m_outputs[i] = m_inputs[i + start_id];
	}

	fireAllOutputs();
}

bool
MUX::
allInputsUpdated()
{
	for (int i = 0; i < m_num_inputs; i++)
		if (!m_updated_inputs[i])
			return false;
	return true;
}


#endif // MUX_CPP_
