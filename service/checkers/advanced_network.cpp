#include "advanced_network.h"

INIT_METRIC_CHECKER(AdvancedNetworkDns64Global, "DNS64 Global")
{
    AddPerformanceCounterChecker("\\DNS64 Global(Default)\\AAAA - Synthesized records", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\DNS64 Global(Default)\\AAAA queries - Failed     ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\DNS64 Global(Default)\\AAAA queries - Successful ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\DNS64 Global(Default)\\IP6.ARPA queries - Matched", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\DNS64 Global(Default)\\Other queries - Failed    ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\DNS64 Global(Default)\\Other queries - Successful", "AdvancedNetwork");
}

INIT_METRIC_CHECKER(AdvancedNetworkIphttpsGlobal, "IPHTTPS Global")
{
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Drops - Neighbor resolution timeouts  ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Errors - Authentication Errors        ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Errors - Receive errors on the server ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Errors - Transmit errors on the server", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\In - Total bytes received             ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\In - Total packets received           ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Out - Total bytes forwarded           ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Out - Total bytes sent                ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Out - Total packets sent              ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\IPHTTPS Global(Default)\\Sessions - Total sessions             ", "AdvancedNetwork");
}

INIT_METRIC_CHECKER(AdvancedNetworkSmbServer, "SMB Server")
{
    AddPerformanceCounterChecker("\\SMB Server\\Read Bytes/sec    ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server\\Read Requests/sec ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server\\Receive Bytes/sec ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server\\Send Bytes/sec    ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server\\Write Bytes/sec   ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server\\Write Requests/sec", "AdvancedNetwork");
}

INIT_METRIC_CHECKER(AdvancedNetworkSmbServerShares, "SMB Server Shares")
{
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\% Persistent Handles   ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\% Resilient Handles    ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. Bytes/Read        ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. Bytes/Write       ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. Data Bytes/Request", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. Data Queue Length ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. Read Queue Length ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. sec/Data Request  ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. sec/Read          ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. sec/Request       ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. sec/Write         ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\SMB Server Shares(_Total)\\Avg. Write Queue Length", "AdvancedNetwork");
}

INIT_METRIC_CHECKER(AdvancedNetworkTerminalServices, "Terminal Services")
{
    AddPerformanceCounterChecker("\\Terminal Services\\Active Sessions  ", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\Terminal Services\\Inactive Sessions", "AdvancedNetwork");
    AddPerformanceCounterChecker("\\Terminal Services\\Total Sessions   ", "AdvancedNetwork");
}
