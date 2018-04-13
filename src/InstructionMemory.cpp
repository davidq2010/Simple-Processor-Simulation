#ifndef INSTRUCTION_MEMORY_CPP_
#define INSTRUCTION_MEMORY_CPP_

#include "InstructionMemory.h"


InstructionMemory::
InstructionMemory()
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS)
{
}


InstructionMemory::
InstructionMemory(std::std::vector<unsigned long> _data)
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS),
    m_data(_data)
{
}


InstructionMemory::
InstructionMemory(unsigned long* _data, int _n_data)
  : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS),
{
  m_data.reserve(_n_data);
  for (int i = 0; i < _n_data; i++)
    m_data.push_back(_data[i]);
}


InstructionMemory::
~InstructionMemory() {}


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
  for (unsigned long i = START_ADDRESS; i < START_ADDRESS + 4*m_num_data; i += 4)
    m_logger->log(i, getData(i));

  // fire
  m_updated_inputs.reset();
  fireAllOutputs();
}


unsigned long 
InstructionMemory::
getData(unsigned long _address)
{
  unsigned long index = (_address - START_ADDRESS) >> 2;
  return m_data[index];
}


void
InstructionMemory::
setData(unsigned long _address, unsigned long _data)
{
  unsigned long index = (_address - START_ADDRESS) >> 2;
  m_data[index] = _data;
}


void
InstructionMemory::
resetData(std::vector<unsigned long> _data)
{
  m_data = _data;
}


#endif // INSTRUCTION_MEMORY_CPP_
