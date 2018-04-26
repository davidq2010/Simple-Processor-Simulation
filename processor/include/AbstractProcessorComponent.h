#ifndef ABSTRACT_PROCESSOR_COMPONENT_H_
#define ABSTRACT_PROCESSOR_COMPONENT_H_

#include "ProcessorComponent.h"

// STL
#include <bitset>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Skeletal implementation of processor component that handles 
/// inputs/outputs get and set methods.
///
/// @detail The default behavior for this abstract component is to update and 
/// fire output after all inputs have been updated. Derived components have to 
/// implement updateOutput method to provide specific ouput calculation.
////////////////////////////////////////////////////////////////////////////////
template <std::size_t NUM_INPUTS, std::size_t NUM_OUTPUTS>
class AbstractProcessorComponent : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{

    AbstractProcessorComponent();

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    /// @brief  Set an input line to high or low
    /// @detail When all input lines are updated, the component automatically
    /// fire outputs to connected components
    /// @param  _line_id the index of the input line
    /// @param  _bit     set the input line to this bit
    void setInput(int _line_id, bool _bit);

    /// @return The current bit of an output line
    bool getOutput(int _line_id);

    /// @brief Overriden by different components, allow each derived component
    /// to specify output calculation
    virtual void updateOutputs() = 0;

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  protected:

    std::bitset<NUM_INPUTS>  m_inputs;  ///< Input bits

    std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

    std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs have been updated
};


template <std::size_t NUM_INPUTS, std::size_t NUM_OUTPUTS>
AbstractProcessorComponent<NUM_INPUTS, NUM_OUTPUTS>::
AbstractProcessorComponent() 
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS)
{
}


template <std::size_t NUM_INPUTS, std::size_t NUM_OUTPUTS>
void
AbstractProcessorComponent<NUM_INPUTS, NUM_OUTPUTS>::
setInput(int _line_id, bool _bit)
{
  m_inputs.set(_line_id, _bit);

  m_updated_inputs.set(_line_id);
  if (m_updated_inputs.all()) 
  {
    updateOutputs();
    m_updated_inputs.reset();
    fireAllOutputs();
  }
}


template <std::size_t NUM_INPUTS, std::size_t NUM_OUTPUTS>
bool
AbstractProcessorComponent<NUM_INPUTS, NUM_OUTPUTS>::
getOutput(int _line_id)
{
  return m_outputs.test(_line_id);
}

#endif // ABSTRACT_PROCESSOR_COMPONENT_H_
