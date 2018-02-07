#include "system_memory_stats_checker.h"


SystemMemoryStatsChecker::SystemMemoryStatsChecker()
{

}


void SystemMemoryStatsChecker::Initialize()
{
    AddCounterMetricChecker( "available_memory", "\\Memory(_Total)\\Available MBytes", EMetricDataType::Counter, "SYSTEM" );
}
