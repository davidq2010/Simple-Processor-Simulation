#ifndef SIGN_EXTENDER_H_
#define SIGN_EXTENDER_H_

#include <bitset>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Processor component that takes in a 16-bit signed integer and 
/// sign extends it to a 32-bit signed integer.
/// Input : 16 lines
/// Output: 32 lines
/// Line ID corresponds to the bit index in integer
////////////////////////////////////////////////////////////////////////////////
class SignExtender : public ProcessorComponent
{
  public:
    /// Constants
    static const int NUM_INPUTS = 16;
    
    static const int NUM_OUTPUTS = 32;

    SignExtender();

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id); 

    void updateOutput();

  private:
    std::bitset<NUM_INPUTS>  m_inputs; ///< Input bits

    std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

    std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated
};

#endif // SIGN_EXTENDER_H_