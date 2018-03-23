#ifndef VMWARE_STATS_H
#define VMWARE_STATS_H

#include <winperformancemetricschecker.h>

DECLARE_PERF_COUNTER_METRIC_CHECKER(VmwareMemoryStats)
DECLARE_PERF_COUNTER_METRIC_CHECKER(VmwareVirtualDiskStats)
DECLARE_PERF_COUNTER_METRIC_CHECKER(VmwareNetworkStats)

#endif // VMWARE_STATS_H
