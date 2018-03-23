#include "utilit_checkers.h"


INIT_METRIC_CHECKER(UtilityPrintQueue, "Print Queue")
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("printers", QStringList() << "total" );
    if( lstAllowedItems.contains("total", Qt::CaseInsensitive) )
    {
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Add Network Printer Calls      ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Bytes Printed/sec              ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Enumerate Network Printer Calls", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Job Errors                     ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Jobs                           ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Jobs Spooling                  ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Max Jobs Spooling              ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Max References                 ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Not Ready Errors               ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Out of Paper Errors            ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\References                     ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Total Jobs Printed             ", "Utility");
        AddPerformanceCounterChecker("\\Print Queue(_Total)\\Total Pages Printed            ", "Utility");
    }
    else
    {
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Add Network Printer Calls      ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Bytes Printed/sec              ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Enumerate Network Printer Calls", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Job Errors                     ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Jobs                           ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Jobs Spooling                  ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Max Jobs Spooling              ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Max References                 ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Not Ready Errors               ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Out of Paper Errors            ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\References                     ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Total Jobs Printed             ", "Utility", lstAllowedItems);
        AddPerformanceCounterCheckerEx("\\Print Queue(*)\\Total Pages Printed            ", "Utility", lstAllowedItems);
    }
}

INIT_METRIC_CHECKER(UtilityThermalZoneInformation, "Thermal Zone Information")
{
    QStringList lstAllowedItems = {"all"};

    AddPerformanceCounterCheckerEx("\\Thermal Zone Information(*)\\% Passive Limit           ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Thermal Zone Information(*)\\High Precision Temperature", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Thermal Zone Information(*)\\Temperature               ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\Thermal Zone Information(*)\\Throttle Reasons          ", "Utility", lstAllowedItems);
}

INIT_METRIC_CHECKER(UtilityUsb, "USB")
{
    QStringList lstAllowedItems = ConfigSection().Value<QStringList>("devices", QStringList() << "all" );

    AddPerformanceCounterCheckerEx("\\USB(*)\\% Total Bandwidth Used for Interrupt", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\% Total Bandwidth Used for Iso      ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\Avg ms latency for ISO transfers    ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\Avg. Bytes/Transfer                 ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\Interrupt Bytes/Sec                 ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\Iso Packet Errors/Sec               ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\Isochronous Bytes/Sec               ", "Utility", lstAllowedItems);
    AddPerformanceCounterCheckerEx("\\USB(*)\\Transfer Errors/Sec                 ", "Utility", lstAllowedItems);
}
