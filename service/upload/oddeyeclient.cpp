#include "oddeyeclient.h"

#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

#include "../logger.h"


COddEyeClient::COddEyeClient(QObject *parent)
    : Base(parent)
{}

void COddEyeClient::SendMetrics(const MetricDataList &lstMetrics)
{
    if( !IsReady() )
    {
        LOG_WARNING( "Unable to send metrics: OEClient is not ready" );
        Q_ASSERT(false);
        return;
    }
    auto oJsonData = ConvertMetricsToJSON( lstMetrics );
    Base::SendJsonData( oJsonData );
}

QJsonDocument COddEyeClient::ConvertMetricsToJSON(const MetricDataList &lstMetrics)
{
    QJsonArray oRootArray;
    for( MetricDataSPtr pCurrentMetric : lstMetrics)
    {
        if( !pCurrentMetric )
            continue;

         oRootArray.append( Base::CreateMetricJson( pCurrentMetric ) );

         // Check metric value severity
         if( pCurrentMetric->HasSeverityDescriptor() )
         {
             // setnd error message
             oRootArray.append( Base::CreateErrorMessageJson( pCurrentMetric->GetSeverityDescriptor()) );
         }
    }

    return QJsonDocument( oRootArray );
}

void COddEyeClient::HandleSendSuccedded(QNetworkReply *pReply, const QJsonDocument &oJsonData)
{
    LOG_INFO( "Metrics successfully sent: " + pReply->readAll() );
    Q_UNUSED( oJsonData );
}

void COddEyeClient::HandleSendError(QNetworkReply *pReply, const QJsonDocument &oJsonData)
{
    Q_ASSERT( pReply );
    QString sError = pReply->errorString();
    LOG_ERROR( sError.toStdString() );

    // store JSON data in cache
    CacheJsonData( oJsonData );
}

bool COddEyeClient::CacheJsonData(const QJsonDocument &oJsonDoc)
{
    if( oJsonDoc.isEmpty() )
    {
        Q_ASSERT(false);
        return false;
    }

    if( m_nMaxCacheCount <= 0 )
        // caching disabled
        return false;

    QDir oCacheDir(m_sCacheDir);
    if( !oCacheDir.exists() )
    {
        LOG_ERROR( "Failed to cache metric data. tmpdir not found!" );
        // TODO: emit appropriate error signal
    }

    // check max cache
    oCacheDir.setNameFilters(QStringList() << "*.json");
    int nCurrentJsonFileCount = oCacheDir.count();

    if( nCurrentJsonFileCount >= m_nMaxCacheCount )
    {
        LOG_INFO( "The maximum number of caches reached. Crrent metric data will be lost" );
        return false;
    }

    QString sJsonFileName = QDateTime::currentDateTime().toString("ddMMyy_HHmmsszzz") + ".json";
    QString sJsonFilePath = oCacheDir.absoluteFilePath( sJsonFileName );

    //
    //  Save JSON data
    //
    QFile oJsonFile(sJsonFilePath);

    if (!oJsonFile.open(QIODevice::WriteOnly))
    {
        LOG_ERROR("Couldn't open json file to save!");
        return false;
    }

    QByteArray aJsonData = oJsonDoc.toJson();
    qint64 nBytesWritten = oJsonFile.write(aJsonData);
    if( nBytesWritten < aJsonData.size() )
        oJsonFile.waitForBytesWritten(100);
    oJsonFile.close();

    LOG_INFO( "Metric data was cached." );
    return true;
}

