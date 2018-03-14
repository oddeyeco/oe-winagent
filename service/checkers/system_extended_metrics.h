#ifndef SYSTEM_EXTENDED_METRICS_H
#define SYSTEM_EXTENDED_METRICS_H

#include <winperformancemetricschecker.h>

DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemGpuAdapterMemory)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemGpuEngine)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemGpuProcessMemory)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemRemoteFXRootGPUManagement)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemRemoteFXSynth3DVSCVMDevice)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemNUMANodeMemory)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemPagingFile)
DECLARE_PERF_COUNTER_METRIC_CHECKER(SystemSecuritySystemWideStatistics)


#endif // SYSTEM_EXTENDED_METRICS_H
