#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

class Logger
{
	public:
		Logger();

		~Logger();

		void log(std::string msg);

		void log(std::string label, std::string value);

		void log(std::string label, unsigned long value);

	private:

		long ulongToLong(unsigned long x);
};


#endif // LOGGER_H_
