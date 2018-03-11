#include "hyper_v.h"

INIT_METRIC_CHECKER(HyperVDynamicMemoryBalancer)
{
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Balancer(_Total_)\\Available Memory                 ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Balancer(_Total_)\\Average Pressure                 ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Balancer(_Total_)\\System Current Pressure          ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Integration Service\\Maximum Memory, Mbytes", "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisor)
{
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\HypervisorStartupCost     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Logical Processors        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Modern Standby Entries    ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Monitored Notifications   ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Partitions                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Platform Idle Transitions ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Total Pages               ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor\\Virtual Processors        ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisorLogicalProcessor)
{
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\% C2 Time                           ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\% Guest Run Time                    ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\% of Max Frequency                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\C1 Transitions/sec                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Hardware Interrupts/sec             ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Inter-Processor Interrupts Sent/sec ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Inter-Processor Interrupts/sec      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Monitor Transition Cost             ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Parking Status                      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Root Vp Index                       ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Scheduler Interrupts/sec            ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Timer Interrupts/sec                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total_)\\Total Interrupts/sec                ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisorRootPartition)
{

}

INIT_METRIC_CHECKER(HyperVHypervisorRootVirtualProcessor)   {}
INIT_METRIC_CHECKER(HyperVVirtualMachineBus)                {}
INIT_METRIC_CHECKER(HyperVVirtualMachineHealthSummary)      {}
INIT_METRIC_CHECKER(HyperVVirtualNetworkAdapter)            {}
INIT_METRIC_CHECKER(HyperVVirtualStorageDevice)             {}
INIT_METRIC_CHECKER(HyperVVirtualSwitch)                    {}
INIT_METRIC_CHECKER(HyperVVMVidNumaNode)                    {}
