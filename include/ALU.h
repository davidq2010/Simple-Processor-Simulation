#ifndef ALU_H_
#define ALU_H_

#include <bitset>
#include <string>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Arithmetic and logic unit. Can perform the following opperations on two
/// 32-bit signed integers: ADD (ADDI), SUB, SLT, BEQ. The operations can be
/// specified using 4-bit opcode:
/// 	0010	Add
/// 	0110	Subtract
/// 	0111 	Set on less than
///
/// Input lines:
/// 	A 		[31 - 0 ]	First number
/// 	B 		[63 - 32]	Second number
/// 	control	[67 - 64] 	Specifies which operation to perform
/// Output lines
/// 	result 	[31 - 0] 	ALU result
/// 	zero 	[32] 		set if result == 0
/// When the control lines don't match exactly any of the instruction supported,
/// ALU has undefined behavior.
////////////////////////////////////////////////////////////////////////////////
class ALU : public ProcessorComponent
{
	public:
		static const int NUM_INPUTS = 68;
		static const int NUM_OUTPUTS = 33;

		static const int A_START_ID = 0;
		static const int B_START_ID = 32;
		static const int CONTROL_START_ID = 64;

		static const int ZERO_ID = 32;

		ALU(std::string _name);

		int inputStartID(bool inputNum)
		{
			return inputNum? B_START_ID : A_START_ID;
		}

		int controlStartID() { return CONTROL_START_ID; }

		int zeroID() 	{ return ZERO_ID; }

		void setInput(int _line_id, bool _bit);

		bool getOutput(int _line_id);

		void updateOutput();

	private:

		static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_32;

		static const std::bitset<NUM_INPUTS> CONTROL_BIT_MASK;

		std::bitset<NUM_INPUTS>  m_inputs; ///< Input bits

		std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

		std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated

		std::string m_name;
};

#endif // ALU_H_
