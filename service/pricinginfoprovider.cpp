#include "pricinginfoprovider.h"
#include "commonexceptions.h"
#include "./upload/sendcontroller.h"
#include "logger.h"

#include <QEventLoop>
#include <QTimer>

CPricingInfoProvider::CPricingInfoProvider(QObject *parent) :
    QObject(parent),
    m_nMetricCount(0),
    m_nUpdateSec(0),
    m_dLastCalculatedPrice(-1)
{
}

void CPricingInfoProvider::SetMetricsCount(int nMetricCount)
{
    m_nMetricCount = nMetricCount;
}

void CPricingInfoProvider::SetUpdatesIntervalSec(int nUpdateSec)
{
    m_nUpdateSec = nUpdateSec;
}

double CPricingInfoProvider::CalculatePrice()
{
    QJsonObject oPriceJson = RequestPriceingInfo();

    if( !oPriceJson.contains("mp") || !oPriceJson.contains("pf") || !oPriceJson.contains("pp"))
        throw CPriceInfoFetchFailedException("Invalid info provider");

    double u_p = oPriceJson["mp"].toDouble();
    double p_f = oPriceJson["pf"].toDouble();
    double p_p = oPriceJson["pp"].toDouble();

    if(m_nUpdateSec <= 0)
        throw CPriceInfoFetchFailedException("Update seconds not set");

    double dRunsMonth = 60 / m_nUpdateSec * 60 * 24 * 30;

    double o = (m_nMetricCount * dRunsMonth * u_p);
    double deq = o + o * p_p / 100 + p_f;

    m_dLastCalculatedPrice = deq;
    return deq;
}

double CPricingInfoProvider::GetLastCalculatedPrice() const
{
    return m_dLastCalculatedPrice;
}

QJsonObject CPricingInfoProvider::RequestPriceingInfo()
{
    NetworkAccessManagerSPtr pNetworkManager = CSendController::Instance().GetNetworkAccessManager().lock();
    Q_ASSERT(pNetworkManager);
    if( !pNetworkManager )
    {
        LOG_ERROR("Internal error: Network Access Manager is NULL");
        throw CPriceInfoFetchFailedException("Network Access Manager is NULL");
    }

    QUrl oUrl = QUrl("https://app.oddeye.co/OddeyeCoconut/getpayinfo");
    Q_ASSERT( oUrl.isValid() );
    auto pReply = pNetworkManager->Get(QNetworkRequest( oUrl ) );

    QTimer oTimeoutTimer;
    oTimeoutTimer.setSingleShot(true);

    QEventLoop loop;
    connect(&oTimeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
    // start timeout timer
    oTimeoutTimer.start(5000);
    // start event loop
    loop.exec();

    if(oTimeoutTimer.isActive())
    {
        oTimeoutTimer.stop();

        // Handle reply
        if( pReply->error() == QNetworkReply::NoError )
        {
            QByteArray aReply = pReply->readAll();
            QJsonObject oJsonObj = QJsonDocument::fromJson( aReply ).object();
            qDebug() << aReply;
            return oJsonObj;
        }
        else
        {
            LOG_ERROR( "Priceing info check failed: " + pReply->errorString().toStdString() );
            throw CPriceInfoFetchFailedException(pReply->errorString());
        }
    }
    else
    {
       // timeout
       disconnect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
       pReply->abort();
       LOG_ERROR( "Priceing info checking timeout!" );
       throw CPriceInfoFetchFailedException("Priceing info checking timeout!");
    }
}

