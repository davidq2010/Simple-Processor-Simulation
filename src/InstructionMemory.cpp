#ifndef INSTRUCTION_MEMORY_CPP_
#define INSTRUCTION_MEMORY_CPP_

#include "InstructionMemory.h"
#include "LoggerFactory.h"

InstructionMemory::
InstructionMemory(unsigned long* _data, int _n_data)
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS),
    m_num_data(_n_data)
{
  m_data = new unsigned long[_n_data];
  for (int i = 0; i < _n_data; i++)
    m_data[i] = _data[i];
}


InstructionMemory::
~InstructionMemory()
{
  delete[] m_data;
}


void
InstructionMemory::
setInput(int _line_id, bool _bit)
{
  m_inputs.set(_line_id, _bit);
  m_updated_inputs.set(_line_id);
  if (m_updated_inputs.all())
    updateOutputs();
}

bool
InstructionMemory::
getOutput(int _line_id)
{
  return m_outputs.test(_line_id);
}

void
InstructionMemory::
updateOutputs()
{
  unsigned long address = m_inputs.to_ulong();

  // output update
  m_outputs = getData(address);

  // log inputs and outputs
  m_logger->log("--------------------------------------------------");
  m_logger->log("Instruction Memory");
  m_logger->log("  Input:");
  m_logger->log("  address", address);
  m_logger->log("  Output:");
  m_logger->log("  instruction", m_outputs.to_ulong());
  m_logger->log("  Memory content:");
  for (int i = 0; i < m_num_data; i++)
  {
    unsigned long address_i = (unsigned long)i << 4 + START_ADDRESS;
    m_logger->log(address_i, m_data[i]);
  }

  // fire
  m_updated_inputs.reset();
  fireAllOutputs();
}


unsigned long 
DataMemory::
getData(unsigned long _address)
{
  unsigned long index = (address - START_ADDRESS) >> 2;
  return m_data[index];
}


void
DataMemory::
setData(unsigned long _address, unsigned long _data)
{
  unsigned long index = (address - START_ADDRESS) >> 2;
  m_data[index] = _data;
}


#endif // INSTRUCTION_MEMORY_CPP_
