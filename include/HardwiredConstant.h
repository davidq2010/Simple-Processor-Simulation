#ifndef HARDWIRED_CONSTANT_H_
#define HARDWIRED_CONSTANT_H_

#include "ProcessorComponent.h"
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
/// The HardwiredConstant is used for the PC ALU and the branch ALU
///
/// Input lines:
///  	Input_0 [0]
/// Output lines: [n lines]
///   The constant specified in the constructor expressed as a boolean array
////////////////////////////////////////////////////////////////////////////////
class HardwiredConstant : public ProcessorComponent
{
	public:
		HardwiredConstant(bool* _constant, int _n_bits); // An integer expressed as a bool array

    ~HardwiredConstant();

		void setInput(int _line_id=0, bool _clock=0); ///< Clock == 1 means it fired

		bool getOutput(int _line_id=0);

		void updateOutput();

    static const int NUM_INPUTS = 1;

	private:
    bool * m_hardwiredConstant;
    bool* m_outputs;
    std::bitset<NUM_INPUTS> m_inputs;
};

#endif // MUX_H_
