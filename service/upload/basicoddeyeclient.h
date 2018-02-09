#ifndef BASICODDEYECLIENT_H
#define BASICODDEYECLIENT_H

#include "../metricdata.h"
#include <QJsonDocument>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <memory>

using NetworkAccessManagerSPtr = std::shared_ptr<QNetworkAccessManager>;

////////////////////////////////////////////////////////////////////////////////////
///
/// class CBasicOddEyeClient
///
///  Base class for OddEye clients
class CBasicOddEyeClient : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    explicit CBasicOddEyeClient(QObject *parent = nullptr);

public:
    void SetNetworkAccessManager( NetworkAccessManagerSPtr pNetAccessManager );
    void SetTSDBUrl( QUrl const& oUrl );
    void SetUuid( QByteArray const& aOddEyeUuid );

    void SetClusterName( QString const& sClusterName );
    void SetGroupName( QString const& sGroupName );
    void SetHostName( QString const& sHostName );
    void SetCacheDir( QString const& sCacheDir );
    void SetMaxCacheCount( int nMaxCacheCount );

    void SendJsonData( QJsonDocument const& oJsonData );

    static QString NormailzeAsOEName( QString sName );

protected:
    virtual void HandleSendSuccedded( QNetworkReply* pReply, QJsonDocument const& oJsonData );
    virtual void HandleSendError(     QNetworkReply* pReply, QJsonDocument const& oJsonData) ;

    QJsonObject CreateMetricJson( MetricDataSPtr pSingleMetric );
    QJsonObject CreateErrorMessageJson( QString const& sMessage, MetricDataSPtr pRelatedMetric );
    QJsonObject CreateErrorMessageJson( QString const& sMessage, QString sMetricName, QVariant vtMetricValue = QVariant(0) );

signals:

public slots:

protected:
    // Content
    NetworkAccessManagerSPtr m_pNetworkAccessManager;
    QUrl m_oTsdbUrl;
    QByteArray m_aOddEyeUuid;

    QString m_sClusterName;
    QString m_sGroupName;
    QString m_sHostName;
    QString m_sCacheDir;
    int     m_nMaxCacheCount;
};
////////////////////////////////////////////////////////////////////////////////////


#endif // BASICODDEYECLIENT_H
