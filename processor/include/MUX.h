#ifndef MUX_H_
#define MUX_H_

#include "ProcessorComponent.h"

// STL
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Representation of a multiplexor in a processor. This component takes
/// in 2 n-bit operands and 1 control signal. If the control signal is 0, the
/// output is the first operand, otherwise the output is the second operand.
///
/// Input lines:
///   control   [0]
///   operand0  [n  - 1]
///   operand1  [2n - n+1]
///
/// Output lines: [n] lines
///   operand0  if control == 0
///   operand1  if control == 1
////////////////////////////////////////////////////////////////////////////////
class MUX : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{

    static const int CONTROL_LINE_ID = 0;
    static const int INPUT_0_START_ID = 1;

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{
    ///
    /// @param _n_bits Number of bits for each input and of output
    /// @param _name Label for the MUX
    MUX(int _n_bits, std::string _name);

    ~MUX();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    int controlID() { return CONTROL_LINE_ID; }

    /// @param _operand_num Specifies the 0th or 1st operand
    /// @return The starting line ID of the specified operand
    int operandStartID(bool _operand_num)
    {
      // numOutputs() returns _n_bits
      return INPUT_0_START_ID + _operand_num * numOutputs();
    }

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id);

    /// @brief Updates output wires according to the operand selected by control
    void updateOutputs();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


  private:

    ///< bool arrays are dynamically allocated since we don't know size until
    /// runtime
    bool* m_inputs;
    bool* m_outputs;
    bool* m_updated_inputs;

    std::string m_name;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Needed since m_updated_inputs is a bool array, not a bitset
    /// @return true if all input lines have been updated
    ////////////////////////////////////////////////////////////////////////////
    bool areAllInputsUpdated();
};

#endif // MUX_H_
