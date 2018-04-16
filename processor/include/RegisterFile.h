#ifndef REGISTER_FILE_H_
#define REGISTER_FILE_H_

#include <bitset>
#include "vector"
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Contains 32 registers, as well as 2 read ports and 1 write port.
/// Input lines: (49 lines)
///   readReg0    [4  - 0 ] (5 lines)
///   readReg1    [9  - 5 ] (5 lines)
///   writeReg    [14 - 10] (5 lines)
///   writeData     [46 - 15] (32 lines)
///   writeControl  [47]
/// Output lines: D(64 lines)
///   regData0    [31 - 0 ] (32 lines)
///   regData1    [63 - 32] (32 lines)
/// Read and write ports function separately, i.e registerData output lines
/// get updated right after all 10 readRegister input lines get updated.
/// Writing occurs if writeReg, writeData, writeControl are all updated and
/// writeControl line is high.
/// Note that registerData ouput lines do not get automatically updated after
/// a write has been done. To get up-to-date output after a write, simply set
/// all readRegister lines again. Best practice is to read before write in
/// a cycle.
////////////////////////////////////////////////////////////////////////////////
class RegisterFile : public ProcessorComponent
{
  public:

    //------------------------------------------------------------------------
    // Constants

    static const int NUM_REGS = 32;
    static const int NUM_INPUTS = 48;
    static const int NUM_OUTPUTS = 64;

    // Input line IDs
    static const int READ_REG_START_ID[2];
    static const int WRITE_REG_START_ID = 10;
    static const int WRITE_DATA_START_ID = 15;
    static const int WRITE_CONTROL_ID = 47;

    // Output line IDs
    static const int REG_DATA_START_ID[2];

    RegisterFile();

    RegisterFile(unsigned long _data[]);

    RegisterFile(std::vector<unsigned long> _data);

    //------------------------------------------------------------------------
    // Line ID getters

    int readRegStartID(bool _port_num)
    {
      return READ_REG_START_ID[_port_num];
    }

    int writeRegStartID()  { return WRITE_REG_START_ID; }

    int writeDataStartID() { return WRITE_DATA_START_ID; }

    int writeControlID()   { return WRITE_CONTROL_ID; }

    int regDataStartID(bool _port_num)
    {
      return REG_DATA_START_ID[_port_num];
    }

    //------------------------------------------------------------------------
    // IO methods

    void setInput(int _line_id, bool _bit = 1);

    bool getOutput(int _line_id);

    void updateOutputs();

  private:

    //------------------------------------------------------------------------
    // IO related
    std::bitset<NUM_INPUTS>  m_inputs;

    std::bitset<NUM_OUTPUTS> m_outputs;

    std::bitset<NUM_INPUTS>  m_updated_inputs;

    /// Bitset with 5 last bit set, used to extract register number from inputs
    static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_5;

    /// Bitset with 32 last bit set, used to extract word from inputs
    static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_32;

    /// All read (non-write) related inputs (input line 10 - 0)
    static const std::bitset<NUM_INPUTS> READ_INPUTS;

    /// All write (non-read) related inputs (input line 48 - 11)
    static const std::bitset<NUM_INPUTS> WRITE_INPUTS;

    bool areAllReadInputsUpdated();

    bool areAllWriteInputsUpdated();

    //------------------------------------------------------------------------
    // Memory related
    unsigned long m_register_data[NUM_REGS];

    void writeToRegister();
};

#endif // REGISTER_FILE_H_
