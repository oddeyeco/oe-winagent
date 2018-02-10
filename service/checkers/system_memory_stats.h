#ifndef SystemMemoryStats_H
#define SystemMemoryStats_H

#include "../winperformancemetricschecker.h"

class SystemMemoryStats : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemMemoryStats)
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemMemoryStats();


    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};

REGISTER_METRIC_CHECKER( SystemMemoryStats )

#endif // SystemMemoryStats_H
