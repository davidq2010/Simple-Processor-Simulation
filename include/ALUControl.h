#ifndef ALU_CONTROL_H_
#define ALU_CONTROL_H_

#include "ProcessorComponent.h"
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
/// ALU Control unit. Take in an ALU Op and a function field and calculates
/// a 4-bit control signal for the ALU. Only implement a subset of instructions.
/// Input lines:
/// 	ALUOp 		[1 - 0]
/// 	func 		[7 - 2]
/// Output lines:
/// 	control 	[3 - 0]
///
/// Input - output mapping:
/// 	ALUOp 	func 		ALU Action 					Output
///
/// 	00 		XXXXXX		Add (for LW, SW, ADDI)		0010
/// 	01 		XXXXXX		Subtract (for BEQ)			0110
/// 	10 		100000		R-type, Add 				0010
/// 	10 		100010 		R-type, Substract 			0110
/// 	10 		101010 		R-type, Set on less than 	0111
///
////////////////////////////////////////////////////////////////////////////////
class ALUControl : public ProcessorComponent
{
	public:
		/// Constants
		static const int NUM_INPUTS = 8;
		static const int NUM_OUTPUTS = 4;

		static const unsigned long OP_ADD    = 0b00;
		static const unsigned long OP_SUB    = 0b01;
		static const unsigned long OP_R_TYPE = 0b10;

		static const unsigned long FUNC_ADD  = 0b100000;
		static const unsigned long FUNC_SUB  = 0b100010;
		static const unsigned long FUNC_SLT  = 0b101010;

		static const unsigned long OUT_ADD   = 0b0010;
		static const unsigned long OUT_SUB   = 0b0110;
		static const unsigned long OUT_SLT   = 0b0111;

		// Input line IDs
		static const int ALU_OP_START_ID = 0;
		static const int FUNC_START_ID = 2;


		ALUControl();

		int aluOpStartID() { return ALU_OP_START_ID; }

		int funcStartID()  { return FUNC_START_ID; }

		void setInput(int _line_id, bool _bit);

		bool getOutput(int _line_id);



		void updateOutputs();

	private:

		static const std::bitset<NUM_INPUTS> ALU_OP_MASK;

		std::bitset<NUM_INPUTS> m_inputs;

		std::bitset<NUM_OUTPUTS> m_outputs;

		std::bitset<NUM_INPUTS> m_updated_inputs;
};

#endif
