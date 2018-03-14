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

    PerformanceCounterCheckerSPtr  AddPerformanceCounterChecker( QString sPerfCounterPath,
                                                                 QString const& sMetricType,
                                                                 QString sMetricName = QString() );



    // Creates CPerformanceCounterChecker instance and addes to checkers list.
    // if bCreateMultipleCheckersByInstanceNames is TRUE then creates multiple checkers
    // acording to Counter Instance Names using specified Counter Object
    PerformanceCounterCheckersList AddPerformanceCounterCheckerEx(QString const& sMetricName,
                                                                   QString const& sCounterPathOrWildcard,
                                                                   EMetricDataType eMetricDataType,
                                                                   const QString &sMetricType,
                                                                   int     nReaction = 0,
                                                                   double  dHighValue = -1,
                                                                   double  dSevereValue = -1,
                                                                   bool    bCreateMultipleCheckersByInstanceNames = false,
                                                                   QString const& sInstanceObjectName = QString(),
                                                                   QString const& sInstanceType = QString(),
                                                                   ValueModifierFunc funcMetricModifier = nullptr,
                                                                   QStringList lstAllowedInstanceNames = QStringList());
    // Creates Multiple Checkers By Allowed Instance Names
    PerformanceCounterCheckersList  AddPerformanceCounterCheckerEx( QString sPerfCounterPath,
                                                                    QString const& sMetricType,
                                                                    QStringList lstAllowedInstances,
                                                                    QString sMetricName = QString() );

    static QString MakeMetricNameFromCounterPath(QString sCounterPath,
                                                  EMetricDataType* pGuessedMetricDataType = nullptr,
                                                  QString* pInstanceName = nullptr,
                                                  QString* psCounterType = nullptr );

    static bool ContainesOneOf( const QString &sSourceString, const QStringList &lstLexems );

private:
    static QString NormalizeAsName( QString sText );

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Useful Macros
//
#define DECLARE_PERF_COUNTER_METRIC_CHECKER(_class_)       \
    class _class_ : public CWinPerformanceMetricsChecker   \
    {                                                      \
        DECLARE_MERTIC_CHECKER(_class_)                    \
        using Base = CWinPerformanceMetricsChecker;        \
    public:                                                \
        _class_(QObject* pParent = nullptr) : Base(pParent) {}               \
    public:                                                \
        void Initialize() override;                        \
    };                                                     \
REGISTER_METRIC_CHECKER( _class_ )

#define INIT_METRIC_CHECKER(_class_) void _class_::Initialize()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // CWINPERFORMANCEMETRICSCHECKER_H
