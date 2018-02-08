#include "system_memory_stats_checker.h"


SystemMemoryStatsChecker::SystemMemoryStatsChecker()
{

}


void SystemMemoryStatsChecker::Initialize()
{
    double dConfHighVal = -1;
    double dConfSevereVal = -1;

    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
    if( bStaticAlertingEnabled )
    {
        dConfHighVal   = ConfigSection().Value<double>("high", -1);
        dConfSevereVal = ConfigSection().Value<double>("severe", -1);
    }

    bool bDetailedEnabled =  ConfigSection().Value<bool>("detailed_stats", false);

    AddCounterMetricChecker( "memory_committed_bytes_in_use",    "\\Memory%1\\% Committed Bytes In Use",     EMetricDataType::Percent, "SYSTEM", 0, dConfHighVal, dConfSevereVal);
    AddCounterMetricChecker( "memory_available_bytes",           "\\Memory%1\\Available Bytes",              EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "memory_cache_bytes",               "\\Memory%1\\Cache Bytes",                  EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "memory_committed_bytes",           "\\Memory%1\\Committed Bytes",              EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "memory_page_reads/sec",            "\\Memory%1\\Page Reads/sec",               EMetricDataType::Rate,    "SYSTEM" );
    AddCounterMetricChecker( "memory_page_writes/sec",           "\\Memory%1\\Page Writes/sec",              EMetricDataType::Rate,    "SYSTEM" );
    AddCounterMetricChecker( "memory_pages_input/sec",           "\\Memory%1\\Pages Input/sec",              EMetricDataType::Rate,    "SYSTEM" );
    AddCounterMetricChecker( "memory_page_pages_output/sec",     "\\Memory%1\\Pages Output/sec",             EMetricDataType::Rate,    "SYSTEM" );
    AddCounterMetricChecker( "memory_page_pages/sec",            "\\Memory%1\\Pages/sec",                    EMetricDataType::Rate,    "SYSTEM" );
    AddCounterMetricChecker( "memory_page_pool_nonpaged_bytes",  "\\Memory%1\\Pool Nonpaged Bytes",          EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "memory_page_pool_paged_bytes",     "\\Memory%1\\Pool Paged Bytes",             EMetricDataType::Counter, "SYSTEM" );

    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //
        AddCounterMetricChecker( "memory_commit_limit",          "\\Memory%1\\Commit Limit",                 EMetricDataType::Counter, "SYSTEM" );
        AddCounterMetricChecker( "memory_cache_bytes_peak",      "\\Memory%1\\Cache Bytes Peak",             EMetricDataType::Counter, "SYSTEM" );
        AddCounterMetricChecker( "system_cache_resident_bytes",  "\\Memory%1\\System Cache Resident Bytes",  EMetricDataType::Counter, "SYSTEM" );
        AddCounterMetricChecker( "system_code_resident_bytes",   "\\Memory%1\\System Code Resident Bytes",   EMetricDataType::Counter, "SYSTEM" );
        AddCounterMetricChecker( "system_code_total_bytes",      "\\Memory%1\\System Code Total Bytes",      EMetricDataType::Counter, "SYSTEM" );
        AddCounterMetricChecker( "system_driver_resident_bytes", "\\Memory%1\\System Driver Resident Bytes", EMetricDataType::Counter, "SYSTEM" );
        AddCounterMetricChecker( "system_driver_total_bytes",    "\\Memory%1\\System Driver Total Bytes",    EMetricDataType::Counter, "SYSTEM" );
    }
}
