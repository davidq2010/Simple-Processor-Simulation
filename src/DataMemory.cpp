#ifndef DATA_MEMORY_CPP_
#define DATA_MEMORY_CPP_

#include "DataMemory.h"


const std::bitset<DataMemory::NUM_INPUTS> DataMemory::FULL_BIT_MASK_32 (0xFFFFFFFFul);


DataMemory::
DataMemory(unsigned long* _data, 
			unsigned long _start_address, 
			unsigned long _end_address)
	
	: ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS), 
	  m_start_address(_start_address),
	  m_end_address(_end_address) 
{
	m_data = new unsigned long[m_end_address - m_start_address + 1];
	for (int i = 0; i < (int)(m_end_address - m_start_address); i++)
	{
		m_data[i] = _data[i];
	}
}


DataMemory::
~DataMemory()
{
	delete[] m_data;
}


void
DataMemory::
setInput(int _line_id, bool _bit)
{
	m_inputs.set(_line_id, _bit);
	m_updated_inputs.set(_line_id);
	if (m_updated_inputs.all())
		updateOutputs();
}

bool
DataMemory::
getOutput(int _line_id)
{
	return m_outputs.test(_line_id);
}

void
DataMemory::
updateOutputs()
{
	unsigned long address = 
			((m_inputs >> addressStartID()) & FULL_BIT_MASK_32).to_ulong();
	address -= m_start_address;

	// write
	if (m_inputs[memWriteID()])
	{
		unsigned long write_data = 
				((m_inputs >> writeDataStartID()) & FULL_BIT_MASK_32).to_ulong();
		m_data[address] = write_data;
	}

	// output update and fire
	m_outputs = m_data[address];
	m_updated_inputs.reset();
	fireAllOutputs();
}

#endif // DATA_MEMORY_CPP_