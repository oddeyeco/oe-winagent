#ifndef SYSTEMTCPSTATSCHECKER_H
#define SYSTEMTCPSTATSCHECKER_H

#include <winperformancemetricschecker.h>


class SystemTcpStatsChecker : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemTcpStatsChecker)
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemTcpStatsChecker(QObject* pParent = nullptr);


    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};



REGISTER_METRIC_CHECKER( SystemTcpStatsChecker )

#endif // SYSTEMTCPSTATSCHECKER_H
