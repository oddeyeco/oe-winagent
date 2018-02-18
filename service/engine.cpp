#include "engine.h"
#include <QDebug>
#include <QElapsedTimer>
#include <iostream>

CEngine::CEngine(QObject *pParent)
    : Base(pParent),
      m_pTimer( nullptr )
{
    // setup windows performance data provider
    m_pDataProvider = std::make_shared<CWinPerformanceDataProvider>();

    // setup timer
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    m_pTimer->setSingleShot(false);
    connect(m_pTimer, &QTimer::timeout, this, &CEngine::onTimerTik);
}

void CEngine::Start()
{
    if( m_setCheckers.empty() )
    {
        LOG_INFO( "No metric checkers" );
        return;
    }
    QString sSep( 80, '-' );
    LOG_INFO( sSep );
    LOG_INFO( "Engine started!" );
    LOG_INFO( sSep );

    m_pDataProvider->UpdateCounters();
    onTimerTik();
    m_pTimer->start();
    // async start
    //QTimer::singleShot(0, m_pTimer, SLOT(start()) );
}

void CEngine::Stop()
{
    // async stop
    //QTimer::singleShot(0, m_pTimer, SLOT(stop()));
    m_pTimer->stop();
    LOG_INFO( "Engine stopped!" );
}

void CEngine::AddChecker(IMetricsCategoryCheckerSPtr pChecker)
{
    Q_ASSERT(pChecker);
    if( pChecker && m_setCheckers.find( pChecker ) == m_setCheckers.end() )
    {
        try
        {
            // give data provider
            pChecker->SetPerformanceDataProvider( m_pDataProvider );
            // Initialize
            pChecker->Initialize();
            m_setCheckers.insert(pChecker);
        }
        catch( std::exception const& oExc )
        {
            CMessage oMessage("Metric checker initialization failed",
                              QString( "Checker - %1" ).arg( pChecker->metaObject()?
                                                             pChecker->metaObject()->className() : "" ),
                              EMessageType::Warning);

            LOG_ERROR( oMessage.FullText().toStdString() );
            emit sigNotify( oMessage );
        }
    }
}

void CEngine::RemoveChecker(IMetricsCategoryCheckerSPtr pChecker)
{
    m_setCheckers.erase(pChecker);
}

void CEngine::RemoveAllCheckers()
{
    m_setCheckers.clear();
}

bool CEngine::IsStarted()
{
    if(m_pTimer && m_pTimer->isActive() )
        return true;
    return false;
}


void CEngine::SetUpdateInterval(int nMsecs)
{
    m_pTimer->setInterval(nMsecs);
}

void CEngine::onTimerTik()
{
    qDebug() << "Data collection started";

    CollectMetrics();

    qDebug() << " ";
}

void CEngine::CollectMetrics()
{
    if( m_setCheckers.empty() )
    {
        LOG_INFO( "No metric checkers" );
        return;
    }

    QElapsedTimer oTimer;
    oTimer.start();

    // Update Win Performance conters values
    Q_ASSERT(m_pDataProvider);
    m_pDataProvider->UpdateCounters();

    MetricDataList lstAllCollectedMetrics;
    for( IMetricsCategoryCheckerSPtr const& pChecker : m_setCheckers )
    {
        Q_ASSERT(pChecker);
        if( !pChecker )
            continue;

        MetricDataList lstCurrentMetricList = pChecker->CheckMetrics();
        lstAllCollectedMetrics.append( lstCurrentMetricList );
    }

    qint64 nElapsedOnDataCollection =  oTimer.elapsed();
    LOG_INFO( QString( "Metrics collected. Count: %1, Duration: %2 msec").arg(lstAllCollectedMetrics.size()).arg( nElapsedOnDataCollection) );

    // Notify
    emit sigMetricsCollected( lstAllCollectedMetrics );

    for( MetricDataSPtr& pMetr : lstAllCollectedMetrics)
        qDebug() << pMetr->GetName() + " " + pMetr->GetInstanceType() + " " + pMetr->GetInstanceName() + " : " + pMetr->GetValue().toString();
}





