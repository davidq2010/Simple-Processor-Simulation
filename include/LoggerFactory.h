#ifndef LOGGER_FACTORY_H_
#define LOGGER_FACTORY_H_

#include "Logger.h"

class LoggerFactory
{
	public:
		static Logger getLogger();

	private:
		static Logger logger;
};


#endif // LOGGER_FACTORY_H_
