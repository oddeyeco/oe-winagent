#include "system_network_stats.h"

INIT_METRIC_CHECKER(SystemNetworkStats, "Network Interface")
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
    QStringList lstAllowedInterface = ConfigSection().Value<QStringList>("interfaces", QStringList() << "all" );

    //PerformanceCounterCheckersList lstAll;

    AddPerformanceCounterCheckerEx( "network_bytes_received",          "\\Network Interface%1\\Bytes Received/sec",      EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_bytes_sent",              "\\Network Interface%1\\Bytes Sent/sec",          EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_bytes_total",             "\\Network Interface%1\\Bytes Total/sec",         EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_output_queue_length",     "\\Network Interface%1\\Output Queue Length",     EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_packets_outbound_errors", "\\Network Interface%1\\Packets Outbound Errors", EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_packets_received_errors", "\\Network Interface%1\\Packets Received Errors", EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_packets_received",        "\\Network Interface%1\\Packets Received/sec",    EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_packets_sent",            "\\Network Interface%1\\Packets Sent/sec",        EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    AddPerformanceCounterCheckerEx( "network_packets",                 "\\Network Interface%1\\Packets/sec",             EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );

    if( bDetailedEnabled )
    {
        //
        //  Add extra checkers
        //
        //lstAll.append( AddPerformanceCounterCheckerEx( "network_current_bandwidth",                "\\Network Interface%1\\Current Bandwidth",                EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "net_interface" ) );
        AddPerformanceCounterCheckerEx( "network_offloaded_connections",            "\\Network Interface%1\\Offloaded Connections",            EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_outbound_discarded",       "\\Network Interface%1\\Packets Outbound Discarded",       EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_received_discarded",       "\\Network Interface%1\\Packets Received Discarded",       EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_received_non-unicast",     "\\Network Interface%1\\Packets Received Non-Unicast/sec", EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_received_unicast",         "\\Network Interface%1\\Packets Received Unicast/sec",     EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_received_unknown",         "\\Network Interface%1\\Packets Received Unknown",         EMetricDataType::Counter, "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_sent_non-unicast",         "\\Network Interface%1\\Packets Sent Non-Unicast/sec",     EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
        AddPerformanceCounterCheckerEx( "network_packets_sent_unicast",             "\\Network Interface%1\\Packets Sent Unicast/sec",         EMetricDataType::Rate,    "SYSTEM", 0,-1,-1, bPerInterfaceEnabled, "Network Interface", "network_interface", nullptr, lstAllowedInterface );
    }


    //
    //  Check is network interface filter specified and remove not matching checkers
    //

//    if( lstAllowedInterface.contains("all", Qt::CaseInsensitive) )
//        // All Interfaces - No Filter
//        return;

//    // decl lambda
//    auto lmContainesOneOf = [](const QString &sSourceString, const QStringList &lstLexems)
//                            {
//                                for( QString const& sLex : lstLexems )
//                                    if( sSourceString.contains(sLex, Qt::CaseInsensitive) )
//                                        return true;
//                                return false;
//                            };

//    for( PerformanceCounterCheckerSPtr pCurrentChecker : lstAll )
//    {
//        if(  !lmContainesOneOf( pCurrentChecker->GetInstanceName(), lstAllowedInterface ) )
//        {
//            // remove checker
//            Base::RemoveMetricChecker( pCurrentChecker );
//        }
//    }

}
