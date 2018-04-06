#ifndef AND_H_
#define AND_H_

#include "ProcessorComponent.h"
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
/// Simple AND gate.
///
/// Input lines:
///   Input_0 [0]
///   Input_1 [1]
/// Output lines:
///   Result  [0]   Input_0 && Input_1
////////////////////////////////////////////////////////////////////////////////
class ANDGate : public ProcessorComponent
{
  public:
    ANDGate();

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id=0);

    void updateOutput();

    static const int NUM_INPUTS = 2;
    static const int NUM_OUTPUTS = 1;

  private:
    std::bitset<NUM_INPUTS>  m_inputs;
    std::bitset<NUM_OUTPUTS> m_outputs;
    std::bitset<NUM_INPUTS>  m_updated_inputs;

    ////////////////////////////////////////////////////////////////////////
    /// @return true if all input lines have been updated
    ////////////////////////////////////////////////////////////////////////
    bool allInputsUpdated();
};

#endif // MUX_H_
