#include "system_extended_metrics.h"

INIT_METRIC_CHECKER(SystemGpuAdapterMemory)
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("instances", QStringList() << "all" );
    AddPerformanceCounterCheckerEx("\\GPU Adapter Memory(*)\\Total Committed", "System", lstAllowedItems);
}

INIT_METRIC_CHECKER(SystemGpuEngine)
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("instances", QStringList() << "all" );
    AddPerformanceCounterCheckerEx("\\GPU Engine(*)\\Running Time          ", "System", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\GPU Engine(*)\\Utilization Percentage", "System", lstAllowedItems);
}

INIT_METRIC_CHECKER(SystemGpuProcessMemory)
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("instances", QStringList() << "all" );

    AddPerformanceCounterCheckerEx("\\GPU Process Memory(*)\\Dedicated Usage", "System", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\GPU Process Memory(*)\\Local Usage    ", "System", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\GPU Process Memory(*)\\Non Local Usage", "System", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\GPU Process Memory(*)\\Shared Usage   ", "System", lstAllowedItems);
}

INIT_METRIC_CHECKER(SystemRemoteFxRootGpuManagement)
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("instances", QStringList() << "all" );

    AddPerformanceCounterCheckerEx("\\RemoteFX Root GPU Management(*)\\Resources: VMs running RemoteFX", "System", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\RemoteFX Root GPU Management(*)\\VRAM: Available MB per GPU     ", "System", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\RemoteFX Root GPU Management(*)\\VRAM: Reserved % per GPU       ", "System", lstAllowedItems);
}

INIT_METRIC_CHECKER(SystemRemoteFxSynth3dVscVmDevice)
{
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSC VM Device\\Number of connected VMT channels       ", "System");
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSC VM Device\\Number of created VMT channels         ", "System");
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSC VM Device\\Number of disconnected VMT channels    ", "System");
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSC VM Device\\Number of RDVGM restarted notifications", "System");
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSC VM Device\\Number of waiting VMT channels         ", "System");
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSC VM Device\\Total number of created VMT channels   ", "System");
    AddPerformanceCounterChecker("\\RemoteFX Synth3D VSP\\Number of created VM devices                     ", "System");
}

INIT_METRIC_CHECKER(SystemNumaNodeMemory)
{
    AddPerformanceCounterChecker("\\NUMA Node Memory(_Total)\\Available MBytes            ", "System");
    AddPerformanceCounterChecker("\\NUMA Node Memory(_Total)\\Free & Zero Page List MBytes", "System");
    AddPerformanceCounterChecker("\\NUMA Node Memory(_Total)\\Standby List MBytes         ", "System");
    AddPerformanceCounterChecker("\\NUMA Node Memory(_Total)\\Total MBytes                ", "System");
}

INIT_METRIC_CHECKER(SystemPagingFile)
{
    AddPerformanceCounterChecker("\\Paging File(_Total)\\% Usage     ", "System");
    AddPerformanceCounterChecker("\\Paging File(_Total)\\% Usage Peak", "System");
}

INIT_METRIC_CHECKER(SystemSecuritySystemWideStatistics)
{
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\Active Schannel Session Cache Entries                   ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\Digest Authentications                                  ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\Forwarded Kerberos Requests                             ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC armored AS Requests                                 ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC armored TGS Requests                                ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC AS Requests                                         ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC claims-aware AS Requests                            ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC claims-aware service asserted identity TGS requests ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC claims-aware TGS Requests                           ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC classic type constrained delegation TGS Requests    ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC key trust AS Requests                               ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC resource type constrained delegation TGS Requests   ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\KDC TGS Requests                                        ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\Kerberos Authentications                                ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\NTLM Authentications                                    ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\Schannel Session Cache Entries                          ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\SSL Client-Side Full Handshakes                         ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\SSL Client-Side Reconnect Handshakes                    ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\SSL Server-Side Full Handshakes                         ", "System");
    AddPerformanceCounterChecker("\\Security System-Wide Statistics\\SSL Server-Side Reconnect Handshakes                    ", "System");
}
