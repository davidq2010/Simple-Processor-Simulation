#ifndef MUX_H_
#define MUX_H_

#include "ProcessorComponent.h"

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// Simulation of a multiplexor in a processor. This component takes in 2 n-bit
/// operands and 1 control signal. If the control signal is 0, the output is the
/// first operand, otherwise the output is the second operand.
///
/// Input lines:
///   control   [0]
///   operand0  [n  - 1]
///   operand1  [2n - n+1]
/// Output lines: [n] lines
///   operand0  if control == 0
///   operand1  if control == 1
////////////////////////////////////////////////////////////////////////////////
class MUX : public ProcessorComponent
{
  public:
    static const int CONTROL_LINE_ID = 0;
    static const int INPUT_0_START_ID = 1;

    ////////////////////////////////////////////////////////////////////////
    /// @param _n_bits number of bits of each input and of output
    ////////////////////////////////////////////////////////////////////////
    MUX(int _n_bits, std::string _name);

    ~MUX();

    int controlID() { return CONTROL_LINE_ID; }

    ////////////////////////////////////////////////////////////////////////
    /// @param _operand_num    specify the 0th or 1st operand
    /// @return the starting line id of the specified operand
    ////////////////////////////////////////////////////////////////////////
    int operandStartID(bool _operand_num)
    {
      return INPUT_0_START_ID + _operand_num * numOutputs();
    }

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id);

    void updateOutputs();

  private:
    bool* m_inputs;
    bool* m_outputs;
    bool* m_updated_inputs;

    std::string m_name;

    ////////////////////////////////////////////////////////////////////////
    /// @return true if all input lines have been updated
    ////////////////////////////////////////////////////////////////////////
    bool areAllInputsUpdated();
};

#endif // MUX_H_
