#ifndef ODDEYECLIENT_H
#define ODDEYECLIENT_H

#include "basicoddeyeclient.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// class COddEyeClient
/// Main OddEye client which provides metric data transmission to the backend and data cacheing
class COddEyeClient : public CBasicOddEyeClient
{
    Q_OBJECT
    using Base = CBasicOddEyeClient;

public:
    explicit COddEyeClient(QObject *parent = nullptr);

public:
    void SendMetrics( MetricDataList const& lstMetrics );

protected:
    void HandleSendSuccedded( QNetworkReply* pReply, QJsonDocument const& oJsonData ) override;
    void HandleSendError(     QNetworkReply* pReply, QJsonDocument const& oJsonData) override;

    void ConvertMetricsToJSON( MetricDataList const& lstMetrics,
                               QJsonDocument& oNormalMetricsJson,
                               QJsonDocument& oSpecialMetricsJson);
    bool CacheJsonData( QJsonDocument const& oJsonDoc );
    bool IsValid( QJsonDocument const& oJsonDec ) const;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // ODDEYECLIENT_H
