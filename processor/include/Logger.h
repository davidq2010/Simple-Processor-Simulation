#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief File/console output logger. Offers different logging options for
/// different formats of data.
////////////////////////////////////////////////////////////////////////////////
class Logger
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name LogType enum
    /// @{

    enum LogType {INFO, DEBUG, MEMORY};   ///< 3 kinds of logging data

    static const int NUM_LOG_TYPE = 3;    ///< 3 types in enum

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{

    Logger(std::ostream& _out);

    ~Logger();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @name log methods
    /// @{

    /// @brief Turn a log option on (can have multiple on)
    /// @param _type The specific log option to adjust
    /// @param _can_print Whether to turn _type log option on/off
    void setPrintOption(LogType _type, bool _can_print = true);

    /// @brief log() displays a message if _type has been set to true already
    /// @param _msg Message to log
    /// @param _type If _type has been set to true, then proceed with logging
    void log(std::string _msg, LogType _type = INFO);

    /// @overload Use for logging data that has string label and data
    void log(std::string _label, std::string _value, LogType _type = INFO);

    /// @overload Use for logging data that has ul data
    void log(std::string _label, unsigned long _value, LogType _type = INFO);

    /// @overload Use for logging memory data in the form [address:data]
    void log(unsigned long _label, unsigned long _value, LogType _type = INFO);

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:
    std::ostream& m_out;

    bool m_print_log_type[NUM_LOG_TYPE];  ///< Array displaying which log
                                          ///< settings are on
};

#endif // LOGGER_H_
