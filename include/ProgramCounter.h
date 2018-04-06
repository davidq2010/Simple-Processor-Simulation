#ifndef PROGRAM_COUNTER_H_
#define PROGRAM_COUNTER_H_

#include <bitset>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Program counter - stores a 32-bit address pointing to the instruction
/// in instruction memory to be executed.
/// Input:
///   address   [31 - 0]
///   clock     [32]
/// Output:
///   address   [31 - 0]
///
/// Update timing: immediately after the clock line is set to high
/// the address is fired
////////////////////////////////////////////////////////////////////////////////
class ProgramCounter : public ProcessorComponent
{
  public:
    // Constants
    static const int NUM_INPUTS = 33;
    static const int NUM_OUTPUTS = 32;
    static const int CLOCK_ID = 32;

    ProgramCounter();
    
    int clockID() { return CLOCK_ID; }

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id);

  private:
    std::bitset<NUM_OUTPUTS> m_address;
};


#endif // PROGRAM_COUNTER_H_