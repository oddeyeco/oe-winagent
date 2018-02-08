#ifndef SYSTEMTCPSTATSCHECKER_H
#define SYSTEMTCPSTATSCHECKER_H

#include <pdhmetricschecker.h>


class SystemTcpStatsChecker : public CPdhMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemTcpStatsChecker)
    using Base = CPdhMetricsChecker;

public:
    SystemTcpStatsChecker(QObject* pParent = nullptr);


    // IMetricsChecker interface
public:
    void Initialize() override;
};



REGISTER_METRIC_CHECKER( SystemTcpStatsChecker )

#endif // SYSTEMTCPSTATSCHECKER_H
