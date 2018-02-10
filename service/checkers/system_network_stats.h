#ifndef SYSTEM_NETWORK_STATS_CHECKER_H
#define SYSTEM_NETWORK_STATS_CHECKER_H

#include "../winperformancemetricschecker.h"

class SystemNetworkStats : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemNetworkStats)
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemNetworkStats(QObject* pParent = nullptr);


    // IMetricsCategoryChecker interface
public:
    void Initialize() override;

private:
    // Helpers
    bool ContainesOneOf( QString const& sSourceString, QStringList const& lstLexems ) const;
};


REGISTER_METRIC_CHECKER( SystemNetworkStats )

#endif // SYSTEM_NETWORK_STATS_CHECKER_H
