#ifndef REGISTER_FILE_CPP_
#define REGISTER_FILE_CPP_

#include <string>
#include "RegisterFile.h"


const int RegisterFile::READ_REG_START_ID[2] = {0, 5};

const int RegisterFile::REG_DATA_START_ID[2] = {0, 32};

const std::bitset<RegisterFile::NUM_INPUTS>
				RegisterFile::FULL_BIT_MASK_5(0b11111ul);

const std::bitset<RegisterFile::NUM_INPUTS>
				RegisterFile::FULL_BIT_MASK_32(0xFFFFFFFFul);

const std::bitset<RegisterFile::NUM_INPUTS>
				RegisterFile::READ_INPUTS(0x3FFul);

const std::bitset<RegisterFile::NUM_INPUTS>
				RegisterFile::WRITE_INPUTS = ~READ_INPUTS;


RegisterFile::
RegisterFile() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}


RegisterFile::
RegisterFile(unsigned long _data[])
		: ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS)
{
	for (int i = 0; i < NUM_REGS; i++)
		m_register_data[i] = _data[i];
}


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
	return (m_updated_inputs & READ_INPUTS) == READ_INPUTS;
}


bool
RegisterFile::
isAllWriteInputsUpdated()
{
	return (m_updated_inputs & WRITE_INPUTS) == WRITE_INPUTS;
}


void
RegisterFile::
updateOutput()
{
	unsigned long reg_id[2];
	unsigned long reg_data[2];

	// intepret input and get appropiate register data
	for (int port = 0; port <= 1; port++)
	{
		// get appropiate input line
		int start_id = readRegStartID(port);

		// get register number from input
		reg_id[port] = ((m_inputs >> start_id) & FULL_BIT_MASK_5).to_ulong();

		// get register data
		reg_data[port] = m_register_data[reg_id[port]];
	}

	// put data into output
	m_outputs = reg_data[1];
	m_outputs <<= 32;
	m_outputs |= reg_data[0];


	// Log input and output
	Logger logger = LoggerFactory::getLogger();
	logger.log("--------------------------------------------------");
	logger.log("Register File Read");
	logger.log("  Content:");

	for (int i = 0; i < NUM_REGS; i++)
		logger.log(std::string("    Reg") + std::to_string(i), m_register_data[i]);

	logger.log("  Input:");
	logger.log("  Reg1", reg_id[0]);
	logger.log("  Reg2", reg_id[1]);
	logger.log("  Output:");
	logger.log("  Data1", reg_data[0]);
	logger.log("  Data2", reg_data[1]);


	// update
	m_updated_inputs &= WRITE_INPUTS; // clear all update bits of read inputs
	fireAllOutputs();
}

void
RegisterFile::
writeToRegister()
{
	m_updated_inputs &= READ_INPUTS; // clear all update bit of write inputs

	if (!m_inputs[writeControlID()]) // don't write if write line is low
		return;

	// get write register number
	int reg_id =
			((m_inputs >> writeRegStartID()) & FULL_BIT_MASK_5).to_ulong();
	// get write data
	unsigned long data =
			((m_inputs >> writeDataStartID()) & FULL_BIT_MASK_32).to_ulong();

	m_register_data[reg_id] = data;
}

#endif // REGISTER_FILE_CPP_
