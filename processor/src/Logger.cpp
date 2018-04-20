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
log(string _msg)
{
  m_out << _msg << endl;
}


void
Logger::
log(string _label, string _value)
{
  m_out << setw(20) << left << _label
    << setw(15) << left << _value << endl;
}


void
Logger::
log(string _label, unsigned long _value)
{
  m_out << setw(20) << left << _label
    << setw(15) << left << hex << _value
    << setw(15) << left << dec << ulongToLong(_value)
    << endl;
}


void
Logger::
log(unsigned long _address, unsigned long _value)
{
  m_out
    << setw(20) << left << ""
    << setw(10) << left << hex << _address
    << setw(10) << left << hex << _value
    << endl;
}


long
Logger::
ulongToLong(unsigned long _x)
{
  if (_x >> 31)
    _x |= (~0xFFFFFFFFul);
  return (long) _x;
}
