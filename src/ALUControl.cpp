#ifndef ALU_CONTROL_CPP_
#define ALU_CONTROL_CPP_

#include "ALUControl.h"

ALUControl::ALUControl() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}

const int ALU_OP_ID[2] = {0, 1};
const int MUX_SELECT_ID[2] = {1, 2}

void ALU:: setInput(int _line_id, bool _bit)
{
	m_inputs.set(_line_id, _bit);
	m_updated_inputs.set(_line_id);

	if (m_updated_inputs.all())
		updateOutput();
}

void ALUControl::updateOutput()
{
	if (m_inputs[ALU_OP_ID[1]]) //ADD, SUB, SLT
	{
		if (m_inputs[FUNC_FIELD_START_ID + 1] && m_inputs[FUNC_FIELD_START_ID + 3])
		{
			//output = 111
			Bnegate = 1;
			MUX_SELECT_ID[0] = 1;
			MUX_SELECT_ID[1] = 1;
		}
		else if (m_inputs[FUNC_FIELD_START_ID + 1])
		{
			//output = 110
			Bnegate = 1;
			MUX_SELECT_ID[0] = 1;
			MUX_SELECT_ID[1] = 0;
		}
		else
		{
			//output = 010
			Bnegate = 0;
			MUX_SELECT_ID[0] = 1;
			MUX_SELECT_ID[1] = 0;
		}
	}

	else if ( ! (m_inputs[ALU_OP_ID[0]]) || (m_inputs[ALU_OP_ID[1]])) //LW, SW, ADDI
	{
		//output = 010
		Bnegate = 0;
		MUX_SELECT_ID[0] = 1;
		MUX_SELECT_ID[1] = 0;
	}

	else if (m_inputs[ALU_OP_ID[0]]) //BEQ
	{
		//output = 110
		Bnegate = 1;
		MUX_SELECT_ID[0] = 1;
		MUX_SELECT_ID[1] = 0;
	}

	m_outputs[0] = Bnegate;
	m_outputs[1] = MUX_SELECT_ID[0];
	m_outputs[2] = MUX_SELECT_ID[1];




}