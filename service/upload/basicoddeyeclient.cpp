#include "basicoddeyeclient.h"
#include "../logger.h"
#include "networkaccessmanager.h"
// Qt
#include <QJsonObject>
#include <QJsonArray>
#include <QAbstractNetworkCache>
#include <QNetworkCookieJar>

CBasicOddEyeClient::CBasicOddEyeClient(QObject *parent)
    : Base(parent),
      m_nMaxCacheCount( 50000 )
{}

CBasicOddEyeClient::~CBasicOddEyeClient()
{
}

void CBasicOddEyeClient::SetNetworkAccessManager(NetworkAccessManagerSPtr pNetAccessManager)
{
    Q_ASSERT( pNetAccessManager );
    m_pNetworkAccessManager = pNetAccessManager;
}

void CBasicOddEyeClient::SetTSDBUrl(const QUrl &oUrl)
{
    Q_ASSERT( !oUrl.isEmpty() );
    m_oTsdbUrl = oUrl;
}

void CBasicOddEyeClient::SetUuid(const QByteArray &aOddEyeUuid)
{
    Q_ASSERT( !aOddEyeUuid.isEmpty() );
    m_aOddEyeUuid = aOddEyeUuid;
}

void CBasicOddEyeClient::SendSpecialMessage(const QString &sMetricName, const QString &sMessage, EMessageType eType)
{
    if(!IsReady())
        return;

    QJsonArray oRootArray;
    oRootArray.append( CreateErrorMessageJson( sMetricName, sMessage, eType ) );
    SendJsonData( QJsonDocument( oRootArray ));
}

void CBasicOddEyeClient::SetClusterName(const QString &sClusterName)
{
    Q_ASSERT( !sClusterName.isEmpty() );
    m_sClusterName = sClusterName;
}

void CBasicOddEyeClient::SetGroupName(const QString &sGroupName)
{
    Q_ASSERT( !sGroupName.isEmpty() );
    m_sGroupName = sGroupName;
}

void CBasicOddEyeClient::SetHostName(const QString &sHostName)
{
    Q_ASSERT( !sHostName.isEmpty() );
    m_sHostName = sHostName;
}

void CBasicOddEyeClient::SetCacheDir(const QString &sCacheDir)
{
    Q_ASSERT( !sCacheDir.isEmpty() );
    m_sCacheDir = sCacheDir;
}

void CBasicOddEyeClient::SetMaxCacheCount(int nMaxCacheCount)
{
    m_nMaxCacheCount = nMaxCacheCount;
}

void CBasicOddEyeClient::SendJsonData(const QJsonDocument &oJsonData)
{
    // make final POST request data
    QByteArray aMetricJsonData = oJsonData.toJson();
    //
    QByteArray aPOSTRequestData = "UUID=" + m_aOddEyeUuid + "&data=" + aMetricJsonData;

    QNetworkRequest oPOSTRequest( m_oTsdbUrl );
    oPOSTRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    QNetworkReply* pReplay = m_pNetworkAccessManager->Post( oPOSTRequest, aPOSTRequestData );
    pReplay->setProperty( "json_doc", oJsonData );

    connect( pReplay, &QNetworkReply::finished, this,
    [this]
    {
        QNetworkReply* pReplay = static_cast<QNetworkReply*>( sender() );
        if( pReplay->error() == QNetworkReply::NoError )
        {
            qDebug() << pReplay->readAll();
            HandleSendSuccedded( pReplay, pReplay->property("json_doc").toJsonDocument() );
        }
        else
        {
            qDebug() << "finished with error";
            HandleSendError( pReplay, pReplay->property("json_doc").toJsonDocument() );
            // cleare network caches
            //m_pNetworkAccessManager->clearAccessCache();
            //m_pNetworkAccessManager->clearConnectionCache();
        }

        pReplay->deleteLater();

        // reset
        m_pNetworkAccessManager->Reset();
    });

    void (QNetworkReply:: *pError)(QNetworkReply::NetworkError) = &QNetworkReply::error;
    connect( pReplay, pError, this,
    [this]
    {
        QNetworkReply* pReplay = static_cast<QNetworkReply*>( sender() );
        if( !pReplay->isFinished() )
            LOG_ERROR ( "Sending time error: " + pReplay->errorString().toStdString() );
    });
}

bool CBasicOddEyeClient::IsReady() const
{
    if( !m_pNetworkAccessManager )
        return false;

    if( !m_oTsdbUrl.isValid() )
        return false;

    if( m_aOddEyeUuid.isEmpty() )
        return false;

    if( m_sClusterName.isEmpty() || m_sGroupName.isEmpty() || m_sHostName.isEmpty() )
        return false;

    if( m_sCacheDir.isEmpty() )
        return false;

    return true;
}

QString CBasicOddEyeClient::NormailzeAsOEName(QString sName)
{
    sName = sName.toLower();
    QRegExp oExtraCharRegExp( "[^_a-zA-Z0-9]" );
    sName.replace( oExtraCharRegExp, "_" );

    while(sName.contains( "__" ))
        sName.replace("__", "_");

    if( sName.left(1) == "_" )
        sName.remove(0, 1);

    if( sName.right(1) == "_" )
        sName.remove(sName.length() - 1, 1);

    return sName;
}


