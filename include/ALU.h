#ifndef ALU_H_
#define ALU_H_

#include <bitset>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Arithmetic and logic unit. Can perform the following opperations on two
/// 32-bit signed integers (A and B):
/// - ADD / ADDI
/// - SUB
/// - SLT
/// - BEQ
/// Input lines:
/// 	A 		[31 - 0 ]	First number
/// 	B 		[63 - 32]	Second number
/// 	Bnegate	[64] 		Set if doing subtraction (SUB, SLT, BEQ)
/// 	less 	[65] 		Set to check whether result < 0 (SLT) and set that
/// 						as new result
/// 	equal 	[66] 		Set to check whether result is 0 (BEQ)
/// Output lines
/// 	result 	[31 - 0] 	ALU result
/// 	zero 	[32] 		equal == 1 && result == 0
/// When the control lines don't match exactly any of the instruction supported,
/// ALU has undefined behavior.
////////////////////////////////////////////////////////////////////////////////
class ALU : public ProcessorComponent
{
	public:
		static const int NUM_INPUTS = 67;
		static const int NUM_OUTPUTS = 33;

		static const int A_START_ID = 0;
		static const int B_START_ID = 32;
		static const int B_NEGATE_ID = 64;
		static const int LESS_ID = 65;
		static const int EQUAL_ID = 66;

		static const int ZERO_ID = 32;

		ALU();

		int inputStartID(bool inputNum)
		{
			return inputNum? B_START_ID : A_START_ID;
		}

		int bNegateID() { return B_NEGATE_ID; }

		int lessID() 	{ return LESS_ID; }

		int equalID() 	{ return EQUAL_ID; }

		int zeroID() 	{ return ZERO_ID; }

		void setInput(int _line_id, bool _bit);

		bool getOutput(int _line_id);

		void updateOutput();

	private:

		static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_32;

		std::bitset<NUM_INPUTS>  m_inputs; ///< Input bits

		std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

		std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated
};

#endif // ALU_H_
