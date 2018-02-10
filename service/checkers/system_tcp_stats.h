#ifndef SystemTcpStats_H
#define SystemTcpStats_H

#include <winperformancemetricschecker.h>


class SystemTcpStats : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemTcpStats)
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemTcpStats(QObject* pParent = nullptr);


    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};



REGISTER_METRIC_CHECKER( SystemTcpStats )

#endif // SystemTcpStats_H
