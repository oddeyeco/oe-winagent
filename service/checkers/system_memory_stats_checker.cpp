#include "system_memory_stats_checker.h"


SystemMemoryStatsChecker::SystemMemoryStatsChecker()
{

}


void SystemMemoryStatsChecker::Initialize()
{
    double dConfigHighValue = -1;
    double dConfigSevereValue = -1;

    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
    if( bStaticAlertingEnabled )
    {
        dConfigHighValue = ConfigSection().Value<double>("high", -1);
        dConfigSevereValue = ConfigSection().Value<double>("severe", -1);
    }

    bool bPerCoreEnabled =  ConfigSection().Value<bool>("percore_stats", false);
    bool bDetailedEnabled =  ConfigSection().Value<bool>("detailed_stats", false);

    AddCounterMetricChecker( "Memory Committed Bytes In Use",   "\\Memory%1\\% Committed Bytes In Use", EMetricDataType::Percent, "SYSTEM", 0, dConfigHighValue, dConfigSevereValue);
    AddCounterMetricChecker( "Memory Available Bytes",          "\\Memory%1\\Available Bytes",          EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Cache Bytes",              "\\Memory%1\\Cache Bytes",              EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Committed Bytes",          "\\Memory%1\\Committed Bytes",          EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Page Reads/sec",           "\\Memory%1\\Page Reads/sec",           EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Page Writes/sec",          "\\Memory%1\\Page Writes/sec",          EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Pages Input/sec",          "\\Memory%1\\Pages Input/sec",          EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Page Pages Output/sec",    "\\Memory%1\\Pages Output/sec",         EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Page Pages/sec",           "\\Memory%1\\Pages/sec",                EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Page Pool Nonpaged Bytes", "\\Memory%1\\Pool Nonpaged Bytes",      EMetricDataType::Counter, "SYSTEM" );
    AddCounterMetricChecker( "Memory Page Pool Paged Bytes",    "\\Memory%1\\Pool Paged Bytes",         EMetricDataType::Counter, "SYSTEM" );

}
