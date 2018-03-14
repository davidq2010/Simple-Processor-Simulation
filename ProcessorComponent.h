#ifndef PROCESSOR_COMPONENT_H_
#define PROCESSOR_COMPONENT_H_

#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////
class ProcessorComponent
{
	public:
		ProcessorComponent(int _n_inputs, int _n_outputs);

		~ProcessorComponent();
		
		int numInputs() { return m_num_inputs; }
		
		int numOutputs() { return m_num_outputs; }

		void addOutputComponent(int _output_id, 
								ProcessorComponent& _output_component, 
								int _input_id);

		virtual void setInput(int _line_id, bool _bit) = 0;

		virtual bool getOutput(int _line_id) = 0;

	protected:
		////////////////////////////////////////////////////////////////////////
		/// An output line 
		////////////////////////////////////////////////////////////////////////
		struct OutputLine 
		{
			ProcessorComponent& output_component;
			int input_id;
		};

		int m_num_inputs;

		int m_num_outputs;

		/// Map each output id to its output components
		std::vector<OutputLine>* m_output_lines;

		void fireAllOutputs();
};

#endif // PROCESSOR_COMPONENT_H_