#include "system_disk_stats.h"

const int MBSize = 1048576;

INIT_METRIC_CHECKER(SystemDiskStats)
{
    double dConfHighVal = -1;
    double dConfSevereVal = -1;

    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
    if( bStaticAlertingEnabled )
    {
        dConfHighVal   = ConfigSection().Value<double>("high", -1);
        dConfSevereVal = ConfigSection().Value<double>("severe", -1);
    }

    bool bDetailedEnabled = ConfigSection().Value<bool>("detailed_stats", false);
    bool bPerDiskEnabled  = ConfigSection().Value<bool>("perdisk_stats",  false);

    AddPerformanceCounterCheckerEx( "disk_busy_space",
                             "\\LogicalDisk%1\\% Free Space",
                             EMetricDataType::Percent,
                             "SYSTEM", 0,
                             dConfHighVal,
                             dConfSevereVal,
                             bPerDiskEnabled,
                             "LogicalDisk",
                             "Drive",
                             [](double& dVal){ dVal = 100.0 - dVal; });

    AddPerformanceCounterCheckerEx( "disk_free_bytes",
                             "\\LogicalDisk%1\\Free Megabytes",
                             EMetricDataType::Counter,
                             "SYSTEM", 0, -1, -1,
                             bPerDiskEnabled,
                             "LogicalDisk",
                             "Drive",
                             [](double& dVal){ dVal *= MBSize; });


    AddPerformanceCounterCheckerEx( "disk_idle_time",   "\\LogicalDisk%1\\% Idle Time",          EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
    AddPerformanceCounterCheckerEx( "disk_reads",       "\\LogicalDisk%1\\Disk Reads/sec",       EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
    AddPerformanceCounterCheckerEx( "disk_transfers",   "\\LogicalDisk%1\\Disk Transfers/sec",   EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
    AddPerformanceCounterCheckerEx( "disk_writes",      "\\LogicalDisk%1\\Disk Writes/sec",      EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
    AddPerformanceCounterCheckerEx( "disk_bytes",       "\\LogicalDisk%1\\Disk Bytes/sec",       EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
    AddPerformanceCounterCheckerEx( "disk_read_bytes",  "\\LogicalDisk%1\\Disk Read Bytes/sec",  EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
    AddPerformanceCounterCheckerEx( "disk_write_bytes", "\\LogicalDisk%1\\Disk Write Bytes/sec", EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");


    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //
        AddPerformanceCounterCheckerEx( "disk_read_time",  "\\LogicalDisk%1\\% Disk Read Time",  EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
        AddPerformanceCounterCheckerEx( "disk_time",       "\\LogicalDisk%1\\% Disk Time",       EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
        AddPerformanceCounterCheckerEx( "disk_write_time", "\\LogicalDisk%1\\% Disk Write Time", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Drive");
     }
}

//MetricDataList SystemDiskStats::CheckMetrics()
//{
//    MetricDataList lstBaseMetrics = Base::CheckMetrics();
//    Q_ASSERT(m_lstDiskBusySpaceChecker.size() == m_lstDiskFreeBytesChecker);
//}
