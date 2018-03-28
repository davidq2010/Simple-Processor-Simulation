#ifndef LOGGER_CPP_
#define LOGGER_CPP_

#include <iostream>
#include "Logger.h"

Logger::
Logger() {}


Logger::
~Logger() {}


void
Logger::
log(std::string msg)
{
	std::cout << msg << std::endl;
}


#endif // LOGGER_CPP_