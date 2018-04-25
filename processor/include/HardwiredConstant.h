#ifndef HARDWIRED_CONSTANT_H_
#define HARDWIRED_CONSTANT_H_

#include "ProcessorComponent.h"

// STL
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief The HardwiredConstant is used to provide constant inputs to
/// components. An example of its use is to provide the constant 4 as input to
/// PC ALU. HardwiredConstant fires whenever the input line (clock line) is set
/// to high.
///
/// Input lines:
///   clock     [0]
///
/// Output lines:
///   constant  [(n-1) - 0]
////////////////////////////////////////////////////////////////////////////////
class HardwiredConstant : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{

    static const int NUM_INPUTS = 1;

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{
    ///
    /// @param _const   bit pattern specifying the output of each output line
    /// @param _n_bits  number of output lines
    HardwiredConstant(unsigned long _constant, int _n_bits);

    /// @param _const   boolean array specifying the output of each output line
    /// @param _n_bits  number of output lines
    HardwiredConstant(bool* _constant, int _n_bits);

    ~HardwiredConstant();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    /// @brief Calls updateOutput() if _clock is 1
    /// @param _line_id Shouldn't be set by user, only here because it extends
    /// ProcessorComponent.
    /// @param _clock Can be high or low
    void setInput(int _line_id = 0, bool _clock = 1);

    bool getOutput(int _line_id = 0);

    void updateOutput();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    bool* m_outputs;

};

#endif // HARDWIRED_CONSTANT_H_
