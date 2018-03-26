#ifndef ALU_CONTROL_H_
#define ALU_CONTROL_H_

#include "ProcessorComponent.h"

/************************************
ALU Control unit. Take in an ALU Op and a function field and calculates
a 3-bit control signal for the ALU.
The control signal consists of a Bnegate bit and 2 bits to select a MUX output.

Input lines:
	ALU_OP [1 - 0]
	FUNC_FIELD [7 - 2]

Output lines:
	Bnegate: [0]
	MuxSelect: [2 - 1]
************************************/



class ALUControl : public ProcessorComponent
{
	public:
		/// Constants
		static const int NUM_INPUTS = 8;
		static const int NUM_OUTPUTS = 3;

		// Input line IDs
		static const int ALU_OP_ID[2];
		static const int FUNC_FIELD_START_ID = 2;

		// Output line IDs
		static const int Bnegate;
		static const int MUX_SELECT_ID[2];

		ALUControl();

		void setInput(int _line_id, bool _bit);

		bool get Output(int _line_id);

		void updateOutput();

	private:

		std::bitset<NUM_INPUTS> m_inputs;

		std::bitset<NUM_OUTPUTS> m_outputs;

		std::bitset<NUM_INPUTS> m_updated_inputs;
};

#endif