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
};

REGISTER_METRIC_CHECKER(SystemDiskStatsChecker)


#endif // SYSTEM_DISK_STATS_CHECKER_H
