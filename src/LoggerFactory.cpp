#ifndef LOGGER_FACTORY_CPP_
#define LOGGER_FACTORY_CPP_


Logger LoggerFactory::logger;

Logger
LoggerFactory::
getLogger()
{
	return logger;
}


#endif // LOGGER_FACTORY_CPP_