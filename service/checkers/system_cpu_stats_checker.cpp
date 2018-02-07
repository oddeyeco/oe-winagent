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


    ADD_METRIC_CHECKER( "cpu_load", L"\\Processor(_Total)\\% Processor Time", EMetricDataType::Percent, "SYSTEM", 0, dConfigHighValue, dConfigSevereValue);
    ADD_METRIC_CHECKER( "cpu_idle", L"\\Processor(_Total)\\% Idle Time", EMetricDataType::Percent, "SYSTEM", 0, -1, -1);
}
