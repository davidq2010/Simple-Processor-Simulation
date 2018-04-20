#include "Clock.h"

Clock::
Clock() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS), m_clock_state(0) {}


void
Clock::
setInput(int _line_id, bool _bit) {}


bool
Clock::
getOutput(int _line_id)
{
  return m_clock_state;
}


void
Clock::
tick()
{
  // clock rise
  m_clock_state = 1;
  fireAllOutputs();
  // clock fall
  m_clock_state = 0;
  fireAllOutputs();
}
