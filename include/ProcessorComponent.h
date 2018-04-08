#ifndef PROCESSOR_COMPONENT_H_
#define PROCESSOR_COMPONENT_H_

#include <string>
#include <vector>
#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
/// Abstract base class for a component of the processor.
/// Each input or and output line can be accessed by its ID. An input line's ID
/// ranges from 0 to (# of input lines - 1). Similarly, an output line's ID
/// ranges from 0 to (# of output lines - 1).
/// 
/// An output line of component can be directly connected 
/// to an input line of another component using addOutputComponent method. In
/// this case, whenever the output line of the 1st component is updated, 
/// the corresponding input line of the 2nd component is also set.
///
/// Unless otherwise specified, output lines of a component are only updated when 
/// all inputs to that component have been updated (through setInput method).
/// After updating output, the component waits until all of its input are
/// updated again before it updates the output again. 
////////////////////////////////////////////////////////////////////////////////
class ProcessorComponent
{
  public:

    //----------------------------------------------------------------------
    // Constructor / Destructor
    //----------------------------------------------------------------------

    ////////////////////////////////////////////////////////////////////////
    /// Constructor
    /// @param  _n_inputs   number of input lines
    /// @param  _n_outputs  number of output lines
    ////////////////////////////////////////////////////////////////////////
    ProcessorComponent(int _n_inputs, int _n_outputs);

    virtual ~ProcessorComponent();

    //----------------------------------------------------------------------
    // Input/output methods
    //----------------------------------------------------------------------
    
    ////////////////////////////////////////////////////////////////////////
    /// @return number of input lines
    ////////////////////////////////////////////////////////////////////////
    int numInputs() { return m_num_inputs; }
    
    ////////////////////////////////////////////////////////////////////////
    /// @return number of output lines
    ////////////////////////////////////////////////////////////////////////
    int numOutputs() { return m_num_outputs; }

    ////////////////////////////////////////////////////////////////////////
    /// Set the bit of an input line
    /// @param  _line_id   ID of input line
    /// @param  _bit       bit of input line
    ////////////////////////////////////////////////////////////////////////
    virtual void setInput(int _line_id, bool _bit) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// Get the bit of an output line
    /// @param  _line_id   ID of input line
    /// @return whether the line is high or low
    ////////////////////////////////////////////////////////////////////////
    virtual bool getOutput(int _line_id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// Connect an output line of this component to an input line of another
    /// component.
    /// @param  _output_id          the ID of the output line
    /// @param  _output_component   the component to output to
    /// @param  _input_id           the ID of input line of the output component
    ////////////////////////////////////////////////////////////////////////
    void addOutputComponent(int _output_id, 
                            ProcessorComponent& _output_component, 
                            int _input_id);

    //----------------------------------------------------------------------
    // Logging
    //----------------------------------------------------------------------
    void setLogger(Logger* _logger)

  protected:

    ////////////////////////////////////////////////////////////////////////
    /// Call setInput method of each component connected to each output line
    ////////////////////////////////////////////////////////////////////////
    void fireAllOutputs();

    Logger* m_logger;

  private:

    int m_num_inputs; ///< Number of input to this component

    int m_num_outputs; ///< Number of output to this component

    ////////////////////////////////////////////////////////////////////////
    /// Struct to store an output component and its input line ID
    ////////////////////////////////////////////////////////////////////////
    struct OutputComponent 
    {
      ProcessorComponent& output_component;
      int input_id;
    };

    /// Array mapping each output ID to its output components
    std::vector<OutputComponent>* m_output_lines;

};

#endif // PROCESSOR_COMPONENT_H_
