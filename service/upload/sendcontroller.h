#ifndef SENDCONTROLLER_H
#define SENDCONTROLLER_H

#include "../metricdata.h"
#include "oddeyeclient.h"

#include "networkaccessmanager.h"
#include <QThread>
#include <atomic>
#include <memory>

using NetworkAccessManagerSPtr = std::shared_ptr<CNetworkAccessManager>;
using NetworkAccessManagerWPtr = std::weak_ptr<CNetworkAccessManager>;

// Forward declarations
class COddEyeCacheUploader;

//////////////////////////////////////////////////////////////////////////////////////////
///
/// class CSendController
/// Controles metric data transmission to the TSDB Service
class CSendController : public QObject
{
    Q_OBJECT
    using Base = QObject;
    using OddEyeClientUPtr = std::unique_ptr<COddEyeClient>;
    using OddEyeCacheUploaderUPtr = std::unique_ptr<COddEyeCacheUploader>;

private:
    CSendController();
public:
    static CSendController& Instance();
    ~CSendController();

public slots:
    // Main Interface
    void SendMetricsData( MetricDataList const& lstMetrics );
    void SendSeverityMessage( MetricSeverityDescriptorSPtr pSeverityDescriptor );
    void SendSeverityMessage( QString const& sMetricName,
                              EMetricDataSeverity eSeverity,
                              QString const& sMessage,
                              double dAlertDurationHint = 0,
                              QString const& sInstanceType = QString(),
                              QString const& sInstanceName = QString() );

    NetworkAccessManagerWPtr GetNetworkAccessManager();

    void TurnOn();
    void TurnOff();
    bool IsReady() const;

signals:
    void sigStartCacheUploading();
    void sigStopCacheUploading();

private:
    // Helpers
    void SetupOEClients();

private:
    // Contents
    NetworkAccessManagerSPtr m_pNetworkManager;
    OddEyeClientUPtr         m_pOEClient;
    QThread*                 m_pCacheUploaderThread;
    OddEyeCacheUploaderUPtr  m_pOECacheUploader;
    std::atomic<bool>        m_bIsReady;
};

#define SendController CSendController::Instance()


//using SendControllerSPtr = std::shared_ptr<CSendController>;
//////////////////////////////////////////////////////////////////////////////////////////

#endif // SENDCONTROLLER_H
