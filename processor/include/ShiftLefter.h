#ifndef SHIFT_LEFTER_H_
#define SHIFT_LEFTER_H_

#include "ProcessorComponent.h"

// STL
#include <bitset>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Processor component that takes in a n-bit integer and shift it left 
/// to a (n+2)-bit integer.
///
/// Input : n   lines
/// Output: n+2 lines
/// Line ID corresponds to the bit index in integer
////////////////////////////////////////////////////////////////////////////////
template <std::size_t NUM_INPUTS>
class ShiftLefter : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{

    ShiftLefter(std::string _name);

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id);

    /// @brief Sign extends the most significant bit and fires outputs
    void updateOutput();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    std::bitset<NUM_INPUTS>  m_inputs; ///< Input bits

    std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated

    std::string m_name;
};


template <std::size_t NUM_INPUTS>
ShiftLefter<NUM_INPUTS>::
ShiftLefter(std::string _name) 
  : ProcessorComponent(NUM_INPUTS, NUM_INPUTS + 2),
    m_name(_name)    
{
}


void
template <std::size_t NUM_INPUTS>
ShiftLefter<NUM_INPUTS>::
setInput(int _line_id, bool _bit)
{
  m_inputs.set(_line_id, _bit);

  m_updated_inputs.set(_line_id);
  if (m_updated_inputs.all())
    updateOutput();
}


void
template <std::size_t NUM_INPUTS>
ShiftLefter<NUM_INPUTS>::
getOutput(int _line_id)
{
  return (_line_id < 2)? 0 : m_inputs[_line_id - 2];
}


void
template <std::size_t NUM_INPUTS>
ShiftLefter<NUM_INPUTS>::
updateOutput()
{
  m_logger->log("--------------------------------------------------");
  m_logger->log(m_name);
  m_logger->log("  Input:");
  m_logger->log("  input", m_inputs.to_ulong());
  m_logger->log("  Output:");
  m_logger->log("  output" , m_inputs.to_ulong() << 2);

  m_updated_inputs.reset();

  fireAllOutputs();
}

#endif // SHIFT_LEFTER_H_
