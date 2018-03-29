#ifndef CLOCK_CPP_
#define CLOCK_CPP_

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
rise()
{
	if (m_clock_state) return;
	m_clock_state = 1;
	fireAllOutputs();
}


void
Clock::
fall()
{
	if (!m_clock_state) return;
	m_clock_state = 0;
	fireAllOutputs();
}


#endif // CLOCK_CPP_
