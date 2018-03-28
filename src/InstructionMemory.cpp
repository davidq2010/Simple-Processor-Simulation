#ifndef INSTRUCTION_MEMORY_CPP_
#define INSTRUCTION_MEMORY_CPP_

#include "InstructionMemory.h"
#include "LoggerFactory.h"

InstructionMemory::
InstructionMemory(word* _data, int _n_data)
	: ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) 
{
	m_data = new word[_n_data];
	for (int i = 0; i < _n_data; i++)
	{
		m_data[i] = _data[i];
	}
}


InstructionMemory::
~InstructionMemory()
{
	delete[] m_data;
}


void
InstructionMemory::
setInput(int _line_id, bool _bit)
{
	m_inputs.set(_line_id, _bit);
	m_updated_inputs.set(_line_id);
	if (m_updated_inputs.all())
		updateOutputs();
}

bool
InstructionMemory::
getOutput(int _line_id)
{
	return m_outputs.test(_line_id);
}

void
InstructionMemory::
updateOutputs()
{
	word address = m_inputs.to_ulong() - START_ADDRESS;

	// output update
	m_outputs = m_data[address];

	// log inputs and outputs
	Logger logger = LoggerFactory::getLogger();
	logger.log("--------------------------------------------------");
	logger.log("Instruction Memory");
	logger.log("  Input:");
	logger.log("  address", m_inputs.to_ulong());
	logger.log("  Output:");
	logger.log("  instruction", m_outputs.to_ulong());

	// fire
	m_updated_inputs.reset();
	fireAllOutputs();
}

#endif // INSTRUCTION_MEMORY_CPP_
