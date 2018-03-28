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

	for (int i = 0; i < m_num_outputs; i++)
		m_outputs[i] = m_inputs[i + start_id];

	// log inputs and outputs
	Logger logger = LoggerFactory::getLogger();
	logger.log("--------------------------------------------------");
	logger.log("MUX");
	logger.log("  Input:");

	unsigned long in0 = 0;
	unsigned long in1 = 0;
	for (int i = 0; i < m_num_outputs; i++)
	{
		in0 <<= 1;
		in0 |= m_inputs[i + startID(0)];
		in1 <<= 1;
		in1 |= m_inputs[i + startID(1)];
	}

	logger.log("  input0", in0);
	logger.log("  input1", in1);
	logger.log("  control", m_inputs[0]? "1" : "0");

	logger.log("  Output:");
  unsigned long out = 0;
  for(int i = 0; i < m_num_outputs; i++)
  {
    out <<= 1;
    out |= m_outputs[i];
  }
	logger.log("  output", out);

	// fire
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
