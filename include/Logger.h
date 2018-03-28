#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

class Logger
{
	public:
		Logger();

		~Logger();

		void log(std::string msg);
}


#endif // LOGGER_H_