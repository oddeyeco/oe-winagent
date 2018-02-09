#ifndef SYSTEM_NETWORK_STATS_CHECKER_H
#define SYSTEM_NETWORK_STATS_CHECKER_H

#include "../winperformancemetricschecker.h"

class SystemNetworkStatsChecker : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemNetworkStatsChecker)
    using Base = CWinPerformanceMetricsChecker;

public:
    SystemNetworkStatsChecker(QObject* pParent = nullptr);


    // IMetricsCategoryChecker interface
public:
    void Initialize() override;

private:
    // Helpers
    bool ContainesOneOf( QString const& sSourceString, QStringList const& lstLexems ) const;
};


REGISTER_METRIC_CHECKER( SystemNetworkStatsChecker )

#endif // SYSTEM_NETWORK_STATS_CHECKER_H
