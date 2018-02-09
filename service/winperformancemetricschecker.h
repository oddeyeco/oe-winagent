#ifndef CWINPERFORMANCEMETRICSCHECKER_H
#define CWINPERFORMANCEMETRICSCHECKER_H

#include "metricsgroupchecker.h"
#include "checkers/performanceounterhecker.h"

using PerformanceCounterCheckersList = QList<PerformanceCounterCheckerSPtr>;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  Base class for Windows performance counter checkers group
///
class CWinPerformanceMetricsChecker : public CMetricsGroupChecker
{
    using Base = CMetricsGroupChecker;

public:
    CWinPerformanceMetricsChecker(QObject* pParent = nullptr);

protected:
    // Creates CPerformanceCounterChecker instance and addes to checkers list
    PerformanceCounterCheckerSPtr AddPerformanceCounterChecker( QString const& sMetricName,
                                                                QString const& sCurrentCounterPath,
                                                                EMetricDataType eMetricDataType,
                                                                const QString &sMetricType,
                                                                int     nReaction = 0,
                                                                double  dHighValue = -1,
                                                                double  dSevereValue = -1,
                                                                QString const& sInstanceType = QString(),
                                                                QString const& sInstanceName = QString(),
                                                                ValueModifierFunc funcMetricModifier = nullptr );

    // Creates CPerformanceCounterChecker instance and addes to checkers list.
    // if bCreateMultipleCheckersByInstanceNames is TRUE then creates multiple checkers
    // acording to Counter Instance Names using specified Counter Object
    PerformanceCounterCheckersList AddPerformanceCounterCheckerEx( QString const& sMetricName,
                                                                   QString const& sCounterPathOrWildcard,
                                                                   EMetricDataType eMetricDataType,
                                                                   const QString &sMetricType,
                                                                   int     nReaction = 0,
                                                                   double  dHighValue = -1,
                                                                   double  dSevereValue = -1,
                                                                   bool    bCreateMultipleCheckersByInstanceNames = false,
                                                                   QString const& sInstanceObjectName = QString(),
                                                                   QString const& sInstanceType = QString(),
                                                                   ValueModifierFunc funcMetricModifier = nullptr );

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // CWINPERFORMANCEMETRICSCHECKER_H
