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
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\1G device pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\1G GPA pages                     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\2M device pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\2M GPA pages                     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\4K device pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\4K GPA pages                     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Address Spaces                   ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Attached Devices                 ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Deposited Pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Device DMA Errors                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Device Interrupt Errors          ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Device Interrupt Mappings        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Device Interrupt Throttle Events ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\GPA Pages                        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\GPA Space Modifications/sec      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\I/O TLB Flush Cost               ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\I/O TLB Flushes/sec              ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Nested TLB Free List Size        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Nested TLB Size                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Nested TLB Trimmed Pages/sec     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Recommended Nested TLB Size      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Recommended Virtual TLB Size     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Skipped Timer Ticks              ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Virtual Processors               ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Virtual TLB Flush Entires/sec    ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total_)\\Virtual TLB Pages                ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisorRootVirtualProcessor)
{
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\% Hypervisor Run Time                            ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\% Remote Run Time                                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\% Total Run Time                                 ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\Total Virtualization Instructions Emulated/sec   ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\Total Virtualization Instructions Emulation Cost ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\Virtual Interrupt Hypercalls/sec                 ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\Virtual Interrupts/sec                           ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\Virtual MMU Hypercalls/sec                       ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total_)\\Virtual Processor Hypercalls/sec                 ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualMachineBus)
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Bus\\Interrupts Received/sec", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Bus\\Interrupts Sent/sec    ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Bus\\Throttle Events        ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualMachineHealthSummary)
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Health Summary\\Health Critical", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Health Summary\\Health Ok      ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualNetworkAdapter)
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Network Adapter(_Total_)\\Bytes Received/sec                     ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Network Adapter(_Total_)\\Dropped Packets Incoming/sec           ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Network Adapter(_Total_)\\Extensions Dropped Packets Outgoing/sec", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Network Adapter(_Total_)\\IPsec offload Bytes Sent/sec           ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualStorageDevice)
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Error Count                  ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Flush Count                  ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Latency                      ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Lower Latency                ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Lower Queue Length           ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Maximum Adapter Worker Count ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Maximum Bandwidth            ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Maximum IO Rate              ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Minimum IO Rate              ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Read Count                   ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Throughput                   ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Storage Device(_Total_)\\Write Count                  ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualSwitch)
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Broadcast Packets Sent/sec             ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Dropped Packets Outgoing/sec           ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Extensions Dropped Packets Incoming/sec", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Learned Mac Addresses                  ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Learned Mac Addresses/sec              ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Multicast Packets Sent/sec             ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Number of Send Channel Moves/sec       ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Number of VMQ Moves/sec                ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Packets Flooded                        ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Packets Flooded/sec                    ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Packets Received/sec                   ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Packets/sec                            ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Purged Mac Addresses                   ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Switch(_Total_)\\Purged Mac Addresses/sec               ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVmVidNumaNode)
{
    AddPerformanceCounterChecker("\\Hyper-V VM Vid Numa Node(_Total_)\\PageCount     ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V VM Vid Numa Node(_Total_)\\ProcessorCount", "HyperV");
}
