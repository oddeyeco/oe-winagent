#ifndef HYPER_V_H
#define HYPER_V_H

#include <winperformancemetricschecker.h>

DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVDynamicMemoryBalancer)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVHypervisor)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVHypervisorLogicalProcessor)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVHypervisorRootPartition)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVHypervisorRootVirtualProcessor)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVVirtualMachineBus)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVVirtualMachineHealthSummary)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVVirtualNetworkAdapter)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVVirtualStorageDevice)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVVirtualSwitch)
DECLARE_PERF_COUNTER_METRIC_CHECKER(HyperVVMVidNumaNode)

#endif // HYPER_V_H
