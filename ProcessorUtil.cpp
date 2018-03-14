#ifndef PROCESSOR_UTIL_CPP_
#define PROCESSOR_UTIL_CPP_

#include "ProcessorUtil.h"


namespace ioutil
{
	
	void setInputs(ProcessorComponent& _comp, unsigned long _input)
	{
		for (int i = 0; i < _comp.numInputs(); i++)
		{
			_comp.setInput(i, _input & 1UL);
			_input >>= 1;
		}
	}


	unsigned long getOutputs(ProcessorComponent& _comp)
	{
		unsigned long output = 0UL;
		for (int i = _comp.numOutputs() - 1; i >= 0; i--)
		{
			output <<= 1;
			output |= _comp.getOutput(i);
		}
		return output;
	}
}


#endif // PROCESSOR_UTIL_CPP_