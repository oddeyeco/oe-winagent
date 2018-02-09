#include "scriptsmetricschecker.h"
#include "../logger.h"

// Qt
#include <QFileInfo>
#include <QProcess>

CScriptsMetricsChecker::CScriptsMetricsChecker(QObject *pParent)
    : Base( pParent )
{
    m_pProcess = std::make_unique<QProcess>();
    connect( m_pProcess.get(), &QProcess::readyReadStandardError, this,
    [this]()
    {
        QByteArray aError = m_pProcess->readAllStandardOutput();

        QString sFileName;
        if( m_pProcess->arguments().size() >= 2 )
        {
            QString sFilePathArg = m_pProcess->arguments().at(1);
            sFileName = QFileInfo(sFilePathArg).baseName();
        }
        LOG_ERROR( QString("Script execution error: %1 : File %2").arg(aError, sFileName).toStdString() );
    });
}

CScriptsMetricsChecker::~CScriptsMetricsChecker()
{}

MetricDataList CScriptsMetricsChecker::CheckMetrics()
{
    MetricDataList lstResults;

    QStringList lstScriptFiles = ConfigSection().Value<QStringList>("scripts_enabled", QStringList());
    for( auto& sScriptFile : lstScriptFiles )
    {
        lstResults.append( GetScriptFileResults( sScriptFile ) );
    }

    return lstResults;
}

MetricDataList CScriptsMetricsChecker::GetScriptFileResults(const QString &sSrcoptFilePath)
{
    MetricDataList lstResltMetricsData;

    auto sCommand = QString("cmd.exe");
    auto lstArguments = QStringList{ QString("/C"), sSrcoptFilePath };

    Q_ASSERT( m_pProcess->state() == QProcess::NotRunning );

    m_pProcess->start(sCommand, lstArguments);
    m_pProcess->waitForFinished(-1);

    if( m_pProcess->exitStatus() == QProcess::NormalExit )
    {
        QString sResult = m_pProcess->readAllStandardOutput();
        QStringList lstResultLines = sResult.split( "\r\n", QString::SkipEmptyParts );

        for( QString& sResultLine : lstResultLines )
        {
            QStringList lstMetricData = sResultLine.split( " ", QString::SkipEmptyParts );
            if( lstMetricData.size() < 2 )
            {
                // Invalid result
                LOG_ERROR( "Invalid script result. Insufficient number of output data" );
                continue;
            }

            // output count is 2+
            // create metric data object
            MetricDataSPtr pMetricData = std::make_shared<CMetricData>();
            pMetricData->SetName( lstMetricData[0] );
            pMetricData->SetValue( QVariant( lstMetricData[1] ) );
            pMetricData->SetTime( QDateTime::currentDateTime() );

            // continue commiting outputs
            if( lstMetricData.size() >= 3 )
            {
                pMetricData->SetType( lstMetricData[2] );
                if( lstMetricData.size() >= 4 )
                {
                    pMetricData->SetDataType( lstMetricData[3] );
                }
            }

            lstResltMetricsData.append( pMetricData );
        }
    }

    return lstResltMetricsData;
}

