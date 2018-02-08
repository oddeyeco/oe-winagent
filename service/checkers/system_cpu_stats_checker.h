#ifndef SYSTEMCPUSTATSCHECKER_H
#define SYSTEMCPUSTATSCHECKER_H

#include "../pdhmetricschecker.h"


class SystemCpuStatsChecker : public CPdhMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemCpuStatsChecker )
    using Base = CPdhMetricsChecker;

public:
    SystemCpuStatsChecker(QObject *pParent = nullptr);

    // IMetricsChecker interface
public:
    void Initialize();
};


REGISTER_METRIC_CHECKER(SystemCpuStatsChecker)

#endif // SYSTEMCPUSTATSCHECKER_H
