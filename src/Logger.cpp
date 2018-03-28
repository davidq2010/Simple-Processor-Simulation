#ifndef LOGGER_CPP_
#define LOGGER_CPP_

#include <iostream>
#include <iomanip>
#include "Logger.h"

using namespace std;

Logger::
Logger() {}


Logger::
~Logger() {}


void
Logger::
log(string msg)
{
	cout << msg << endl;
}


void
Logger::
log(string label, string value)
{
	cout << setw(20) << left << label
		<< setw(20) << left << value << endl;
}


void
Logger::
log(string label, unsigned long value)
{
	cout << setw(20) << left << label
		<< setw(20) << left << hex << value
		<< setw(20) << left << dec << ulongToLong(value)
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

#endif // LOGGER_CPP_
