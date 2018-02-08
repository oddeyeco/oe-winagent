#ifndef CPDHMETRICSCHECKER_H
#define CPDHMETRICSCHECKER_H

#include "imetricschecker.h"
#include "checkers/singlemetricchecker.h"


using SingleMetricCheckersList = QList<SingleMetricCheckerSPtr>;


class CPdhMetricsChecker : public IMetricsChecker
{
    using Base = IMetricsChecker;

public:
    CPdhMetricsChecker(QObject* pParent = nullptr);

public:
    MetricDataList CheckMetrics() override;

protected:
    SingleMetricCheckerSPtr AddSingleMetricChecker( SingleMetricCheckerSPtr pMetricChecker );
    void RemoveSingleMetricChecker( SingleMetricCheckerSPtr pMetricChecker );

    SingleMetricCheckersList AddCounterMetricChecker( QString const& sMetricName,
                                                      QString const& sCounterPathOrWildcard,
                                                      EMetricDataType eMetricDataType,
                                                      const QString &sMetricType,
                                                      int     nReaction = 0,
                                                      double  dHighValue = -1,
                                                      double  dSevereValue = -1,
                                                      bool    bCreateMultipleCheckersByInstanceNames = false,
                                                      QString const& sInstanceObjectName = QString(),
                                                      QString const& sInstanceType = QString(),
                                                      MetricModifierFunc funcMetricModifier = nullptr );

    SingleMetricCheckerSPtr AddSingleMetricChecker(   QString const& sMetricName,
                                                      QString const& sCurrentCounterPath,
                                                      EMetricDataType eMetricDataType,
                                                      const QString &sMetricType,
                                                      int     nReaction = 0,
                                                      double  dHighValue = -1,
                                                      double  dSevereValue = -1,
                                                      QString const& sInstanceType = QString(),
                                                      QString const& sInstanceName = QString(),
                                                      MetricModifierFunc funcMetricModifier = nullptr );

private:
    // Content
    SingleMetricCheckersList m_lstSingleMetricCheckers;
};



#endif // CPDHMETRICSCHECKER_H
