#ifndef DATA_MEMORY_H_
#define DATA_MEMORY_H_

#include "ProcessorComponent.h"

// STL
#include <bitset>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Data memory unit. Allow reading from and writing to memory, using 32-
/// bit address.
///
/// Input lines:
///   address     [31 - 0]    Address to read/write to
///   memRead     [32]        Set if reading
///   memWrite    [33]        Set if writing
///   writeData   [65 - 34]
///
/// Output lines
///   readData    [31 - 0]    Data at the specified read address
////////////////////////////////////////////////////////////////////////////////
class DataMemory : public ProcessorComponent
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constants
    /// @{

    static const int NUM_INPUTS = 66;
    static const int NUM_OUTPUTS = 32;

    ///< Input line IDs
    static const int ADDRESS_START_ID    = 0;
    static const int MEM_READ_ID         = 32;
    static const int MEM_WRITE_ID        = 33;
    static const int WRITE_DATA_START_ID = 34;

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors/Destructor
    /// @{
    ///
    /// @param _data vector of data corresponding to addresses
    /// @param _start_address starting address of Data Memory's data
    DataMemory(std::vector<unsigned long> _data, unsigned long _start_address);

    /// @deprecated
    DataMemory(unsigned long* _data,
               unsigned long _start_address,
               int _memory_size);

    ~DataMemory();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name Accessors/Manipulators
    /// @{

    int addressStartID() { return ADDRESS_START_ID; }

    int memReadID() { return MEM_READ_ID; }

    int memWriteID() { return MEM_WRITE_ID; }

    int writeDataStartID() { return WRITE_DATA_START_ID; }

    bool getOutput(int _line_id);

    ///@param _address Address in dataMem from which to retrieve data
    ///@return the data at _address
    unsigned long getData(unsigned long _address);

    void setInput(int _line_id, bool _bit);

    void setData(unsigned long _address, unsigned long _data);

    /// @}
    ////////////////////////////////////////////////////////////////////////////


  private:

    std::bitset<NUM_INPUTS>  m_inputs;  ///< Input bits

    std::bitset<NUM_OUTPUTS> m_outputs; ///< Output bits

    ///< keep track of which inputs are updated
    std::bitset<NUM_INPUTS>  m_updated_inputs;

    static const std::bitset<NUM_INPUTS> FULL_BIT_MASK_32; ///< bitmask

    /// @brief Updates output bits depending on whether read or write has been
    /// signalled. If read, get the data at address. If write, write data from
    /// write_data to address.
    void updateOutputs();

    std::vector<unsigned long> m_data; ///< Vector of data in dataMem

    unsigned long m_start_address;

    ///< Last address in data mem, based on data size
    unsigned long m_end_address;
};

#endif // DATA_MEMORY_H_
