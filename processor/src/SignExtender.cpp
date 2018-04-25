#include "SignExtender.h"

//TODO: Delete this
#include <iostream>

SignExtender::
SignExtender() : ProcessorComponent(NUM_INPUTS, NUM_OUTPUTS) {};

void
SignExtender::
setInput(int _line_id, bool _bit)
{
  m_inputs.set(_line_id, _bit);

  m_updated_inputs.set(_line_id);
  if (m_updated_inputs.all())
    updateOutput();
}

bool
SignExtender::
getOutput(int _line_id)
{
  return m_outputs.test(_line_id);
}

void
SignExtender::
updateOutput()
{
  for (int i = 0; i < NUM_INPUTS; i++)
    m_outputs[i] = m_inputs[i];

  bool sign_bit = m_outputs[NUM_INPUTS - 1];
  for (int i = NUM_INPUTS; i < NUM_OUTPUTS; i++)
    m_outputs[i] = sign_bit;

  m_updated_inputs.reset();

  unsigned long log_input = 0ul;
  unsigned long log_output = 0ul;
  for (int i = NUM_INPUTS - 1; i >= 0; i--)
  {
    log_input <<= 1;
    log_input |= m_inputs[i];
  }
  for (int i = NUM_OUTPUTS - 1; i >= 0; i--)
  {
    log_output <<= 1;
    log_output |= m_outputs[i];
  }
  m_logger->log("--------------------------------------------------");
  m_logger->log("Sign Extender");
  m_logger->log("  Input:");
  m_logger->log("  immediate", log_input);
  m_logger->log("  Output:");
  m_logger->log("  extended" , log_output);

  fireAllOutputs();
}
