#ifndef PROCESSOR_COMPONENT_H_
#define PROCESSOR_COMPONENT_H_

#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// Abstract base class for an unit on the processor.
/// Input to and output from a component is accessed through setInput and 
/// getOutput methods. An output line of component A can be directly connected 
/// to an input line of component B by using method A.addOutputComponent. In
/// this case, whenever A's output is updated, A will automatically set B's
/// input to the new output.
/// Unless otherwise specified, output lines of a component are only updated when 
/// all inputs to that component have been updated (through setInput method).
/// After updating output, the component waits until all of its input are
/// updated again before it updates the output a second time. 
////////////////////////////////////////////////////////////////////////////////
class ProcessorComponent
{
	public:
		////////////////////////////////////////////////////////////////////////
		/// Constructor
		/// @param 	_n_inputs 	number of input lines
		/// @param 	_n_outputs 	number of output lines
		////////////////////////////////////////////////////////////////////////
		ProcessorComponent(int _n_inputs, int _n_outputs);

		virtual ~ProcessorComponent();
		
		////////////////////////////////////////////////////////////////////////
		/// @return	number of input lines
		////////////////////////////////////////////////////////////////////////
		int numInputs() { return m_num_inputs; }
		
		////////////////////////////////////////////////////////////////////////
		/// @return	number of output lines
		////////////////////////////////////////////////////////////////////////
		int numOutputs() { return m_num_outputs; }

		////////////////////////////////////////////////////////////////////////
		/// Connect the output line of this input to an input line of another
		/// component.
		/// @param	_output_id 			the ID of the output line
		/// @param 	_output_component 	the component to output to
		/// @param 	_input_id 			the ID of input line of the output
		/// 							component
		////////////////////////////////////////////////////////////////////////
		void addOutputComponent(int _output_id, 
								ProcessorComponent& _output_component, 
								int _input_id);

		////////////////////////////////////////////////////////////////////////
		/// Set the bit of an input line
		////////////////////////////////////////////////////////////////////////
		virtual void setInput(int _line_id, bool _bit) = 0;

		////////////////////////////////////////////////////////////////////////
		/// Get the bit of an output line
		////////////////////////////////////////////////////////////////////////
		virtual bool getOutput(int _line_id) = 0;

	protected:
		////////////////////////////////////////////////////////////////////////
		/// Struct to store an output component and its input line ID
		////////////////////////////////////////////////////////////////////////
		struct OutputLine 
		{
			ProcessorComponent& output_component;
			int input_id;
		};

		////////////////////////////////////////////////////////////////////////
		/// Call setInput method of each component connected to each output line
		////////////////////////////////////////////////////////////////////////
		void fireAllOutputs();

		int m_num_inputs; ///< Number of input to this component

		int m_num_outputs; ///< Number of output to this component

		/// Map each output ID to its output components
		std::vector<OutputLine>* m_output_lines;

};

#endif // PROCESSOR_COMPONENT_H_