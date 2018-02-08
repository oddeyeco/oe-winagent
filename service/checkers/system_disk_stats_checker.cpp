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
                             bPerCoreEnabled,
                             "Disk",
                             "LogicalDisk",
                             [](auto pMetric){ pMetric->SetValue( 100.0 - pMetric->GetValue().toDouble() )});

    AddCounterMetricChecker( "disk_free_bytes",
                             "\\LogicalDisk%1\\Free Megabytes",
                             EMetricDataType::Counter,
                             "SYSTEM", 0, -1, -1,
                             bPerDiskEnabled,
                             "Disk",
                             "LogicalDisk",
                             [](auto pMetric){ pMetric->SetValue( MBSize * pMetric->GetValue().toInt() )  });

    AddCounterMetricChecker( "disk_total_bytes",
                             "\\LogicalDisk%1\\Total Megabytes",
                             EMetricDataType::Counter,
                             "SYSTEM", 0, -1, -1,
                             bPerDiskEnabled,
                             "Disk",
                             "LogicalDisk",
                             [](auto pMetric){ pMetric->SetValue( MBSize * pMetric->GetValue().toInt() )  });


    AddCounterMetricChecker( "disk_Idle Time", "\\LogicalDisk%1\\% Idle Time", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");
    AddCounterMetricChecker( "Disk Reads/sec", "\\LogicalDisk%1\\Disk Reads/sec", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");
    AddCounterMetricChecker( "Disk Transfers/sec", "\\LogicalDisk%1\\Disk Transfers/sec", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");
    AddCounterMetricChecker( "Disk Writes/sec", "\\LogicalDisk%1\\Disk Writes/sec", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");

    AddCounterMetricChecker( "Disk Bytes/sec", "\\LogicalDisk%1\\Disk Bytes/sec", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");
    AddCounterMetricChecker( "Disk Read Bytes/sec", "\\LogicalDisk%1\\Disk Read Bytes/sec", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");
    AddCounterMetricChecker( "Disk Write Bytes/sec", "\\LogicalDisk%1\\Disk Write Bytes/sec", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerDiskEnabled, "Disk", "LogicalDisk");




//    if( bDetailedEnabled )
//    {
//        //
//        //  Add extra checkers
//        //
//        AddCounterMetricChecker( "memory_commit_limit",          "\\Memory%1\\Commit Limit",                 EMetricDataType::Counter, "SYSTEM" );
//        AddCounterMetricChecker( "memory_cache_bytes_peak",      "\\Memory%1\\Cache Bytes Peak",             EMetricDataType::Counter, "SYSTEM" );
//        AddCounterMetricChecker( "system_cache_resident_bytes",  "\\Memory%1\\System Cache Resident Bytes",  EMetricDataType::Counter, "SYSTEM" );
//        AddCounterMetricChecker( "system_code_resident_bytes",   "\\Memory%1\\System Code Resident Bytes",   EMetricDataType::Counter, "SYSTEM" );
//        AddCounterMetricChecker( "system_code_total_bytes",      "\\Memory%1\\System Code Total Bytes",      EMetricDataType::Counter, "SYSTEM" );
//        AddCounterMetricChecker( "system_driver_resident_bytes", "\\Memory%1\\System Driver Resident Bytes", EMetricDataType::Counter, "SYSTEM" );
//        AddCounterMetricChecker( "system_driver_total_bytes",    "\\Memory%1\\System Driver Total Bytes",    EMetricDataType::Counter, "SYSTEM" );
//    }
}
