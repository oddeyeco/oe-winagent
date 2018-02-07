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

void CPdhMetricsChecker::AddCounterMetricChecker(const QString &sMetricName,
                                                 const QString &sCounterPathOrWildcard,
                                                 EMetricDataType eMetricDataType,
                                                 const QString &sMetricType,
                                                 int nReaction,
                                                 double dHighValue,
                                                 double dSevereValue,
                                                 bool bCreateMultipleCheckersByInstanceNames,
                                                 const QString &sInstanceObjectName,
                                                 const QString &sInstanceType)
{
    if( !bCreateMultipleCheckersByInstanceNames )
    {
        // complete counter path
        QString sFilledCounterPathOrWildcard = sCounterPathOrWildcard.arg("(_Total)");

        AddSingleMetricChecker( std::make_shared<CSingleMetricChecker>( sMetricName,
                                                                        sFilledCounterPathOrWildcard,
                                                                        eMetricDataType,
                                                                        sMetricType,
                                                                        PerfDataProvider(),
                                                                        nReaction,
                                                                        dHighValue,
                                                                        dSevereValue,
                                                                        sInstanceType,
                                                                        "") );
    }
    else
    {
        // create multiple checkers by instance names
        Q_ASSERT( !sInstanceObjectName.isEmpty() );
        Q_ASSERT( !sInstanceType.isEmpty() );

        // complete counter path
        QString sFilledCounterPathOrWildcard = sCounterPathOrWildcard.arg("(*)");

        // fetch counter paths and instance names
        QStringList lstExpandedCounterPaths = CWinPerformanceDataProvider::ExpandCounterPath(sFilledCounterPathOrWildcard);
        QStringList lstInstanceNames        = CWinPerformanceDataProvider::GetObjectInstanceNames(sInstanceObjectName);
        Q_ASSERT( lstExpandedCounterPaths.size() == lstInstanceNames.size() );
        if( lstExpandedCounterPaths.size() != lstInstanceNames.size() )
            throw CCheckerInitializationException( QString("Failed to fetch per %1 information for metric %2").arg(sInstanceType.toLower(), sMetricName) );

        for( int i = 0; i < lstExpandedCounterPaths.size(); ++i )
        {
            QString sCurrentCounterPath = lstExpandedCounterPaths[i];
            QString sCurrentInstanceName = lstInstanceNames[i];

            // create checkers
            AddSingleMetricChecker( std::make_shared<CSingleMetricChecker>( sMetricName,
                                                                            sCurrentCounterPath,
                                                                            eMetricDataType,
                                                                            sMetricType,
                                                                            PerfDataProvider(),
                                                                            nReaction,
                                                                            dHighValue,
                                                                            dSevereValue,
                                                                            sInstanceType,
                                                                            sCurrentInstanceName) );
        }

    }
}
