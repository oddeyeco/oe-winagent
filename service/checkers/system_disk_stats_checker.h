#ifndef SYSTEM_DISK_STATS_CHECKER_H
#define SYSTEM_DISK_STATS_CHECKER_H

#include "../pdhmetricschecker.h"

class SystemDiskStatsChecker : public CPdhMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemDiskStatsChecker )
    using Base = CPdhMetricsChecker;

public:
    SystemDiskStatsChecker(QObject *pParent = nullptr);

    // IMetricsChecker interface
public:
    void Initialize() override;
    //MetricDataList CheckMetrics() override;

//private:
//    SingleMetricCheckersList m_lstDiskBusySpaceChecker;
//    SingleMetricCheckersList m_lstDiskFreeBytesChecker;

};

REGISTER_METRIC_CHECKER(SystemDiskStatsChecker)


#endif // SYSTEM_DISK_STATS_CHECKER_H
