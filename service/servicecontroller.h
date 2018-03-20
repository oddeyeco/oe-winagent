#ifndef CSERVICECONTROLLER_H
#define CSERVICECONTROLLER_H

#include <QObject>
#include "engine.h"
#include "pricinginfoprovider.h"
#include "upload/sendcontroller.h"

using EngineUPtr = std::unique_ptr<CEngine>;
//using SendControllerUPtr = std::unique_ptr<CSendController>;

///////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Service controller singltone class
///
class CServiceController : public QObject
{
    Q_OBJECT
    using Base = QObject;

private:
    explicit CServiceController(QObject* pParent = nullptr);

public:
    static CServiceController& Instance();

public:
    //
    //  Main Interface
    //
    void Start();
    void Stop();
    void DumpPerformanceCountersInfo();

    bool IsStarted() const;
    double GetPriceInfo();

signals:
    void sigStarted();
    void sigStopped();
    void sigError( QString const& sErrorMessage );

private:
    //
    //  Content
    //
    EngineUPtr         m_pEngine;
    //SendControllerUPtr m_pSendController;
    CPricingInfoProvider m_oPriceInfoFetcher;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // CSERVICECONTROLLER_H
