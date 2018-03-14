#include "sql_server.h"

INIT_METRIC_CHECKER(SqlServerAccessMethods)
{
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\Forwarded Records/sec  ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\FreeSpace Scans/sec    ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\Full Scans/sec         ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\Index Searches/sec     ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\Page Deallocations/sec ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\Page Splits/sec        ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Access Methods\\Pages Allocated/sec    ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerAvailabilityReplica)
{
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Bytes Received from Replica/sec", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Bytes Sent to Replica/sec      ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Bytes Sent to Transport/sec    ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Flow Control Time (ms/sec)     ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Flow Control/sec               ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Receives from Replica/sec      ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Resent Messages/sec            ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Sends to Replica/sec           ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Availability Replica(_Total)\\Sends to Transport/sec         ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerBufferManager)
{
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Background writer pages/sec", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Buffer cache hit ratio     ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Checkpoint pages/sec       ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Database pages             ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Free list stalls/sec       ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Integral Controller Slope  ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Lazy writes/sec            ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Page life expectancy       ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Page lookups/sec           ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Page reads/sec             ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Page writes/sec            ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Readahead pages/sec        ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Buffer Manager\\Target pages               ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerBufferNode)
{
    // All instances
    AddPerformanceCounterCheckerEx( "\\SQLServer:Buffer Node(*)\\Database pages             ", "SQLServer", QStringList() << "all");
    AddPerformanceCounterCheckerEx( "\\SQLServer:Buffer Node(*)\\Local node page lookups/sec", "SQLServer", QStringList() << "all");
    AddPerformanceCounterCheckerEx( "\\SQLServer:Buffer Node(*)\\Page life expectancy       ", "SQLServer", QStringList() << "all");
}

INIT_METRIC_CHECKER(SqlServerClr)
{
    AddPerformanceCounterChecker("\\SQLServer:CLR\\CLR Execution", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerDatabaseReplica)
{
    AddPerformanceCounterChecker("\\SQLServer:Database Replica(_Total)\\File Bytes Received/sec", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Database Replica(_Total)\\Log Bytes Received/sec ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Database Replica(_Total)\\Log Send Queue         ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Database Replica(_Total)\\Transaction Delay      ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerDatabases)
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("databases", QStringList() << "total" );
    if( lstAllowedItems.contains("total", Qt::CaseInsensitive) )
    {
        AddPerformanceCounterChecker("\\SQLServer:Databases(_Total)\\Active Transactions          ", "SQLServer");
        AddPerformanceCounterChecker("\\SQLServer:Databases(_Total)\\Backup/Restore Throughput/sec", "SQLServer");
        AddPerformanceCounterChecker("\\SQLServer:Databases(_Total)\\Transactions/sec             ", "SQLServer");
    }
    else
    {
        AddPerformanceCounterCheckerEx("\\SQLServer:Databases(*)\\Active Transactions          ", "SQLServer", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\SQLServer:Databases(*)\\Backup/Restore Throughput/sec", "SQLServer", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\SQLServer:Databases(*)\\Transactions/sec             ", "SQLServer", lstAllowedItems);
    }
}

INIT_METRIC_CHECKER(SqlServerGeneralStatistics)
{
    AddPerformanceCounterChecker("\\SQLServer:General Statistics\\Logins/sec                      ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:General Statistics\\Logouts/sec                     ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:General Statistics\\Processes blocked               ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:General Statistics\\SQL Trace IO Provider Lock Waits", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:General Statistics\\Transactions                    ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:General Statistics\\User Connections                ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerLocks)
{
    AddPerformanceCounterChecker("\\SQLServer:Locks(_Total)\\Average Wait Time (ms)         ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Locks(_Total)\\Lock Requests/sec              ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Locks(_Total)\\Lock Timeouts (timeout > 0)/sec", "SQLServer", "sqlserver_locks_lock_timeouts");
    AddPerformanceCounterChecker("\\SQLServer:Locks(_Total)\\Lock Waits/sec                 ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Locks(_Total)\\Number of Deadlocks/sec        ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerMemoryManager)
{
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Database Cache Memory (KB) ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Free Memory (KB)           ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Lock Blocks                ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Lock Memory (KB)           ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Optimizer Memory (KB)      ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Reserved Server Memory (KB)", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\SQL Cache Memory (KB)      ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Target Server Memory (KB)  ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Memory Manager\\Total Server Memory (KB)   ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerPlanCache)
{
    AddPerformanceCounterChecker("\\SQLServer:Plan Cache(_Total)\\Cache Object Counts ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Plan Cache(_Total)\\Cache Objects in use", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Plan Cache(_Total)\\Cache Pages         ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerQueryExecution)
{
    AddPerformanceCounterChecker("\\SQLServer:Query Execution\\Local data access/sec     ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Query Execution\\Rem Req Cache Hit Ratio   ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Query Execution\\Remote requests/sec       ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Query Execution\\Remote resend requests/sec", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerSqlErrors)
{
    AddPerformanceCounterChecker("\\SQLServer:SQL Errors(_Total)\\Errors/sec", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerSqlStatistics)
{
    AddPerformanceCounterChecker("\\SQLServer:SQL Statistics\\Batch Requests/sec     ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:SQL Statistics\\SQL Compilations/sec   ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:SQL Statistics\\SQL Re-Compilations/sec", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerTransactions)
{
    AddPerformanceCounterChecker("\\SQLServer:Transactions\\Free Space in tempdb (KB)       ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Transactions\\Longest Transaction Running Time", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Transactions\\Snapshot Transactions           ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Transactions\\Transactions                    ", "SQLServer");
    AddPerformanceCounterChecker("\\SQLServer:Transactions\\Update conflict ratio           ", "SQLServer");
}

INIT_METRIC_CHECKER(SqlServerUserSettable)
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("counters", QStringList() << "all" );
    AddPerformanceCounterCheckerEx("\\SQLServer:User Settable(*)\\Query", "SQLServer", lstAllowedItems);
}

INIT_METRIC_CHECKER(SqlServerWaitStatistics)
{
    QStringList lstFilter = QStringList() << "Average";

    AddPerformanceCounterCheckerEx("\\SQLServer:Wait Statistics(*)\\Lock waits              ", "SQLServer", lstFilter);
    AddPerformanceCounterCheckerEx("\\SQLServer:Wait Statistics(*)\\Log buffer waits        ", "SQLServer", lstFilter);
    AddPerformanceCounterCheckerEx("\\SQLServer:Wait Statistics(*)\\Log write waits         ", "SQLServer", lstFilter);
    AddPerformanceCounterCheckerEx("\\SQLServer:Wait Statistics(*)\\Memory grant queue waits", "SQLServer", lstFilter);
    AddPerformanceCounterCheckerEx("\\SQLServer:Wait Statistics(*)\\Network IO waits        ", "SQLServer", lstFilter);
}
