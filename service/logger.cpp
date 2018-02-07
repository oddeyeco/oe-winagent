#include "logger.h"

#include <iostream>

#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time

#include <configurationmanager.h>
#include <QDir>
#include <QString>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QTextStream>

std::string currentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t( now );
    
    std::stringstream ss;
    ss << std::put_time( std::localtime( &in_time_t ), "%Y-%m-%d %X" );
    return ss.str();
}

Logger& Logger::getInstance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    QString full_logs_folder_path = ConfMgr.GetMainConfiguration().Value<QString>( "SelfConfig/log_dir" );
    // TODO: log_dir vs log_file
    QDir logs_dir(full_logs_folder_path);

    if (! logs_dir.exists())
    {
        logs_dir.mkpath(full_logs_folder_path);
    }
}

void Logger::error(const std::string &prefix, std::string msg)
{
    _log<LogType::Error>(prefix, "Error: " + msg );
}

void Logger::warning(const std::string &prefix, std::string msg)
{
    _log<LogType::Warning>(prefix, "Warning: " + msg );
}

void Logger::info(const std::string &prefix, std::string msg)
{
    _log<LogType::Info>(prefix, "Info: " + msg );
}

void Logger::debug(const std::string &prefix, std::string msg)
{
    _log<LogType::Debug>(prefix, "Debug: " + msg );
}

template<Logger::LogType type>
void Logger::_log(const std::string& prefix, const std::string& msg)
{
    _prepare_logs_file();

    std::string log = "[" + currentTime() + "] ";
    std::stringstream ss;
    ss << log << std::left << std::setfill('-') << std::setw( 70 )
           << prefix << std::setw( 0 ) << msg << std::endl;

    _logs_stream << ss.str().c_str();
    _logs_stream.flush();

    log += ( prefix + " = " + msg);
    qDebug() << QString::fromStdString( log );
}

void Logger::_prepare_logs_file()
{
    const auto current_date = QDate::currentDate();
    if (_logs_file_open_date != current_date)
    {
        const auto filename = current_date.toString(Qt::ISODate) + ".txt";
        if (_logs_file.isOpen())
        {
            _logs_file.close();
        }

        _logs_file.setFileName(ConfMgr.GetMainConfiguration().Value<QString>( "SelfConfig/log_dir" ) + QDir::separator() + filename);
        if (_logs_file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append))
        {
            _logs_file_open_date = current_date;
            _logs_stream.setDevice(& _logs_file);
        }
    }
}
