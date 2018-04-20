#include <iostream>
#include <iomanip>
#include "Logger.h"

using namespace std;

Logger::
Logger(ostream& _out) : m_out(_out) {}


Logger::
~Logger() {}


void
Logger::
log(string msg)
{
  m_out << msg << endl;
}


void
Logger::
log(string label, string value)
{
  m_out << setw(20) << left << label
    << setw(15) << left << value << endl;
}


void
Logger::
log(string label, unsigned long value)
{
  m_out << setw(20) << left << label
    << setw(15) << left << hex << value
    << setw(15) << left << dec << ulongToLong(value)
    << endl;
}


void
Logger::
log(unsigned long address, unsigned long value)
{
  m_out 
    << setw(20) << left << ""
    << setw(10) << left << hex << address
    << setw(10) << left << hex << value
    << endl;
}


long
Logger::
ulongToLong(unsigned long x)
{
  if (x >> 31)
    x |= (~0xFFFFFFFFul);
  return (long) x;
}
