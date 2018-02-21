#include "oddeyeselfcheck.h"
#include "basicmetricchecker.h"
#include "pinger.h"
#include "../upload/sendcontroller.h"
#include "../configurationmanager.h"
#include "../commonexceptions.h"

#include <QElapsedTimer>
#include <QEventLoop>
#include <QTimer>

class COEHostAliveMetricChecker : public QObject, public IMetricChecker
{
    Q_OBJECT

public:
    COEHostAliveMetricChecker(int nTimeout = 2000)
        : m_nTimeout( nTimeout )
    {}

    // IMetricChecker interface
public:
    MetricDataSPtr CheckMetric()
    {   
        Q_ASSERT( m_nTimeout > 0 );
        qint64 nDuration = MeasureResponseTime( m_nTimeout );
        MetricDataSPtr pMetric = std::make_shared<CMetricData>("host_alive",
                                             nDuration,
                                             EMetricDataType::None,
                                             QDateTime::currentDateTime(),
                                             "health");

        QString sMsg = "{DURATION} without HearBeats from host";
        pMetric->SetSeverityDescriptor( "HeartBeat", EMetricDataSeverity::Normal, 0, sMsg );

        return pMetric;
    }

    qint64 MeasureResponseTime( int nTimeoutMsecs )
    {
        NetworkAccessManagerSPtr pNetworkManager = CSendController::Instance().GetNetworkAccessManager().lock();
        Q_ASSERT(pNetworkManager);
        if( !pNetworkManager )
        {
            throw CUnableCheckMetricException( "host_alive", "Network Access Manager is NULL" );
            LOG_ERROR("Internal error: Network Access Manager is NULL")
        }

        // Start timer
        QElapsedTimer oTimer;
        oTimer.start();

        QUrl oUrl = QUrl("https://api.oddeye.co/ok.txt");
        Q_ASSERT( oUrl.isValid() );
        auto pReply = pNetworkManager->Get(QNetworkRequest( oUrl) );

        QTimer oTimeoutTimer;
        oTimeoutTimer.setSingleShot(true);

        QEventLoop loop;
        connect(&oTimeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
        connect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
        // start timeout timer
        oTimeoutTimer.start(nTimeoutMsecs);
        // start event loop
        loop.exec();

        if(oTimeoutTimer.isActive())
        {
            oTimeoutTimer.stop();

            // Handle reply
            if( pReply->error() == QNetworkReply::NoError )
            {
                QByteArray aReply = pReply->readAll();
                qDebug() << aReply;
            }
            else
            {
                throw CUnableCheckMetricException( "host_alive", pReply->errorString());
            }
        }
        else
        {
           // timeout
           disconnect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
           pReply->abort();

           throw CUnableCheckMetricException( "host_alive", "Time out!");
        }

        qint64 nElapsedTime = oTimer.elapsed();
        return nElapsedTime;
    }

private:
    int    m_nTimeout;
};

#include "oddeyeselfcheck.moc"

//
//  class OddeyeSelfCheck
//
OddeyeSelfCheck::OddeyeSelfCheck( QObject* pParent )
    : Base( pParent )
{
}

void OddeyeSelfCheck::Initialize()
{
//    double dConfHighVal   = -1;
//    double dConfSevereVal = -1;

//    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
//    if( bStaticAlertingEnabled )
//    {
//        dConfHighVal   = ConfigSection().Value<double>("high", -1);
//        dConfSevereVal = ConfigSection().Value<double>("severe", -1);
//    }

//    BasicMetricCheckerSPtr pChecker = std::make_shared<CBasicMetricChecker>("oddeye_self_check_time",
//                                                                            EMetricDataType::Counter,
//                                                                            "OddEye_Specific", 0,
//                                                                            dConfHighVal,
//                                                                            dConfSevereVal );
//    pChecker->SetValueCheckerFunction(
//    [this]()
//    {
//        Q_ASSERT(!m_sOddEyeAddress.isEmpty());
//        double dPingTime = CPinger::RoundTripTime( m_sOddEyeAddress );
//        return dPingTime;
//    } );

    int nTimeoutMsec = ConfigSection().Value<double>("timeout_seconds", 5) * 1000;
    if( nTimeoutMsec <= 0 )
    {
        throw CInvalidConfigValueException( ConfigSection().Value<QString>("timeout_seconds", QString("")) );
    }

    Base::AddMetricChecker( std::make_shared<COEHostAliveMetricChecker>(nTimeoutMsec) );
}


