#ifndef SYSTEM_DISK_STATS_CHECKER_H
#define SYSTEM_DISK_STATS_CHECKER_H

#include "../winperformancemetricschecker.h"

class SystemDiskStatsChecker : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemDiskStatsChecker )
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemDiskStatsChecker(QObject *pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
    //MetricDataList CheckMetrics() override;

//private:
//    PerformanceCounterCheckersList m_lstDiskBusySpaceChecker;
//    PerformanceCounterCheckersList m_lstDiskFreeBytesChecker;

};

REGISTER_METRIC_CHECKER(SystemDiskStatsChecker)


#endif // SYSTEM_DISK_STATS_CHECKER_H
