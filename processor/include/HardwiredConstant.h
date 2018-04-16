#ifndef HARDWIRED_CONSTANT_H_
#define HARDWIRED_CONSTANT_H_

#include "ProcessorComponent.h"
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
/// The HardwiredConstant is used to provide constant inputs to components.
/// An example of its use is to provide the constant 4 as input to PC ALU.
/// HardwiredConstant fires whenever the input line (clock line) is set to high.
///
/// Input lines:
///   clock     [0]
/// Output lines:
///   constant  [(n-1) - 0]
////////////////////////////////////////////////////////////////////////////////
class HardwiredConstant : public ProcessorComponent
{
  public:
    static const int NUM_INPUTS = 1;

    HardwiredConstant(bool* _constant, int _n_bits); // An integer expressed as a bool array

    ~HardwiredConstant();

    void setInput(int _line_id = 0, bool _clock = 1); ///< Clock == 1 means it fired

    bool getOutput(int _line_id = 0);

    void updateOutput();

  private:
    bool* m_outputs;

};

#endif // MUX_H_
