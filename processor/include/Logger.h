#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <string>

class Logger
{
  public:
    enum LogType {INFO, DEBUG, MEMORY};

    static const int NUM_LOG_TYPE = 3;

    Logger(std::ostream& _out);

    ~Logger();

    void setPrintOption(LogType _type, bool _can_print = true);

    void log(std::string _msg, LogType _type = INFO);

    void log(std::string _label, std::string _value, LogType _type = INFO);

    void log(std::string _label, unsigned long _value, LogType _type = INFO);

    void log(unsigned long _label, unsigned long _value, LogType _type = INFO);

  private:
    std::ostream& m_out;

    bool m_print_log_type[NUM_LOG_TYPE];
};

#endif // LOGGER_H_
