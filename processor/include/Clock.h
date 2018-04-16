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

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id = 0);

    void tick();

  private:
    bool m_clock_state;
};


#endif // CLOCK_H_
