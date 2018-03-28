#ifndef LOGGER_FACTORY_H_
#define LOGGER_FACTORY_H_

#include "Logger.h"

class LoggerFactory
{
	public:
		static void getLogger() { return logger }

	private:
		static Logger logger;
}


#endif // LOGGER_FACTORY_H_