#include "agentinitializer.h"
#include "performancecounterinfodumper.h"
#include "performancecountersinfoprovider.h"
#include "winperformancemetricschecker.h"

#include <QDir>
#include <QFile>
#include <QTextStream>


CPerformanceCounterInfoDumper::CPerformanceCounterInfoDumper()
{
}

CPerformanceCounterInfoDumper &CPerformanceCounterInfoDumper::Instance()
{
    static CPerformanceCounterInfoDumper oInst;
    return oInst;
}

void CPerformanceCounterInfoDumper::DumpCountersInfo()
{

    PerformanceObjectsInfoList lstCounters = CPerformanceCountersInfoProvider::RetrieveCountersInfo();
    Q_ASSERT(!m_sDumpFileName.isEmpty());

    QFile oFile(m_sDumpFileName);
    if( !oFile.open(QFile::WriteOnly | QFile::Truncate |QIODevice::Append) )
    {
        throw CException("Failed to open file for writing: " + m_sDumpFileName);
    }

    QTextStream out(&oFile);

    QStringList a = m_setFilter.toList();

    for( int i = 0; i < lstCounters.size(); ++i )
    {
        SPerformanceObjectInfo& oObject = lstCounters[i];

        // Filter
        if( m_setFilter.contains( oObject.sName ) )
            continue;

        out << oObject.sName;
        if(!oObject.sDescription.contains( "not available", Qt::CaseInsensitive ))
            out << " - " << oObject.sDescription << "\r\n";
        else
            out << "\r\n";

        // append counter paths

        for( int j = 0; j < oObject.lstCounters.size(); ++j )
        {
            if( oObject.lstInstances.isEmpty() )
            {
                QString sPath = QString("\\%1\\%2").arg(oObject.sName).arg(oObject.lstCounters[j].sPath);
                QString sMetricName = CWinPerformanceMetricsChecker::MakeMetricNameFromCounterPath( sPath );
                out << sMetricName <<" = " << sPath << "," << oObject.lstCounters[j].sDescription << "\r\n";
            }
            else
            {
                for( QString sInstanceName : oObject.lstInstances )
                {

                    QString sPath = QString("\\%1(%3)\\%2")
                            .arg(oObject.sName,
                                 oObject.lstCounters[j].sPath,
                                 sInstanceName)
                            ;
                    QString sMetricName = CWinPerformanceMetricsChecker::MakeMetricNameFromCounterPath( sPath );
                    out << sMetricName <<" = " << sPath << "," << oObject.lstCounters[j].sDescription << "\r\n";
                }
            }
        }
        out << "\r\n";
    }
}

void CPerformanceCounterInfoDumper::SetDumpDirPath(const QString &sPath)
{
    Q_ASSERT( !sPath.isEmpty() );
    QDir oDir( sPath );
    if( !oDir.exists() )
    {
        oDir.mkpath( sPath );
    }

    m_sDumpFileName = oDir.absoluteFilePath( "available_performance_counters.csv" );
}

QString CPerformanceCounterInfoDumper::GetDumpFilePath() const
{
    return m_sDumpFileName;
}

void CPerformanceCounterInfoDumper::AddtoFilter(const QString &sFilter)
{
    if( sFilter.isEmpty() )
        return;
    m_setFilter.insert(sFilter);
}

bool CPerformanceCounterInfoDumper::ContainesOneOf(const QString &sSourceString, const QStringList &lstLexems)
{
    for( QString const& sLex : lstLexems )
        if( sSourceString.contains(sLex, Qt::CaseInsensitive) )
            return true;
    return false;
}


