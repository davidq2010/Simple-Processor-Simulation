#include "ProcessorUtil.h"


namespace ioutil
{

  void setInputs(ProcessorComponent& _comp, unsigned long long _input)
  {
    for (int i = 0; i < _comp.numInputs(); i++)
    {
      _comp.setInput(i, _input & 1ull);
      _input >>= 1;
    }
  }


  unsigned long long getOutputs(ProcessorComponent& _comp)
  {
    unsigned long long output = 0;
    for (int i = _comp.numOutputs() - 1; i >= 0; i--)
    {
      output <<= 1;
      output |= _comp.getOutput(i);
    }
    return output;
  }
}
