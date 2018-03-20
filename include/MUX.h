#ifndef MUX_H_
#define MUX_H_

#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Simulation of a multiplexor in a processor. This component takes in 2 n-bit
/// inputs and 1 control signal. If the control signal is 0, the output is the
/// first n-bit input, otherwise the output is the second n-bit input.
///
/// Input lines: [2n + 1] lines
/// 	Control [0]
///  	Input_0 [n  - 1]
/// 	Input_1 [2n - n+1]
/// Output lines: [n] lines
/// 	Input_0 if control == 0
/// 	Input_1 if control == 1
////////////////////////////////////////////////////////////////////////////////
class MUX : public ProcessorComponent
{
	public:
		static const int CONTROL_LINE_ID = 0;
		static const int INPUT_0_START_ID = 1;

		////////////////////////////////////////////////////////////////////////
		/// @param _n_bits number of bits of each input and of output
		////////////////////////////////////////////////////////////////////////
		MUX(int _n_bits = 1);

		~MUX();

		int controlLineID() { return CONTROL_LINE_ID; }

		////////////////////////////////////////////////////////////////////////
		/// @param _input_num the 0th or 1st input
		/// @return the starting id of that input
		////////////////////////////////////////////////////////////////////////		
		int startID(bool _input_num) 
		{ 
			return INPUT_0_START_ID + _input_num * m_num_outputs; 
		}

		void setInput(int _line_id, bool _bit);

		bool getOutput(int _line_id);

		void updateOutput();

	private:
		bool* m_inputs;
		bool* m_outputs;
		bool* m_updated_inputs;

		////////////////////////////////////////////////////////////////////////
		/// @return true if all input lines have been updated
		////////////////////////////////////////////////////////////////////////		
		bool allInputsUpdated();
};

#endif // MUX_H_