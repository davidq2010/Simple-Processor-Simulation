#include <iostream>
#include <iomanip>
#include "Logger.h"

using namespace std;

Logger::
Logger(ostream& _out) : m_out(_out) 
{
  for (int i = 0; i < NUM_LOG_TYPE; m_print_log_type[i++] = false);
  m_print_log_type[INFO] = true;
}


Logger::
~Logger() {}


void
Logger::
setPrintOption(LogType _type, bool _can_print)
{
  m_print_log_type[_type] = _can_print;
}


void
Logger::
log(string _msg, LogType _type)
{
  if (m_print_log_type[_type])
    m_out << _msg << endl;
}


void
Logger::
log(string _label, string _value, LogType _type)
{
  if (m_print_log_type[_type])
    m_out 
    << setw(20) << left << _label
    << setw(15) << left << _value << endl;
}


void
Logger::
log(string _label, unsigned long _value, LogType _type)
{
  if (m_print_log_type[_type])
    m_out << setw(20) << left << _label
    << setw(15) << left << hex << _value
    << endl;
}


void
Logger::
log(unsigned long _address, unsigned long _value, LogType _type)
{
  if (m_print_log_type[_type])
    m_out
    << setw(20) << left << ""
    << setw(10) << left << hex << _address
    << setw(10) << left << hex << _value
    << endl;
}


/*long
Logger::
ulongToLong(unsigned long _x)
{
  if (_x >> 31)
    _x |= (~0xFFFFFFFFul);
  return (long) _x;
}*/
