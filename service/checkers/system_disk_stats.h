#ifndef SYSTEM_DISK_STATS_CHECKER_H
#define SYSTEM_DISK_STATS_CHECKER_H

#include "../winperformancemetricschecker.h"

class SystemDiskStats : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemDiskStats )
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemDiskStats(QObject *pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
    //MetricDataList CheckMetrics() override;

//private:
//    PerformanceCounterCheckersList m_lstDiskBusySpaceChecker;
//    PerformanceCounterCheckersList m_lstDiskFreeBytesChecker;

};

REGISTER_METRIC_CHECKER(SystemDiskStats)


#endif // SYSTEM_DISK_STATS_CHECKER_H
