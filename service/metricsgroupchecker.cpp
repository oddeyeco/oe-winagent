#include "metricsgroupchecker.h"
#include "basicmetricchecker.h"

CMetricsGroupChecker::CMetricsGroupChecker(QObject* pParent)
    : Base( pParent )
{
}

MetricDataList CMetricsGroupChecker::CheckMetrics()
{
    MetricDataList lstMetrics;
    for( IMetricCheckerSPtr pCurrentChecker : m_lstMetricCheckers )
    {
        Q_ASSERT(pCurrentChecker);
        if( !pCurrentChecker )
            continue;

        try
        {
            auto pMetricData = pCurrentChecker->CheckMetric();
            lstMetrics.append(pMetricData);
        }
        catch( std::exception const& oErr )
        {
            auto pBasicChecker = dynamic_cast<CBasicMetricChecker*>(pCurrentChecker.get());
            QString sMsg = pBasicChecker? QString("Excpetion: Metric %1 : %2 %3 - check failed: %4")
                                          .arg( pBasicChecker->GetMetricName() )
                                          .arg( pBasicChecker->GetInstanceType() )
                                          .arg( pBasicChecker->GetInstanceType() )
                                          .arg( oErr.what() )
                                        :
                                          QString("Excpetion: Metric checking failed: %1").arg( oErr.what() );

            if( QString(oErr.what()).contains( "negative denominator" ) )
            {
                // This is common exception and could sometimes appeare base on enviroment
                // So just Skip it

                LOG_DEBUG( sMsg );
                continue;
            }

            LOG_ERROR( sMsg.toStdString() );
        }
    }

    return lstMetrics;
}

void CMetricsGroupChecker::AddMetricChecker(IMetricCheckerSPtr pMetricChecker)
{
    Q_ASSERT(pMetricChecker);
    if( pMetricChecker )
        m_lstMetricCheckers.append(pMetricChecker);
}

void CMetricsGroupChecker::RemoveMetricChecker(IMetricCheckerSPtr pMetricChecker)
{
    if( pMetricChecker )
        m_lstMetricCheckers.removeAll( pMetricChecker );
}

