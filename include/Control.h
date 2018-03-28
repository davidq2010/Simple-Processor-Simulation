#ifndef CONTROL_H_
#define CONTROL_H_

#include <bitset>
#include <unordered_map>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Control unit. Will use input from instruction opcode to determine what
/// signals to send to the following output processor components:
///
/// Input lines:
///   Opcode    [5-0]     Instruction opcode
///
/// Output lines
/// 	RegDst    [0]
///   Jump      [1]
///   Branch    [2]
///   MemRead   [3]
///   MemToReg  [4]
///   ALUOp     [5-6]
///   MemWrite  [7]
///   ALUSrc    [8]
///   RegWrite  [9]
///
/// When the control lines don't match exactly any of the instruction supported,
/// Control Unit has undefined behavior.
////////////////////////////////////////////////////////////////////////////////
class Control : public ProcessorComponent
{
	public:
		static const int NUM_INPUTS  = 6;
		static const int NUM_OUTPUTS = 10;

    static const int OPCODE_ID = 0;
		static const int RESULT_ID = 0;

		Control();

		int opcodeID() 	{ return OPCODE_ID; }

		int resultID() 	{ return RESULT_ID; }

		void setInput(int _line_id, bool _bit);

		bool getOutput(int _line_id);

		void updateOutput();

	private:

    typedef std::unordered_map<std::bitset<NUM_INPUTS>,std::bitset<NUM_OUTPUTS>>
    opcodeMap;

    static const opcodeMap OPCODE_TABLE;  ///< Hashmap mapping input opcode bits
                                          ///< to which output line to fire

		std::bitset<NUM_INPUTS>  m_inputs;  /// Input bits

		std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

		std::bitset<NUM_INPUTS>  m_updated_inputs;  ///< Keep track of which inputs
                                                ///< are updated
};

#endif