QJsonObject CBasicOddEyeClient::CreateMetricJson(MetricDataSPtr pSingleMetric)
{
    Q_ASSERT( pSingleMetric );

    if( !pSingleMetric )
        return QJsonObject();

    QJsonObject oMetricJson;
    oMetricJson["metric"] = pSingleMetric->GetName();
    oMetricJson["reaction"] = pSingleMetric->GetReaction();
    oMetricJson["timestamp"] = QString::number( pSingleMetric->GetTime().toUTC().toTime_t() );

    bool bOk = false;
    double dValue = pSingleMetric->GetValue().toDouble(&bOk);
    if( bOk )
        oMetricJson["value"] = dValue;
    else
        oMetricJson["value"] = pSingleMetric->GetValue().toString();

    QJsonObject oTagsJson;
    oTagsJson["cluster"] = m_sClusterName;
    oTagsJson["group"] = m_sGroupName;
    oTagsJson["host"] = m_sHostName;
    oTagsJson["type"] = pSingleMetric->GetMetricType();
    if( !pSingleMetric->GetInstanceType().isEmpty() && !pSingleMetric->GetInstanceName().isEmpty() )
    {
        QString sTagName = NormailzeAsOEName( pSingleMetric->GetInstanceType() );
        QString sTagVal  = NormailzeAsOEName( pSingleMetric->GetInstanceName() );
        oTagsJson[sTagName] = sTagVal;
    }
    // add tags
    oMetricJson["tags"] = oTagsJson;

    oMetricJson["type"] = ToString( pSingleMetric->GetDataType() );

    return oMetricJson;
}


QJsonObject CBasicOddEyeClient::CreateErrorMessageJson(MetricSeverityDescriptorSPtr pDescriptor)
{
    Q_ASSERT( pDescriptor );
    if( !pDescriptor )
        return QJsonObject();


    QJsonObject oMetricJson;
    oMetricJson["metric"] = pDescriptor->GetMetricName();
    oMetricJson["reaction"] = 0;
    oMetricJson["timestamp"] = QString::number( pDescriptor->GetTime().toUTC().toTime_t() );

    QVariant vtValue;
    QString sStatus;
    if( pDescriptor->GetDataSeverity() == EMetricDataSeverity::Normal)
    {
        vtValue = 0;/*pDescriptor->GetValue();*/
        sStatus = "OK";
    }
    else if( pDescriptor->GetDataSeverity() == EMetricDataSeverity::High )
    {
        vtValue = 8;
        sStatus = "WARNING";
    }
    else
    {
        vtValue = 16;
        sStatus = "ERROR";
    }

    oMetricJson["value"] = vtValue.toInt();

    QJsonObject oTagsJson;
    oTagsJson["cluster"] = m_sClusterName;
    oTagsJson["group"] = m_sGroupName;
    oTagsJson["host"] = m_sHostName;
    if( !pDescriptor->GetInstanceType().isEmpty() && !pDescriptor->GetInstanceName().isEmpty() )
    {
        QString sTagName = NormailzeAsOEName( pDescriptor->GetInstanceType() );
        QString sTagVal  = NormailzeAsOEName( pDescriptor->GetInstanceName() );
        oTagsJson[sTagName] = sTagVal;
    }

    // add tags
    oMetricJson["tags"] = oTagsJson;


    oMetricJson["type"] = "Special";
    oMetricJson["status"] = sStatus;
    oMetricJson["message"] = pDescriptor->GetMessage();

    return oMetricJson;
}

QJsonObject CBasicOddEyeClient::CreateErrorMessageJson(const QString &sMessage,
                                                       QString sMetricName,
                                                       EMessageType eMessageType,
                                                       QVariant vtMetricValue)
{
    Q_ASSERT( !sMessage.isEmpty() );

    QJsonObject oMetricJson;
    oMetricJson["metric"] = sMetricName;
    oMetricJson["reaction"] = -2;
    oMetricJson["timestamp"] = QString::number( QDateTime::currentDateTime().toUTC().toTime_t() );

    QJsonObject oTagsJson;
    oTagsJson["cluster"] = m_sClusterName;
    oTagsJson["group"] = m_sGroupName;
    oTagsJson["host"] = m_sHostName;

    // add tags
    oMetricJson["tags"] = oTagsJson;
    oMetricJson["type"] = "Special";

    QString sStatus;
    switch (eMessageType) {
    case EMessageType::Error:
        sStatus = "ERROR";
        vtMetricValue = 16;
        break;
    case EMessageType::Warning:
        sStatus = "WARNING";
        vtMetricValue = 8;
        break;

    default:
        break;
        sStatus = "OK";
        vtMetricValue = 0;
    }

    oMetricJson["value"] = vtMetricValue.toInt();
    oMetricJson["status"] = sStatus;
    oMetricJson["message"] = sMessage;

    return oMetricJson;
}



void CBasicOddEyeClient::HandleSendError(QNetworkReply *pReply, const QJsonDocument &oJsonData)
{
    // nothing to do
    Q_UNUSED(pReply);
    Q_UNUSED(oJsonData);
}



void CBasicOddEyeClient::HandleSendSuccedded(QNetworkReply *pReply, const QJsonDocument &oJsonData)
{
     // nothing to do
    Q_UNUSED(pReply);
    Q_UNUSED(oJsonData);
}
