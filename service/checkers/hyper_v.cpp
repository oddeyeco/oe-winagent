#include "hyper_v.h"

INIT_METRIC_CHECKER(HyperVDynamicMemoryBalancer, "Hyper-V Dynamic Memory Balancer")
{
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Balancer(System Balancer)\\Available Memory                 ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Balancer(System Balancer)\\Average Pressure                 ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Balancer(System Balancer)\\System Current Pressure          ", "HyperV");

    //AddPerformanceCounterChecker("\\Hyper-V Dynamic Memory Integration Service\\Maximum Memory, Mbytes"                 , "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisor, "Hyper-V Hypervisor")
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

INIT_METRIC_CHECKER(HyperVHypervisorLogicalProcessor, "Hyper-V Hypervisor Logical Processor")
{
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\% C2 Time                           ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\% Guest Run Time                    ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\% of Max Frequency                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\C1 Transitions/sec                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Hardware Interrupts/sec             ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Inter-Processor Interrupts Sent/sec ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Inter-Processor Interrupts/sec      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Monitor Transition Cost             ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Parking Status                      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Root Vp Index                       ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Scheduler Interrupts/sec            ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Timer Interrupts/sec                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Logical Processor(_Total)\\Total Interrupts/sec                ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisorRootPartition, "Hyper-V Hypervisor Root Partition")
{
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\1G device pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\1G GPA pages                     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\2M device pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\2M GPA pages                     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\4K device pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\4K GPA pages                     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Address Spaces                   ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Attached Devices                 ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Deposited Pages                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Device DMA Errors                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Device Interrupt Errors          ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Device Interrupt Mappings        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Device Interrupt Throttle Events ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\GPA Pages                        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\GPA Space Modifications/sec      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\I/O TLB Flush Cost               ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\I/O TLB Flushes/sec              ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Nested TLB Free List Size        ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Nested TLB Size                  ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Nested TLB Trimmed Pages/sec     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Recommended Nested TLB Size      ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Recommended Virtual TLB Size     ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Skipped Timer Ticks              ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Virtual Processors               ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Virtual TLB Flush Entires/sec    ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Partition(_Total)\\Virtual TLB Pages                ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVHypervisorRootVirtualProcessor, Hyper-V Hypervisor Root Virtual Processor)
{
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\% Hypervisor Run Time                            ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\% Remote Run Time                                ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\% Total Run Time                                 ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\Total Virtualization Instructions Emulated/sec   ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\Total Virtualization Instructions Emulation Cost ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\Virtual Interrupt Hypercalls/sec                 ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\Virtual Interrupts/sec                           ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\Virtual MMU Hypercalls/sec                       ", "HyperV");
    AddPerformanceCounterChecker( "\\Hyper-V Hypervisor Root Virtual Processor(_Total)\\Virtual Processor Hypercalls/sec                 ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualMachineBus, "Hyper-V Virtual Machine Bus")
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Bus\\Interrupts Received/sec", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Bus\\Interrupts Sent/sec    ", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Bus\\Throttle Events        ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualMachineHealthSummary, "Hyper-V Virtual Machine Health Summary")
{
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Health Summary\\Health Critical", "HyperV");
    AddPerformanceCounterChecker("\\Hyper-V Virtual Machine Health Summary\\Health Ok      ", "HyperV");
}

INIT_METRIC_CHECKER(HyperVVirtualNetworkAdapter, "Hyper-V Virtual Network Adapter")
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("adapters", QStringList() << "all" );

    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Network Adapter(*)\\Bytes Received/sec                     ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Network Adapter(*)\\Dropped Packets Incoming/sec           ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Network Adapter(*)\\Extensions Dropped Packets Outgoing/sec", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Network Adapter(*)\\IPsec offload Bytes Sent/sec           ", "HyperV", lstAllowedItems);
}

INIT_METRIC_CHECKER(HyperVVirtualStorageDevice, "Hyper-V Virtual Storage Device")
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("storages", QStringList() << "all" );

    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Error Count                  ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Flush Count                  ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Latency                      ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Lower Latency                ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Lower Queue Length           ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Maximum Adapter Worker Count ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Maximum Bandwidth            ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Maximum IO Rate              ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Minimum IO Rate              ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Read Count                   ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Throughput                   ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Storage Device(*)\\Write Count                  ", "HyperV", lstAllowedItems);
}

INIT_METRIC_CHECKER(HyperVVirtualSwitch, "Hyper-V Virtual Switch")
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("switches", QStringList() << "all" );

    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Broadcast Packets Sent/sec             ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Dropped Packets Outgoing/sec           ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Extensions Dropped Packets Incoming/sec", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Learned Mac Addresses                  ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Learned Mac Addresses/sec              ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Multicast Packets Sent/sec             ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Number of Send Channel Moves/sec       ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Number of VMQ Moves/sec                ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Packets Flooded                        ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Packets Flooded/sec                    ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Packets Received/sec                   ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Packets/sec                            ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Purged Mac Addresses                   ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V Virtual Switch(*)\\Purged Mac Addresses/sec               ", "HyperV", lstAllowedItems);
}

INIT_METRIC_CHECKER(HyperVVmVidNumaNode, "Hyper-V VM Vid Numa Node")
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("instances", QStringList() << "all" );
    AddPerformanceCounterCheckerEx("\\Hyper-V VM Vid Numa Node(*)\\PageCount     ", "HyperV", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Hyper-V VM Vid Numa Node(*)\\ProcessorCount", "HyperV", lstAllowedItems);
}
