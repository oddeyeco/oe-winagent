#include "system_cpu_stats_checker.h"

SystemCpuStatsChecker::SystemCpuStatsChecker(QObject *pParent)
    : Base( pParent )
{

}

void SystemCpuStatsChecker::Initialize()
{
    double dConfHighVal   = -1;
    double dConfSevereVal = -1;

    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
    if( bStaticAlertingEnabled )
    {
        dConfHighVal   = ConfigSection().Value<double>("high", -1);
        dConfSevereVal = ConfigSection().Value<double>("severe", -1);
    }

    bool bPerCoreEnabled =  ConfigSection().Value<bool>("percore_stats", false);
    bool bDetailedEnabled =  ConfigSection().Value<bool>("detailed_stats", false);

    AddPerformanceCounterCheckerEx( "cpu_load",           "\\Processor%1\\% Processor Time", EMetricDataType::Percent, "SYSTEM", 0, dConfHighVal, dConfSevereVal, bPerCoreEnabled, "Processor", "Core" );
    AddPerformanceCounterCheckerEx( "cpu_idle",           "\\Processor%1\\% Idle Time",      EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor", "Core" );
    AddPerformanceCounterCheckerEx( "cpu_interrupt_time", "\\Processor%1\\% Interrupt Time", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor", "Core" );
    AddPerformanceCounterCheckerEx( "process_count",      "\\System%1\\Processes",           EMetricDataType::Counter, "SYSTEM" );
    AddPerformanceCounterCheckerEx( "thread_count",       "\\Process%1\\Thread Count",       EMetricDataType::Counter, "SYSTEM" );
    AddPerformanceCounterCheckerEx( "handle_count",       "\\Process%1\\Handle Count",       EMetricDataType::Counter, "SYSTEM" );

    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //
        AddPerformanceCounterCheckerEx( "cpu_privileged_time",    "\\Processor%1\\% Privileged Time",                  EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor", "Core" );
        AddPerformanceCounterCheckerEx( "cpu_dpc_time",           "\\Processor%1\\% DPC Time",                         EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor", "Core" );

        PerformanceCounterCheckersList lstProcInformationCheckers;
        lstProcInformationCheckers.append( AddPerformanceCounterCheckerEx( "cpu_max_frequency",      "\\Processor Information%1\\% of Maximum Frequency", EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor Information", "Core" ) );
        lstProcInformationCheckers.append( AddPerformanceCounterCheckerEx( "cpu_performance_limit",  "\\Processor Information%1\\% Performance Limit",    EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor Information", "Core" ) );
        lstProcInformationCheckers.append( AddPerformanceCounterCheckerEx( "cpu_performance_time",   "\\Processor Information%1\\% Priority Time",        EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor Information", "Core" ) );
        lstProcInformationCheckers.append( AddPerformanceCounterCheckerEx( "cpu_privileged_time",    "\\Processor Information%1\\% Privileged Time",      EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor Information", "Core" ) );
        lstProcInformationCheckers.append( AddPerformanceCounterCheckerEx( "cpu_privileged_utility", "\\Processor Information%1\\% Privileged Utility",   EMetricDataType::Percent, "SYSTEM", 0, -1, -1, bPerCoreEnabled, "Processor Information", "Core" ) );

        // correcting instance names
        for( PerformanceCounterCheckerSPtr pPerfCounterChecker : lstProcInformationCheckers )
        {
            Q_ASSERT( pPerfCounterChecker );
            QString sInstanceName = pPerfCounterChecker->GetInstanceName();
            int nIdx = sInstanceName.lastIndexOf( "," );

            bool bNotDuplicate = true;
            if( nIdx >= 0 )
            {
                sInstanceName.remove(0, nIdx + 1);

                // Check if the normailized name is a duplicate or not
                for( PerformanceCounterCheckerSPtr pCurrentChecker : lstProcInformationCheckers )
                {
                    if( pCurrentChecker->GetMetricName() == pPerfCounterChecker->GetMetricName()
                            && pCurrentChecker->GetInstanceName() == sInstanceName )
                    {
                        // case: Duplicate, so remove from checkers list
                        Base::RemoveMetricChecker( pPerfCounterChecker );
                        bNotDuplicate = false;
                        break;
                    }
                }
            }

            if( bNotDuplicate )
                pPerfCounterChecker->SetInstanceName( sInstanceName );
        }
    }
}
