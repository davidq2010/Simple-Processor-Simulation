#ifndef CLOCK_H_
#define CLOCK_H_

#include "ProcessorComponent.h"

class Clock : public ProcessorComponent
{
	public:
		// Constants
		static const int NUM_INPUTS = 0;
		static const int NUM_OUTPUTS = 1;

		Clock();

		bool getOutput(int _line_id = 0);

		void rise();

		void fall();

	private:
		bool m_clock_state;
};


#endif // CLOCK_H_
