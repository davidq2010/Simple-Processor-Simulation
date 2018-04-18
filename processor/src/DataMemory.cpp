#include "DataMemory.h"

#include <stdexcept>
#include <sstream>


const std::bitset<DataMemory::NUM_INPUTS> DataMemory::FULL_BIT_MASK_32 (0xFFFFFFFFul);


DataMemory::
DataMemory(std::vector<unsigned long> _data, unsigned long _start_address)
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS),
    m_data(_data),
    m_start_address(_start_address),
    m_end_address(_start_address + _data.size() * 4)
{
}



DataMemory::
DataMemory(unsigned long* _data, 
           unsigned long _start_address, 
           int _memory_size)
  
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS), 
    m_data(_data, _data + _memory_size),
    m_start_address(_start_address),
    m_end_address(_start_address + 4 * _memory_size) 
{
}


DataMemory::
~DataMemory()
{
}


void
DataMemory::
setInput(int _line_id, bool _bit)
{
  m_inputs.set(_line_id, _bit);
  m_updated_inputs.set(_line_id);
  if (m_updated_inputs.all())
    updateOutputs();
}

bool
DataMemory::
getOutput(int _line_id)
{
  return m_outputs.test(_line_id);
}

void
DataMemory::
updateOutputs()
{
  unsigned long address = 
      ((m_inputs >> addressStartID()) & FULL_BIT_MASK_32).to_ulong();
  
  unsigned long write_data = 
        ((m_inputs >> writeDataStartID()) & FULL_BIT_MASK_32).to_ulong();
  
  //read
  if (m_inputs[ memReadID() ])
    m_outputs = getData(address);
  else
    m_outputs.reset();
  
  // write
  if (m_inputs[memWriteID()])
    setData(address, write_data);

  // log
  m_logger->log("--------------------------------------------------");
  m_logger->log("Data Memory");
  m_logger->log("  Input:");
  m_logger->log("  address" , address);
  m_logger->log("  memRead" , m_inputs[memReadID()]);
  m_logger->log("  memWrite", m_inputs[memWriteID()]);
  m_logger->log("  Output:");
  m_logger->log("  readData", m_outputs.to_ulong());
  m_logger->log("  Memory content:");
  for (unsigned long i = m_start_address; i < m_end_address; i += 4)
  {
    m_logger->log(i, getData(i));
  }

  // output update and fire
  m_updated_inputs.reset();
  fireAllOutputs();
}


unsigned long 
DataMemory::
getData(unsigned long _address)
{
  unsigned long index = (_address - m_start_address) >> 2;
  if (index >= m_data.size()) {
    std::stringstream ss;
    ss << "DataMemory: address out of bound :";
    ss << std::hex << std::showbase << std::uppercase << _address; 
    throw std::out_of_range(ss.str());
  }
  return m_data[index];
}


void
DataMemory::
setData(unsigned long _address, unsigned long _data)
{
  unsigned long index = (_address - m_start_address) >> 2;
  if (index >= m_data.size()) {
    std::stringstream ss;
    ss << "DataMemory: address out of bound :";
    ss << std::hex << "0x" << std::uppercase << _address; 
    throw std::out_of_range(ss.str());
  }

  m_data[index] = _data;
}

