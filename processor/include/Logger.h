#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <string>


class Logger
{
  public:
    Logger(std::ostream& _out);

    ~Logger();

    void log(std::string msg);

    void log(std::string label, std::string value);

    void log(std::string label, unsigned long value);

    void log(unsigned long label, unsigned long value);

  private:
  	ostream& m_out;

    long ulongToLong(unsigned long x);
};

#endif // LOGGER_H_