#ifndef DATA_MEMORY_H_
#define DATA_MEMORY_H_

#include <bitset>
#include "ProcessorComponent.h"

////////////////////////////////////////////////////////////////////////////////
/// Data memory unit. Allow reading from and writing to memory, using 32-bit
/// address.
/// Input lines:
///   address     [31 - 0]    Address to read/write to
///   memRead     [32]        Set if reading
///   memWrite    [33]        Set if writing
///   writeData   [65 - 34]
/// Output lines
///   readData    [31 - 0]    Data at the specified read address
////////////////////////////////////////////////////////////////////////////////
class DataMemory : public ProcessorComponent
{
  public:

    //------------------------------------------------------------------------
    // Constants

    static const int NUM_INPUTS = 66;
    static const int NUM_OUTPUTS = 32;

    // Input line IDs
    static const int ADDRESS_START_ID    = 0;
    static const int MEM_READ_ID         = 32;
    static const int MEM_WRITE_ID        = 33;
    static const int WRITE_DATA_START_ID = 34;

    DataMemory(unsigned long* _data, 
               unsigned long _start_address, 
               int _memory_size);

    ~DataMemory();

    int addressStartID() { return ADDRESS_START_ID; }

    int memReadID() { return MEM_READ_ID; }

    int memWriteID() { return MEM_WRITE_ID; }
    
    int writeDataStartID() { return WRITE_DATA_START_ID; }

    void setInput(int _line_id, bool _bit);

    bool getOutput(int _line_id);

  private:
    //------------------------------------------------------------------------
    // IO related
    std::bitset<NUM_INPUTS> m_inputs; /// Input bits

    std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

    std::bitset<NUM_INPUTS>  m_updated_inputs; ///< keep track of which inputs are updated

    static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_32;

    void updateOutputs();

    //------------------------------------------------------------------------
    // Data
    unsigned long* m_data;

    unsigned long m_start_address;
    
    unsigned long m_end_address;
};

#endif // DATA_MEMORY_H_
