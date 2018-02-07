#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iomanip>
#include <QDate>
#include <QFile>
#include <QTextStream>

class Logger
{
public:
    static Logger& getInstance();

    void error( const std::string &prefix, std::string msg );
    void warning( const std::string &prefix, std::string msg );
    void info( const std::string &prefix, std::string msg );
    void debug( const std::string &prefix, std::string msg );
    

private:
    enum class LogType
    {
        Error,
        Warning,
        Info,
        Debug
    };

    Logger();
    Logger( const Logger& )            = delete; // Copy construct
    Logger( Logger&& )                 = delete; // Move construct
    Logger& operator=( const Logger& ) = delete; // Copy assign
    Logger& operator=( Logger && )     = delete; // Move assign

    template<LogType type>
    void _log(const std::string &prefix, const std::string&msg );

    void _prepare_logs_file();

    // members
    QFile		_logs_file;
    QTextStream _logs_stream;
    QDate		_logs_file_open_date;
};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __PREFIX__ std::string( std::string( __FILENAME__ ) + "(" + std::string( __FUNCTION__ ) + ")" )

#define LOG_VERBOSE( __MSG__ ) { }
#define LOG_DEBUG( __MSG__ ) { Logger::getInstance().debug( std::string( __PREFIX__ ), std::string( __MSG__ ) ) ; }
#define LOG_INFO( __MSG__ ) { Logger::getInstance().info( /*std::string( __PREFIX__ )*/"", std::string( __MSG__ ) ) ; }
#define LOG_WARNING( __MSG__ ) { Logger::getInstance().warning( std::string( __PREFIX__ ), std::string( __MSG__ ) ); }
#define LOG_ERROR( __MSG__ ) { Logger::getInstance().error( std::string( __PREFIX__ ), std::string( __MSG__ ) ); }

#endif // LOGGER_H
