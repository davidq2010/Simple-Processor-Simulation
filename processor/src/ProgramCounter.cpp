#include "ProgramCounter.h"

ProgramCounter::
ProgramCounter() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {}


void
ProgramCounter::
setInput(int _line_id, bool _bit)
{
  if (_line_id == CLOCK_ID){
    if (_bit)
      fireAllOutputs();
  }
  else
    m_address[_line_id] = _bit;
}

bool
ProgramCounter::
getOutput(int _line_id)
{
  return m_address.test(_line_id);
}

unsigned long
ProgramCounter::
getInstructionAddress(int _line_id)
{
  return m_address.to_ulong();
}