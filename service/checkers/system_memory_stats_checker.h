#ifndef SYSTEMMEMORYSTATSCHECKER_H
#define SYSTEMMEMORYSTATSCHECKER_H

#include "../winperformancemetricschecker.h"

class SystemMemoryStatsChecker : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemMemoryStatsChecker)
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemMemoryStatsChecker();


    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};

REGISTER_METRIC_CHECKER( SystemMemoryStatsChecker )

#endif // SYSTEMMEMORYSTATSCHECKER_H
