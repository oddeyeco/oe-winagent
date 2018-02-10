#include "system_tcp_stats.h"

SystemTcpStats::SystemTcpStats(QObject *pParent)
    : Base( pParent )
{}

void SystemTcpStats::Initialize()
{
    QStringList lstAllowedTcpVersions = ConfigSection().Value<QStringList>("version", QStringList() << "v4" << "v6" );
    bool bTCPv4Enabled = false;
    bool bTCPv6Enabled = false;

    for( QString& sVersion : lstAllowedTcpVersions )
    {
        if( sVersion.contains( "4" ) )
            bTCPv4Enabled = true;
        if( sVersion.contains( "6" ) )
            bTCPv6Enabled = true;
    }

    if( bTCPv4Enabled )
    {
        AddPerformanceCounterChecker("tcp_connection_failures",        "\\TCPv4\\Connection Failures",        EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_connections_active",         "\\TCPv4\\Connections Active",         EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_connections_established",    "\\TCPv4\\Connections Established",    EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_connections_passive",        "\\TCPv4\\Connections Passive",        EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_connections_reset",          "\\TCPv4\\Connections Reset",          EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_segments_received",      "\\TCPv4\\Segments Received/sec",      EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_segments_retransmitted", "\\TCPv4\\Segments Retransmitted/sec", EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_segments_sent",          "\\TCPv4\\Segments Sent/sec",          EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
        AddPerformanceCounterChecker("tcp_segments",               "\\TCPv4\\Segments/sec",               EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v4" );
    }

    if( bTCPv6Enabled )
    {
        AddPerformanceCounterChecker("tcp_connection_failures",        "\\TCPv6\\Connection Failures",        EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_connections_active",         "\\TCPv6\\Connections Active",         EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_connections_established",    "\\TCPv6\\Connections Established",    EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_connections_passive",        "\\TCPv6\\Connections Passive",        EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_connections_reset",          "\\TCPv6\\Connections Reset",          EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_segments_received",      "\\TCPv6\\Segments Received/sec",      EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_segments_retransmitted", "\\TCPv6\\Segments Retransmitted/sec", EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_segments_sent",          "\\TCPv6\\Segments Sent/sec",          EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
        AddPerformanceCounterChecker("tcp_segments",               "\\TCPv6\\Segments/sec",               EMetricDataType::Counter, "SYSTEM",0,-1,-1, "tcp_version", "v6" );
    }
}
