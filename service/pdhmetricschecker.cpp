#include "pdhmetricschecker.h"

CPdhMetricsChecker::CPdhMetricsChecker(QObject *pParent)
    : Base( pParent )
{
}

MetricDataList CPdhMetricsChecker::CheckMetrics()
{
    MetricDataList lstMetrics;
    for( SingleMetricCheckerSPtr pCurrentSingleChecker : m_lstSingleMetricCheckers )
    {
        Q_ASSERT(pCurrentSingleChecker);
        auto pMetricData = pCurrentSingleChecker->CheckMetric();
        lstMetrics.append(pMetricData);
    }

    return lstMetrics;
}

void CPdhMetricsChecker::AddSingleMetricChecker(SingleMetricCheckerSPtr pCounterChecker)
{
    Q_ASSERT(pCounterChecker);
    if( pCounterChecker )
        m_lstSingleMetricCheckers.append(pCounterChecker);
}
