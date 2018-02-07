#include "system_cpu_stats_checker.h"

SystemCpuStatsChecker::SystemCpuStatsChecker(QObject *pParent)
    : Base( pParent )
{

}

void SystemCpuStatsChecker::Initialize()
{
    double dConfigHighValue = ConfigSection().Value<double>("high", -1);
    double dConfigSevereValue = ConfigSection().Value<double>("severe", -1);

    bool bPerCoreEnabled =  ConfigSection().Value<bool>("percore_stats", false);
    bool bDetailedEnabled =  ConfigSection().Value<bool>("detailed_stats", false);

    AddCounterMetricChecker( "cpu_load",           "\\Processor%1\\% Processor Time", EMetricDataType::Percent, "SYSTEM", 0, dConfigHighValue, dConfigSevereValue, bPerCoreEnabled, "Processor", "Core" );
    AddCounterMetricChecker( "cpu_idle",           "\\Processor%1\\% Idle Time",      EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor", "Core" );
    AddCounterMetricChecker( "cpu_interrupt_time", "\\Processor%1\\% Interrupt Time", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor", "Core" );
    //AddCounterMetricChecker( "cpu_idle", "\\Processor(_Total)\\% Idle Time", EMetricDataType::Percent, "SYSTEM" );

    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //


    }
}
