#include "engine.h"
#include <QDebug>
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
    m_pDataProvider->UpdateCounters();
    onTimerTik();
    m_pTimer->start();
}

void CEngine::Stop()
{
    m_pTimer->stop();
}

void CEngine::AddChecker(IMetricsCheckerSPtr pChecker)
{
    Q_ASSERT(pChecker);
    if( pChecker && m_setCheckers.find( pChecker ) == m_setCheckers.end() )
    {
        // give data provider
        pChecker->SetPerformanceDataProvider( m_pDataProvider );
        // Initialize
        pChecker->Initialize();
        m_setCheckers.insert(pChecker);
    }
}

void CEngine::RemoveChecker(IMetricsCheckerSPtr pChecker)
{
    m_setCheckers.erase(pChecker);
}

void CEngine::RemoveAllCheckers()
{
    m_setCheckers.clear();
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
    // Update Win Performance conters values
    Q_ASSERT(m_pDataProvider);
    m_pDataProvider->UpdateCounters();

    MetricDataList lstAllCollectedMetrics;
    for( IMetricsCheckerSPtr const& pChecker : m_setCheckers )
    {
        Q_ASSERT(pChecker);
        if( !pChecker )
            continue;

        MetricDataList lstCurrentMetricList = pChecker->CheckMetrics();
        lstAllCollectedMetrics.append( lstCurrentMetricList );
    }

    // Notify
    emit sigMetricsCollected( lstAllCollectedMetrics );

    for( MetricDataSPtr& pMetr : lstAllCollectedMetrics)
        qDebug() << pMetr->GetName() +  " " + pMetr->GetInstanceType() + pMetr->GetInstanceName() + " : " + pMetr->GetValue().toString();
}





