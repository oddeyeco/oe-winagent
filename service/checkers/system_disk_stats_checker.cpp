#include "system_disk_stats_checker.h"

constexpr int MBSize = 1048576;

SystemDiskStatsChecker::SystemDiskStatsChecker(QObject *pParent)
    : Base(pParent)
{}

void SystemDiskStatsChecker::Initialize()
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

    AddCounterMetricChecker( "disk_busy_space",
                             "\\LogicalDisk%1\\% Free Space",
                             EMetricDataType::Percent,
                             "SYSTEM", 0,
                             dConfHighVal,
                             dConfSevereVal,
                             bPerDiskEnabled,
                             "LogicalDisk",
                             "Disk",
                             [](auto pMetric){ pMetric->SetValue( 100.0 - pMetric->GetValue().toDouble() ); });

    AddCounterMetricChecker( "disk_free_bytes",
                             "\\LogicalDisk%1\\Free Megabytes",
                             EMetricDataType::Counter,
                             "SYSTEM", 0, -1, -1,
                             bPerDiskEnabled,
                             "LogicalDisk",
                             "Disk",
                             [](auto pMetric){ pMetric->SetValue( MBSize * pMetric->GetValue().toInt() );  });


    AddCounterMetricChecker( "disk_idle_time",       "\\LogicalDisk%1\\% Idle Time",          EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
    AddCounterMetricChecker( "disk_reads/sec",       "\\LogicalDisk%1\\Disk Reads/sec",       EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
    AddCounterMetricChecker( "disk_transfers/sec",   "\\LogicalDisk%1\\Disk Transfers/sec",   EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
    AddCounterMetricChecker( "disk_writes/sec",      "\\LogicalDisk%1\\Disk Writes/sec",      EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
    AddCounterMetricChecker( "disk_bytes/sec",       "\\LogicalDisk%1\\Disk Bytes/sec",       EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
    AddCounterMetricChecker( "disk_read_bytes/sec",  "\\LogicalDisk%1\\Disk Read Bytes/sec",  EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
    AddCounterMetricChecker( "disk_write_bytes/sec", "\\LogicalDisk%1\\Disk Write Bytes/sec", EMetricDataType::Rate,    "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");


    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //
        AddCounterMetricChecker( "disk_read_time",  "\\LogicalDisk%1\\% Disk Read Time",  EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
        AddCounterMetricChecker( "disk_time",       "\\LogicalDisk%1\\% Disk Time",       EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
        AddCounterMetricChecker( "disk_write_time", "\\LogicalDisk%1\\% Disk Write Time", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "LogicalDisk", "Disk");
     }
}

//MetricDataList SystemDiskStatsChecker::CheckMetrics()
//{
//    MetricDataList lstBaseMetrics = Base::CheckMetrics();
//    Q_ASSERT(m_lstDiskBusySpaceChecker.size() == m_lstDiskFreeBytesChecker);
//}
