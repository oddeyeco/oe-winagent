#include "system_memory_stats_checker.h"


SystemMemoryStatsChecker::SystemMemoryStatsChecker()
{

}


void SystemMemoryStatsChecker::Initialize()
{
    ADD_METRIC_CHECKER( "available_memory", L"\\Memory\\Available MBytes", EMetricDataType::Counter, "SYSTEM", 0, -1, -1 );
}
