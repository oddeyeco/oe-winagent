#ifndef SYSTEMCPUSTATS_H
#define SYSTEMCPUSTATS_H

#include "../winperformancemetricschecker.h"


class SystemCpuStats : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemCpuStats )
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemCpuStats(QObject *pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};


REGISTER_METRIC_CHECKER(SystemCpuStats)

#endif // SYSTEMCPUSTATS_H
