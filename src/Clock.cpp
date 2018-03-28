#ifndef CLOCK_CPP_
#define CLOCK_CPP_


Clock::
Clock() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS), m_clock_state(0) {}


void
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