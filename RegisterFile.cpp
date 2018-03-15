#ifndef REGISTER_FILE_CPP_
#define REGISTER_FILE_CPP_

#include "RegisterFile.h"


const int RegisterFile::READ_REG_START_ID[2] = {0, 6}; 

const int RegisterFile::REG_DATA_START_ID[2] = {0, 32};

const std::bitset<RegisterFile::NUM_INPUTS> 
				RegisterFile::FULL_BIT_MASK_5(0b11111ul);
		/// All read (non-write) related inputs (input line 10 - 0)

const std::bitset<RegisterFile::NUM_INPUTS>
				RegisterFile::READ_INPUTS(0x3FFul);

const std::bitset<RegisterFile::NUM_INPUTS>
				RegisterFile::WRITE_INPUTS = ~READ_INPUTS;

RegisterFile::
RegisterFile() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}


void
RegisterFile::
setInput(int _line_id, bool _bit)
{
	m_inputs.set(_line_id, _bit);
	m_updated_inputs.set(_line_id);

	if (isAllReadInputsUpdated())
		updateOutput();
	else if (isAllWriteInputsUpdated())
		writeToRegister();
}


bool
RegisterFile::
getOutput(int _line_id)
{
	return m_outputs.test(_line_id);
}


bool
RegisterFile::
isAllReadInputsUpdated()
{
	return (m_inputs & READ_INPUTS) == READ_INPUTS;
}


bool
RegisterFile::
isAllWriteInputsUpdated()
{
	return (m_inputs & WRITE_INPUTS) == WRITE_INPUTS;
}


void 
RegisterFile::
updateOutput() 
{
	unsigned long data[2];

	// intepret input and get appropiate register data
	for (int port = 0; port <= 1; port++)
	{
		// get appropiate input line
		int start_id = readRegStartID(port);

		// get register number from input
		int reg_id = ((m_inputs >> start_id) & FULL_BIT_MASK_5).to_ulong();

		// get register data
		data[port] = m_registerData[reg_id];
	}

	// put data into output
	m_outputs = data[1];
	m_outputs >> 32;
	m_outputs |= data[0];

	// update
	m_updated_inputs &= WRITE_INPUTS; // clear all update bits of read inputs
	fireAllOutputs();
}

void
RegisterFile::
writeToRegister()
{
	if (m_inputs[writeControlID()]) // write if write line is set
	{
		// get write register number
		int reg_id = 
				((m_inputs >> writeRegStartID()) & FULL_BIT_MASK_5).to_ulong();
		// get write data
		unsigned long data = m_inputs >>	
	}
	
}

#endif // REGISTER_FILE_CPP_