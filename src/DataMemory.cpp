#ifndef DATA_MEMORY_CPP_
#define DATA_MEMORY_CPP_

#include "DataMemory.h"


const std::bitset<DataMemory::NUM_INPUTS> DataMemory::FULL_BIT_MASK_32 (0xFFFFFFFFul);


DataMemory::
DataMemory(unsigned long* _data, 
      unsigned long _start_address, 
      int _memory_size)
  
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS), 
    m_start_address(_start_address),
    m_end_address(_start_address + 4 * _memory_size) 
{
  m_data = new unsigned long[_memory_size];
  for (int i = 0; i < _memory_size; i++)
  {
    m_data[i] = _data[i];
  }
}


DataMemory::
~DataMemory()
{
  delete[] m_data;
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
  unsigned long index = (address - m_start_address) >> 2;
  return m_data[index];
}


void
DataMemory::
setData(unsigned long _address, unsigned long _data)
{
  unsigned long index = (address - m_start_address) >> 2;
  m_data[index] = _data;
}


#endif // DATA_MEMORY_CPP_