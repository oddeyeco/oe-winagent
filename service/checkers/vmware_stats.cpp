#include "vmware_stats.h"

INIT_METRIC_CHECKER(VmwareMemoryStats, "VMware")
{
    AddPerformanceCounterChecker( "\\VMware\\Guest Locked Memory Bytes            ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Guest Virtual Physical Memory Bytes  ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Percent Guest Physical Memory Touched", "VMware");
}

INIT_METRIC_CHECKER(VmwareVirtualDiskStats, "VMware")
{
    AddPerformanceCounterChecker( "\\VMware\\Virtual Disk Bytes Read/sec       ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Virtual Disk Bytes Transferred/sec", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Virtual Disk Bytes Written/sec    ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Virtual Disk Reads/sec            ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Virtual Disk Transfers/sec        ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Virtual Disk Writes/sec           ", "VMware");
}

INIT_METRIC_CHECKER(VmwareNetworkStats, "VMware")
{
    AddPerformanceCounterChecker( "\\VMware\\Network Bytes Received/sec   ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Bytes Sent/sec       ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Bytes Transferred/sec", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Packets Received/sec ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Packets Sent/sec     ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Receive Errors/sec   ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Send Errors/sec      ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Transfer Errors/sec  ", "VMware");
    AddPerformanceCounterChecker( "\\VMware\\Network Transfers/sec        ", "VMware");
}






