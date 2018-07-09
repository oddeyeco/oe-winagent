#include "system_disk_stats.h"


const int MBSize = 1048576;

class CDiskTotalBytesChecker : public CBasicMetricChecker
{
    using Base = CBasicMetricChecker;
public:
    CDiskTotalBytesChecker( BasicMetricCheckerSPtr pDiskBusySpacePercentChecker,
                            BasicMetricCheckerSPtr pDiskFreeBytesChecker)
        : Base("disk_total_bytes",
               EMetricDataType::Counter,
               "SYSTEM", 0 ),
          m_pDiskBusySpacePercentChecker(pDiskBusySpacePercentChecker),
          m_pDiskFreeBytesChecker(pDiskFreeBytesChecker)

    {
        Q_ASSERT( pDiskBusySpacePercentChecker );
        Q_ASSERT( pDiskFreeBytesChecker );
        Base::SetInstanceName( pDiskBusySpacePercentChecker->GetInstanceName() );
        Base::SetInstanceType( pDiskBusySpacePercentChecker->GetInstanceType() );
    }


private:
    BasicMetricCheckerSPtr m_pDiskBusySpacePercentChecker;
    BasicMetricCheckerSPtr m_pDiskFreeBytesChecker;

    // CBasicMetricChecker interface
protected:
    double CheckMetricValue()
    {
        if( !m_pDiskBusySpacePercentChecker || !m_pDiskFreeBytesChecker )
            return -1;

        // calc free space percent
        auto pBusySpacePercent = m_pDiskBusySpacePercentChecker->CheckMetric();
        if( !pBusySpacePercent )
            return -1;
        double dFreeSpacePercent = 100.0 - pBusySpacePercent->GetValue().toDouble();

        // calc free bytes
        auto pFreeBytes = m_pDiskFreeBytesChecker->CheckMetric();
        if( !pFreeBytes )
            return -1;
        double nFreeBytes = pFreeBytes->GetValue().toDouble();

        qint64 nTotalBytes = static_cast<qint64>( (nFreeBytes*100) / dFreeSpacePercent );
        return static_cast<double>(nTotalBytes);
    }
};



INIT_METRIC_CHECKER(SystemDiskStats, "LogicalDisk")
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

    PerformanceCounterCheckersList lstDiskBusySpaceCheckers = AddPerformanceCounterCheckerEx(
                "disk_busy_space",
                "\\LogicalDisk%1\\% Free Space",
                EMetricDataType::Percent,
                "SYSTEM", 0,
                dConfHighVal,
                dConfSevereVal,
                bPerDiskEnabled,
                "LogicalDisk",
                "Drive",
                [](double& dVal){ dVal = 100.0 - dVal; });

    PerformanceCounterCheckersList lstDiskFreeBytesCheckers = AddPerformanceCounterCheckerEx(
                "disk_free_bytes",
                "\\LogicalDisk%1\\Free Megabytes",
                EMetricDataType::Counter,
                "SYSTEM", 0, -1, -1,
                bPerDiskEnabled,
                "LogicalDisk",
                "Drive",
                [](double& dVal){ dVal *= MBSize; });

    // add total disk space checker
    Q_ASSERT(lstDiskBusySpaceCheckers.size() == lstDiskFreeBytesCheckers.size());
    if( lstDiskBusySpaceCheckers.size() == lstDiskFreeBytesCheckers.size() )
    {
        for( int i = 0; i < lstDiskBusySpaceCheckers.size(); ++i )
        {
            auto pChecker = std::make_shared<CDiskTotalBytesChecker>(lstDiskBusySpaceCheckers.at(i),
                                                                     lstDiskFreeBytesCheckers.at(i));
            Base::AddMetricChecker( pChecker );
        }
    }


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
