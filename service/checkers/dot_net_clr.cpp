#include "dot_net_clr.h"

//
//  DotNetClrJit
//
DotNetClrJit::DotNetClrJit(QObject* pParent)
    : Base(pParent)
{}

void DotNetClrJit::Initialize()
{
    AddPerformanceCounterChecker("dot_net_clr_il_bytes_jitted", "\\.NET CLR Jit(_Global_)\\# of IL Bytes Jitted", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_methods_jitted", "\\.NET CLR Jit(_Global_)\\# of Methods Jitted", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_time_in_jit", "\\.NET CLR Jit(_Global_)\\% Time in Jit", EMetricDataType::Percent, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_standard_jit_failures", "\\.NET CLR Jit(_Global_)\\Standard Jit Failures", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_total_il_bytes_jitted", "\\.NET CLR Jit(_Global_)\\Total # of IL Bytes Jitted", EMetricDataType::Counter, "DotNet" );

    AddPerformanceCounterChecker("dot_net_clr_il_bytes_jitted", "\\.NET CLR Exceptions(_Global_)\\# of Exceps Thrown", EMetricDataType::Counter, "DotNet" );

    try{

    QVector<QString> aCounters = CWinPerformanceDataProvider::GetAllAvailableCounterPaths();
    for(int i = 0; i < aCounters.size(); ++i )
    {
        QString sCounterPath = aCounters[i];
        EMetricDataType eGessedType;
        QString sInstanceName;
        QString sMetricName = Base::MakeMetricNameFromCounterPath( sCounterPath, &eGessedType, &sInstanceName );

        int ll = sInstanceName.size();
    }




    } catch( std::exception& e )
    {
        QString ss(e.what());
        int kk = 5;
    }

}

//
//  DotNetClrLocksAndThreads
//
DotNetClrLocksAndThreads::DotNetClrLocksAndThreads(QObject *pParent)
    : Base(pParent)
{}

void DotNetClrLocksAndThreads::Initialize()
{
    AddPerformanceCounterChecker("dot_net_clr_current_logical_threads_count",  "\\.NET CLR LocksAndThreads(_Global_)\\# of current logical Threads",  EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_current_physical_threads_count", "\\.NET CLR LocksAndThreads(_Global_)\\# of current physical Threads", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_contention_rate",                "\\.NET CLR LocksAndThreads(_Global_)\\Contention Rate / sec",         EMetricDataType::Rate,    "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_current_queue_length",           "\\.NET CLR LocksAndThreads(_Global_)\\Current Queue Length",          EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_queue_length_peak",              "\\.NET CLR LocksAndThreads(_Global_)\\Queue Length Peak",             EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_total_count_of_contentions",     "\\.NET CLR LocksAndThreads(_Global_)\\Total # of Contentions",        EMetricDataType::Counter, "DotNet" );
}

DotNetClrMemory::DotNetClrMemory(QObject *pParent)
    : Base(pParent)
{
}

void DotNetClrMemory::Initialize()
{
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Bytes in all Heaps",  EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# GC Handles", EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Gen 0 Collections",         EMetricDataType::Counter,    "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Gen 1 Collections",          EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Gen 2 Collections",             EMetricDataType::Counter, "DotNet" );

//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Induced GC",  EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# GC Handles", EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# of Pinned Objects",         EMetricDataType::Counter,    "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# of Sink Blocks in use",          EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Total committed Bytes",             EMetricDataType::Counter, "DotNet" );

//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\# Total reserved Bytes",  EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\% Time in GC",             EMetricDataType::Percent, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Allocated Bytes/sec",         EMetricDataType::Rate,    "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Finalization Survivors",          EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Gen 0 heap size",             EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Gen 0 Promoted Bytes/Sec",                 EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Gen 1 heap size",                  EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Gen 1 Promoted Bytes/Sec",         EMetricDataType::Counter,    "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Gen 2 heap size",          EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Large Object Heap size",             EMetricDataType::Counter, "DotNet" );

//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Promoted Finalization-Memory from Gen 0",         EMetricDataType::Counter,    "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Promoted Memory from Gen 0",          EMetricDataType::Counter, "DotNet" );
//    AddPerformanceCounterChecker("dot_net_clr_memory_", "\\.NET CLR Memory(_Global_)\\Promoted Memory from Gen 1",             EMetricDataType::Counter, "DotNet" );






}
