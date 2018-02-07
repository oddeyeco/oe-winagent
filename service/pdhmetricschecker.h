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
    void AddSingleMetricChecker( SingleMetricCheckerSPtr pCounterChecker );

private:
    // Content
    QList<SingleMetricCheckerSPtr> m_lstSingleMetricCheckers;
};



#endif // CPDHMETRICSCHECKER_H
