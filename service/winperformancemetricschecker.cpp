#include "winperformancemetricschecker.h"

CWinPerformanceMetricsChecker::CWinPerformanceMetricsChecker(QObject *pParent)
    : Base( pParent )
{
}

PerformanceCounterCheckersList CWinPerformanceMetricsChecker::AddPerformanceCounterCheckerEx( const QString &sMetricName,
                                                                                       const QString &sCounterPathOrWildcard,
                                                                                       EMetricDataType eMetricDataType,
                                                                                       const QString &sMetricType,
                                                                                       int nReaction,
                                                                                       double dHighValue,
                                                                                       double dSevereValue,
                                                                                       bool bCreateMultipleCheckersByInstanceNames,
                                                                                       const QString &sInstanceObjectName,
                                                                                       const QString &sInstanceType,
                                                                                       ValueModifierFunc funcMetricModifier)
{
    QList<PerformanceCounterCheckerSPtr> lstAddedCheckers;

    if( !bCreateMultipleCheckersByInstanceNames )
    {
        // complete counter path
        QString sFilledCounterPathOrWildcard = sCounterPathOrWildcard.arg("(_Total)");

        auto pChecker = AddPerformanceCounterChecker(  sMetricName,
                                                       sFilledCounterPathOrWildcard,
                                                       eMetricDataType,
                                                       sMetricType,
                                                       nReaction,
                                                       dHighValue,
                                                       dSevereValue,
                                                       sInstanceType,
                                                       "",
                                                       funcMetricModifier );

        lstAddedCheckers.append( pChecker );
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
            auto pChecker = AddPerformanceCounterChecker(  sMetricName,
                                                           sCurrentCounterPath,
                                                           eMetricDataType,
                                                           sMetricType,
                                                           nReaction,
                                                           dHighValue,
                                                           dSevereValue,
                                                           sInstanceType,
                                                           sCurrentInstanceName,
                                                           funcMetricModifier );
            lstAddedCheckers.append(pChecker);
        }

    }

    return lstAddedCheckers;
}

PerformanceCounterCheckerSPtr CWinPerformanceMetricsChecker::AddPerformanceCounterChecker(  const QString &sMetricName,
                                                                                            const QString &sCurrentCounterPath,
                                                                                            EMetricDataType eMetricDataType,
                                                                                            const QString &sMetricType,
                                                                                            int nReaction,
                                                                                            double dHighValue,
                                                                                            double dSevereValue,
                                                                                            const QString &sInstanceType,
                                                                                            const QString &sInstanceName,
                                                                                            ValueModifierFunc funcMetricModifier)
{
    // create checker
    auto pChecker = std::make_shared<CPerformanceCounterChecker>( sMetricName,
                                                                  sCurrentCounterPath,
                                                                  eMetricDataType,
                                                                  sMetricType,
                                                                  PerfDataProvider(),
                                                                  nReaction,
                                                                  dHighValue,
                                                                  dSevereValue,
                                                                  sInstanceType,
                                                                  sInstanceName,
                                                                  funcMetricModifier );
    Base::AddMetricChecker( pChecker );
    return pChecker;
}
