#include "system_network_stats_checker.h"

SystemNetworkStatsChecker::SystemNetworkStatsChecker(QObject *pParent)
    : Base(pParent)
{
}

void SystemNetworkStatsChecker::Initialize()
{
//    double dConfHighVal = -1;
//    double dConfSevereVal = -1;

//    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
//    if( bStaticAlertingEnabled )
//    {
//        dConfHighVal   = ConfigSection().Value<double>("high", -1);
//        dConfSevereVal = ConfigSection().Value<double>("severe", -1);
//    }

    //! No Static Alerting

    bool bDetailedEnabled =  ConfigSection().Value<bool>("detailed_stats", false);
    bool bPerInterfaceEnabled = true;

    SingleMetricCheckersList lstAll;

    lstAll.append( AddCounterMetricChecker( "network_bytes_received/sec",      "\\Network Interface%1\\Bytes Received/sec",      EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_bytes_sent/sec",          "\\Network Interface%1\\Bytes Sent/sec",          EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_bytes_total/sec",         "\\Network Interface%1\\Bytes Total/sec",         EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_output_queue_length",     "\\Network Interface%1\\Output Queue Length",     EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_packets_outbound_errors", "\\Network Interface%1\\Packets Outbound Errors", EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_packets_received_errors", "\\Network Interface%1\\Packets Received Errors", EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_packets_received/sec",    "\\Network Interface%1\\Packets Received/sec",    EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_packets_sent/sec",        "\\Network Interface%1\\Packets Sent/sec",        EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    lstAll.append( AddCounterMetricChecker( "network_packets/sec",             "\\Network Interface%1\\Packets/sec",             EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );

    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //
        lstAll.append( AddCounterMetricChecker( "network_current_bandwidth",                "\\Network Interface%1\\Current Bandwidth",                EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_offloaded_connections",            "\\Network Interface%1\\Offloaded Connections",            EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_outbound_discarded",       "\\Network Interface%1\\Packets Outbound Discarded",       EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_received_discarded",       "\\Network Interface%1\\Packets Received Discarded",       EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_received_non-unicast/sec", "\\Network Interface%1\\Packets Received Non-Unicast/sec", EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_received_unicast/sec",     "\\Network Interface%1\\Packets Received Unicast/sec",     EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_received_unknown",         "\\Network Interface%1\\Packets Received Unknown",         EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_sent_non-unicast/sec",     "\\Network Interface%1\\Packets Sent Non-Unicast/sec",     EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
        lstAll.append( AddCounterMetricChecker( "network_packets_sent_unicast/sec",         "\\Network Interface%1\\Packets Sent Unicast/sec",         EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "Interface" ) );
    }


    //
    //  Check is network interface filter specified and remove not matching checkers
    //

    QStringList lstAllowedInterface = ConfigSection().Value<QStringList>("interfaces", QStringList() << "all" );
    if( lstAllowedInterface.contains("all", Qt::CaseInsensitive) )
        // All Interfaces - No Filter
        return;

    for( SingleMetricCheckerSPtr pCurrentChecker : lstAll )
    {
        if(  !ContainesOneOf( pCurrentChecker->GetInstanceName(), lstAllowedInterface ) )
        {
            // remove checker
            Base::RemoveSingleMetricChecker( pCurrentChecker );
        }
    }

}

bool SystemNetworkStatsChecker::ContainesOneOf(const QString &sSourceString, const QStringList &lstLexems) const
{
    for( QString const& sLex : lstLexems )
    {
        if( sSourceString.contains(sLex, Qt::CaseInsensitive) )
            return true;
    }

    return false;
}

