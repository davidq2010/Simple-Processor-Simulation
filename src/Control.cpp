#ifndef CONTROL_CPP_
#define CONTROL_CPP_

#include "Control.h"

const Control::opcodeMap Control::OPCODE_TABLE
({
 // R-Type instructions
 {std::bitset<NUM_INPUTS>("000000"), std::bitset<NUM_OUTPUTS>("1000010001")},

 // ADDI
 {std::bitset<NUM_INPUTS>("001000"), std::bitset<NUM_OUTPUTS>("0000000011")},

 // LW
 {std::bitset<NUM_INPUTS>("100000"), std::bitset<NUM_OUTPUTS>("0001100011")},

 // SW (RegDst/MemToReg don't matter)
 {std::bitset<NUM_INPUTS>("101011"), std::bitset<NUM_OUTPUTS>("0000000110")},

 // BEQ (RegDst/MemToReg don't matter)
 {std::bitset<NUM_INPUTS>("000100"), std::bitset<NUM_OUTPUTS>("0010010000")},

 // J (No other fields matter but jump)
 {std::bitset<NUM_INPUTS>("000010"), std::bitset<NUM_OUTPUTS>("0100000000")}
 });

Control::
Control() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}


void
Control::
setInput(int _line_id, bool _bit)
{
	m_inputs.set(_line_id, _bit);

	m_updated_inputs.set(_line_id);

	if (m_updated_inputs.all())
		updateOutput();
}


bool
Control::
getOutput(int _line_id)
{
	return m_outputs.test(_line_id);
}


void
Control::
updateOutput()
{
  // Check if the input bits match an opcode. If it does, output the correct bit
  // to the correct wire.

  // Look up the output bits for that inputs std::bitset and put into m_outputs
  m_outputs = OPCODE_TABLE.at(m_inputs);

	// update
	m_updated_inputs.reset();
	fireAllOutputs();
}


#endif
