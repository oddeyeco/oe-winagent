#ifndef SYSTEMMEMORYSTATSCHECKER_H
#define SYSTEMMEMORYSTATSCHECKER_H

#include "../pdhmetricschecker.h"

class SystemMemoryStatsChecker : public CPdhMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemMemoryStatsChecker)
    using Base = CPdhMetricsChecker;

public:
    SystemMemoryStatsChecker();


    // IMetricsChecker interface
public:
    void Initialize();
};

REGISTER_METRIC_CHECKER( SystemMemoryStatsChecker )

#endif // SYSTEMMEMORYSTATSCHECKER_H
