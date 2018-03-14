#ifndef SIGN_EXTENDER_H_
#define SIGN_EXTENDER_H_

#include <bitset>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// \brief Processor component that takes in a 16-bit signed integer and 
/// sign extends it to a 32-bit signed integer.
/// Input: 16 lines, smaller line id corresponds to less significant bit
/// Output: 32 lines, smaller line id corresponds to less significant bit
///
/// To reduce computation, the output of this component is only updated after
/// all 16 input lines have been updated (through setInput method). 
////////////////////////////////////////////////////////////////////////////////
class SignExtender : public ProcessorComponent
{
	public:
		static const int NUM_INPUTS = 16;
		static const int NUM_OUTPUTS = 32;

		SignExtender();

		void setInput(int _line_id, bool _bit);

		bool getOutput(int _line_id); 

		void update();

	private:
		/// The 16 high bits are set to 1
		/// Used in extending negative number
		std::bitset<NUM_INPUTS>  m_inputs; /// Input bits

		std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

		std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which input is updated
};

#endif // SIGN_EXTENDER_H_