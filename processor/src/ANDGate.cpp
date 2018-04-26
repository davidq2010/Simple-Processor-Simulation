#include "ANDGate.h"

ANDGate::
ANDGate() : AbstractProcessorComponent<NUM_INPUTS, NUM_OUTPUTS>() {}


void
ANDGate::
updateOutputs()
{
  m_outputs[0] = m_inputs[0] & m_inputs[1];
}
