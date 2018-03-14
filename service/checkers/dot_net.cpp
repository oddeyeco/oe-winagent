#include "dot_net.h"

//
//  DotNetClrJit
//
INIT_METRIC_CHECKER(DotNetClrJit)
{
    AddPerformanceCounterChecker("dot_net_clr_il_bytes_jitted",       "\\.NET CLR Jit(_Global_)\\# of IL Bytes Jitted", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_methods_jitted",        "\\.NET CLR Jit(_Global_)\\# of Methods Jitted", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_time_in_jit",           "\\.NET CLR Jit(_Global_)\\% Time in Jit", EMetricDataType::Percent, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_standard_jit_failures", "\\.NET CLR Jit(_Global_)\\Standard Jit Failures", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_total_il_bytes_jitted", "\\.NET CLR Jit(_Global_)\\Total # of IL Bytes Jitted", EMetricDataType::Counter, "DotNet" );

    AddPerformanceCounterChecker("dot_net_clr_il_bytes_jitted", "\\.NET CLR Exceptions(_Global_)\\# of Exceps Thrown", EMetricDataType::Counter, "DotNet" );

//    try{

//    QVector<QString> aCounters = CWinPerformanceDataProvider::GetAllAvailableCounterPaths();
//    QStringList lstFinalPaths;
//    for(int i = 0; i < aCounters.size(); ++i )
//    {
//        QString sCounterPath = aCounters[i];
//        EMetricDataType eGessedType;
//        QString sInstanceName;
//        QString sMetricName = Base::MakeMetricNameFromCounterPath( sCounterPath, &eGessedType, &sInstanceName );

//        lstFinalPaths.append( sMetricName + " = " + sCounterPath );

//        int ll = sInstanceName.size();
//    }

//    QFile oFile("ayo.csv");
//    if( oFile.open(QIODevice::WriteOnly) )
//    {
//         QString sData = lstFinalPaths.join("\r\n");
//         oFile.write( sData.toLatin1() );
//         oFile.waitForBytesWritten(5000);
//    }

//    } catch( std::exception& e )
//    {
//        QString ss(e.what());
//        int kk = 5;
//    }

}

//
//  DotNetClrLocksAndThreads
//

INIT_METRIC_CHECKER(DotNetClrLocksAndThreads)
{
    AddPerformanceCounterChecker("dot_net_clr_current_logical_threads_count",  "\\.NET CLR LocksAndThreads(_Global_)\\# of current logical Threads",  EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_current_physical_threads_count", "\\.NET CLR LocksAndThreads(_Global_)\\# of current physical Threads", EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_contention_rate",                "\\.NET CLR LocksAndThreads(_Global_)\\Contention Rate / sec",         EMetricDataType::Rate,    "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_current_queue_length",           "\\.NET CLR LocksAndThreads(_Global_)\\Current Queue Length",          EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_queue_length_peak",              "\\.NET CLR LocksAndThreads(_Global_)\\Queue Length Peak",             EMetricDataType::Counter, "DotNet" );
    AddPerformanceCounterChecker("dot_net_clr_total_count_of_contentions",     "\\.NET CLR LocksAndThreads(_Global_)\\Total # of Contentions",        EMetricDataType::Counter, "DotNet" );
}

INIT_METRIC_CHECKER(DotNetClrMemory)
{
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Bytes in all Heaps",                    "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# GC Handles",                            "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Gen 0 Collections",                     "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Gen 1 Collections",                     "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Gen 2 Collections",                     "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Induced GC",                            "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# GC Handles",                            "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# of Pinned Objects",                     "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# of Sink Blocks in use",                 "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Total committed Bytes",                 "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\# Total reserved Bytes",                  "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\% Time in GC",                            "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Allocated Bytes/sec",                     "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Finalization Survivors",                  "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Gen 0 heap size",                         "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Gen 0 Promoted Bytes/Sec",                "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Gen 1 heap size",                         "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Gen 1 Promoted Bytes/Sec",                "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Gen 2 heap size",                         "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Large Object Heap size",                  "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Promoted Finalization-Memory from Gen 0", "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Promoted Memory from Gen 0",              "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Memory(_Global_)\\Promoted Memory from Gen 1",              "DotNet");
}

INIT_METRIC_CHECKER(DotNetClrRemoting)
{
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Channels"                          , "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Context Proxies"                   , "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Context-Bound Classes Loaded"      , "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Context-Bound Objects Alloc / sec" , "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Contexts"                          , "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Remote Calls/sec"                  , "DotNet");
    AddPerformanceCounterChecker("\\.NET CLR Remoting(_Global_)\\Total Remote Calls"                , "DotNet");
}

INIT_METRIC_CHECKER(DotNetAspNet)
{
    AddPerformanceCounterChecker("\\ASP.NET\\Application Restarts"              , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Applications Running"              , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Audit Failure Events Raised"       , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Audit Success Events Raised"       , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Error Events Raised"               , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Infrastructure Error Events Raised", "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Request Error Events Raised"       , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Request Execution Time"            , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Request Wait Time"                 , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Requests Current"                  , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Requests Disconnected"             , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Requests In Native Queue"          , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Requests Queued"                   , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Requests Rejected"                 , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\State Server Sessions Abandoned"   , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\State Server Sessions Active"      , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\State Server Sessions Timed Out"   , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\State Server Sessions Total"       , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Worker Process Restarts"           , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET\\Worker Processes Running"          , "ASPNet");
}

INIT_METRIC_CHECKER(DotNetAspNetApplications)
{
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\% Managed Processor Time (estimated)    ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Anonymous Requests/Sec                  ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Application Lifetime Events/Sec         ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Cache % Machine Memory Limit Used       ", "ASPNet");
    //AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Cache % Machine Memory Limit Used Base", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Cache API Entries                       ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Cache Total Hit Ratio                   ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Compilations Total                      ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Error Events Raised                     ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Errors During Compilation               ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Errors During Execution                 ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Errors Unhandled During Execution       ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Errors Unhandled During Execution/Sec   ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Events Raised/Sec                       ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Forms Authentication Success            ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Infrastructure Error Events Raised/Sec  ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Managed Memory Used (estimated)         ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Output Cache Entries                    ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Output Cache Hit Ratio                  ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Pipeline Instance Count                 ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Request Bytes In Total (WebSockets)     ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Request Bytes Out Total                 ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Request Bytes Out Total (WebSockets)    ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Request Error Events Raised/Sec         ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Request Events Raised/Sec               ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Request Execution Time                  ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Requests Executing                      ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Requests Executing (WebSockets)         ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Requests Failed (WebSockets)            ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Requests In Application Queue           ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Requests Succeeded (WebSockets)         ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Session State Server connections total  ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Sessions Active                         ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Transactions Aborted                    ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Transactions Committed                  ", "ASPNet");
    AddPerformanceCounterChecker( "\\ASP.NET Applications(__Total__)\\Transactions Total                      ", "ASPNet");
}

INIT_METRIC_CHECKER(DotNetAspNetStateService)
{
    AddPerformanceCounterChecker("\\ASP.NET State Service\\State Server Sessions Abandoned", "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET State Service\\State Server Sessions Active"   , "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET State Service\\State Server Sessions Timed Out", "ASPNet");
    AddPerformanceCounterChecker("\\ASP.NET State Service\\State Server Sessions Total"    , "ASPNet");
}
