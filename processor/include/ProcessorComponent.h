#ifndef PROCESSOR_COMPONENT_H_
#define PROCESSOR_COMPONENT_H_

#include "Logger.h"

// STL
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Abstract base class for a component of the processor.
/// Each input or and output line can be accessed by its ID. An input line's ID
/// ranges from 0 to (# of input lines - 1). Similarly, an output line's ID
/// ranges from 0 to (# of output lines - 1).
///
/// @details An output line of component can be directly connected
/// to an input line of another component using addOutputComponent method. In
/// this case, whenever the output line of the 1st component is updated,
/// the corresponding input line of the 2nd component is also set.
///
/// Unless otherwise specified, output lines of a component are only updated
/// when all inputs to that component have been updated (through setInput
/// method). After updating output, the component waits until all of its inputs
/// are updated again before it updates the output again.
////////////////////////////////////////////////////////////////////////////////
class ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{
    ///
    /// @param  _n_inputs   number of input lines
    /// @param  _n_outputs  number of output lines
    ProcessorComponent(int _n_inputs, int _n_outputs);

    virtual ~ProcessorComponent();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    /// @return number of input lines
    int numInputs() { return m_num_inputs; }

    /// @return number of output lines
    int numOutputs() { return m_num_outputs; }

    /// @brief Get the bit of an output line
    /// @param  _line_id   ID of output line
    /// @return whether the line is high or low
    virtual bool getOutput(int _line_id) = 0;

    /// @brief Set the bit of an input line
    /// @param  _line_id   ID of input line
    /// @param  _bit       bit of input line
    virtual void setInput(int _line_id, bool _bit) = 0;

    /// @brief Assign the processor component a logger
    /// @param  _logger Pointer to a Logger for all processor components to
    /// share
    void setLogger(Logger* _logger);

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @brief Connect an output line of this component to an input line of
    /// another component.
    /// @param  _output_id          the ID of the output line
    /// @param  _output_component   the component to output to
    /// @param  _input_id           the ID of input line of the output component
    ////////////////////////////////////////////////////////////////////////////
    void addOutputComponent(int _output_id,
                            ProcessorComponent& _output_component,
                            int _input_id);


  protected:

    ////////////////////////////////////////////////////////////////////////////
    /// @details Triggers the setInput() methods of each OutputComponent's input
    /// lines, in sequential order.
    ////////////////////////////////////////////////////////////////////////////
    void fireAllOutputs();


    Logger* m_logger;   ///< Logger to be shared among processor components


  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Struct to store an output component and its input line ID
    ////////////////////////////////////////////////////////////////////////////
    struct OutputComponent
    {
      ProcessorComponent& output_component;
      int input_id;
    };


    ///< Array mapping each output line ID of the current component to its
    ///< OutputComponent (output_component, its input line ID)
    ///< (i.e. some lines go to multiple components)
    std::vector<OutputComponent>* m_output_lines;

    int m_num_inputs;   ///< Number of inputs to this component

    int m_num_outputs;  ///< Number of outputs for this component
};

#endif // PROCESSOR_COMPONENT_H_
