#ifndef CPDHMETRICSCHECKER_H
#define CPDHMETRICSCHECKER_H

#include "imetricschecker.h"
#include "checkers/singlemetricchecker.h"

class CPdhMetricsChecker : public IMetricsChecker
{
    using Base = IMetricsChecker;

public:
    CPdhMetricsChecker(QObject* pParent = nullptr);

public:
    MetricDataList CheckMetrics() override;

protected:
    SingleMetricCheckerSPtr AddSingleMetricChecker( SingleMetricCheckerSPtr pCounterChecker );
    QList<SingleMetricCheckerSPtr> AddCounterMetricChecker( QString const& sMetricName,
                                                            QString const& sCounterPathOrWildcard,
                                                            EMetricDataType eMetricDataType,
                                                            const QString &sMetricType,
                                                            int     nReaction = 0,
                                                            double  dHighValue = -1,
                                                            double  dSevereValue = -1,
                                                            bool    bCreateMultipleCheckersByInstanceNames = false,
                                                            QString const& sInstanceObjectName = QString(),
                                                            QString const& sInstanceType = QString(),
                                                            MetricModifierFunc funcMetricModifier = nullptr);

private:
    // Content
    QList<SingleMetricCheckerSPtr> m_lstSingleMetricCheckers;
};



#endif // CPDHMETRICSCHECKER_H
