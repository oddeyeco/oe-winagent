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

Logger::~Logger()
{
    ConfMgr.GetRegistrySettings().setValue("logs_file_open_datetime", _logs_file_open_datetime);
}

Logger::Logger()
    : _nLogRotateSeconds(3600),
      _nBackupFileCount(24),
      _bDebugLoggingEnabled(false)
{
    if(  !ConfMgr.GetRegistrySettings().contains( "logs_file_open_datetime" ) )
    {
        ConfMgr.GetRegistrySettings().setValue("logs_file_open_datetime", QDateTime::currentDateTime());
    }

    _logs_file_open_datetime = ConfMgr.GetRegistrySettings().value( "logs_file_open_datetime" ).toDateTime();
}

void Logger::error(const std::string &prefix, std::string msg)
{
    _log<LogType::Error>(prefix,     "Error: " + msg );
}

void Logger::info(const std::string &prefix, std::string msg)
{
    _log<LogType::Info>(prefix,      "Info:  " + msg );
}

void Logger::debug(const std::string &prefix, std::string msg)
{
    if( _bDebugLoggingEnabled )
        _log<LogType::Debug>(prefix, "Debug: " + msg );
}

void Logger::setLogRotateSeconds(qint64 nSeconds)
{
    _nLogRotateSeconds = nSeconds;
}

void Logger::warning(const std::string &prefix, std::string msg)
{
    _log<LogType::Warning>(prefix,   "Warning: " + msg );
}


void Logger::setBackupFileCount(int nCount)
{
    _nBackupFileCount = nCount;
}

void Logger::setLogsFolderPath(const QString &sFolderPath)
{
    Q_ASSERT( !sFolderPath.isEmpty() );
    _logs_folder_path = sFolderPath;


    QDir logs_dir(_logs_folder_path);

    if (! logs_dir.exists())
    {
        logs_dir.mkpath(_logs_folder_path);
    }

    _init_log_file(_logs_file_open_datetime);
    /*
    QDateTime current_datetime = QDateTime::currentDateTime();
    qint64 nActualSecondsLeft = _logs_file_open_datetime.secsTo( current_datetime );
    if ( nActualSecondsLeft >= _nLogRotateSeconds )
    {
        _init_log_file( current_datetime );
    }
    else
    {

    }*/


}

void Logger::SetDebugLoggingEnabled(bool bEnabled)
{
    _bDebugLoggingEnabled = bEnabled;
}

QString Logger::GetLogDirPath() const
{
    if( _logs_folder_path.isEmpty() )
        return QString();
    QDir logs_dir(_logs_folder_path);
    return logs_dir.absolutePath();
}

template<Logger::LogType type>
void Logger::_log(const std::string& prefix, const std::string& msg)
{
    if( !_prepare_logs_file() )
        return;

    std::string log = "[" + currentTime() + "] ";
    std::stringstream ss;
    ss << log << std::left << std::setfill('-')
       << (prefix.empty()? std::setw( 0 ): std::setw( 70 ) )<< prefix
       << std::setw( 0 ) << msg << std::endl;

    QMutexLocker oLocker(&m_oMutex);
    _logs_stream << ss.str().c_str();
    _logs_stream.flush();

    log += ( prefix + " = " + msg);
    qDebug() << QString::fromStdString( log );
}

bool Logger::_prepare_logs_file()
{
    if( _nLogRotateSeconds <= 0 || _nBackupFileCount <= 0 )
        // logging disabled
        return false;

    const auto current_datetime = QDateTime::currentDateTime();
    qint64 nActualSecondsLeft = _logs_file_open_datetime.secsTo( current_datetime );

    if ( nActualSecondsLeft >= _nLogRotateSeconds )
    {
        _init_log_file( current_datetime );
    }

    return true;
}

void Logger::_init_log_file(const QDateTime &oLogFileDateTime)
{
    const auto filename = oLogFileDateTime.toString("dd-MM-yyyy_HH-mm-ss") + ".txt";
    if (_logs_file.isOpen())
    {
        _logs_file.close();
    }

    _logs_file.setFileName(_logs_folder_path + QDir::separator() + filename);

    if (_logs_file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append))
    {
        _logs_file_open_datetime = oLogFileDateTime;
        _logs_stream.setDevice(& _logs_file);
    }


    // check backuped file count
    QDir oLogsDir( _logs_folder_path );
    QFileInfoList lstLogFileInfos = oLogsDir.entryInfoList( QStringList() << "*.txt" );
    if( lstLogFileInfos.size() > _nBackupFileCount )
    {
        // remove oldest file
        QFileInfoList::iterator oIt = std::min_element( lstLogFileInfos.begin(), lstLogFileInfos.end(),
                                                        [](QFileInfo const& a, QFileInfo const& b ) { return a.created() < b.created(); } );
        QString sOldestFilePath = (*oIt).absoluteFilePath();
        QFile oOldestFile( sOldestFilePath );
        bool bOK = oOldestFile.remove();
        Q_ASSERT(bOK);

    }
}
