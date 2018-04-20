#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <string>


class Logger
{
  public:
    Logger(std::ostream& _out);

    ~Logger();

    void log(std::string _msg);

    void log(std::string _label, std::string _value);

    void log(std::string _label, unsigned long _value);

    void log(unsigned long _label, unsigned long _value);

  private:
    std::ostream& m_out;

    long ulongToLong(unsigned long _x);
};

#endif // LOGGER_H_
