#ifndef SHIFT_LEFTER_H_
#define SHIFT_LEFTER_H_

#include "AbstractProcessorComponent.h"

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
class ShiftLefter : public AbstractProcessorComponent<NUM_INPUTS, NUM_INPUTS + 2>
{
  using AbstractProcessorComponent<NUM_INPUTS, NUM_INPUTS + 2>::m_inputs;
  using AbstractProcessorComponent<NUM_INPUTS, NUM_INPUTS + 2>::m_outputs;
  using AbstractProcessorComponent<NUM_INPUTS, NUM_INPUTS + 2>::m_logger;
  
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

    /// @brief output = input << 2
    void updateOutputs();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    std::string m_name;
};


template <std::size_t NUM_INPUTS>
ShiftLefter<NUM_INPUTS>::
ShiftLefter(std::string _name) 
  : AbstractProcessorComponent<NUM_INPUTS, NUM_INPUTS + 2>(),
    m_name(_name)    
{
}

template <std::size_t NUM_INPUTS>
void
ShiftLefter<NUM_INPUTS>::
updateOutputs()
{
  m_outputs = std::bitset<NUM_INPUTS+2>(m_inputs.to_string());
  m_outputs <<= 2;

  // Log inputs/outputs
  m_logger->log("--------------------------------------------------");
  m_logger->log(m_name);
  m_logger->log("  Input:");
  m_logger->log("  input", m_inputs.to_ulong());
  m_logger->log("  Output:");
  m_logger->log("  output" , m_inputs.to_ulong() << 2);
}

#endif // SHIFT_LEFTER_H_
