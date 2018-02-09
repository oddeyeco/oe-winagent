#ifndef SYSTEMCPUSTATSCHECKER_H
#define SYSTEMCPUSTATSCHECKER_H

#include "../winperformancemetricschecker.h"


class SystemCpuStatsChecker : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemCpuStatsChecker )
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemCpuStatsChecker(QObject *pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};


REGISTER_METRIC_CHECKER(SystemCpuStatsChecker)

#endif // SYSTEMCPUSTATSCHECKER_H
