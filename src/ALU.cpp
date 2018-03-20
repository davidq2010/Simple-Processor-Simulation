#ifndef ALU_CPP_
#define ALU_CPP_

#include "ALU.h"

const std::bitset<ALU::NUM_INPUTS> ALU::FULL_BIT_MASK_32 (0xFFFFFFFFul);

ALU::
ALU() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}


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
		((m_inputs >> inputStartID(0)) & FULL_BIT_MASK_32).to_ulong();
	unsigned long b =
		((m_inputs >> inputStartID(1)) & FULL_BIT_MASK_32).to_ulong();

	if (m_inputs[bNegateID()]) b = -b;
	unsigned long result = a + b;

	if (m_inputs[lessID()]) result = result >> 31 & 1ul; // if SLT, output the signed bit only
	bool zero = m_inputs[equalID()] && (result == 0);

	// put the values into m_outputs
	for (int i = 0; i < 32; i++)
		m_outputs[i] = (result >> i) & 1ul;
	m_outputs[zeroID()] = zero;

	// update
	m_updated_inputs.reset();
	fireAllOutputs();
}


#endif // ALU_CPP_
