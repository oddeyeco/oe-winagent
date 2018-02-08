#ifndef SYSTEM_NETWORK_STATS_CHECKER_H
#define SYSTEM_NETWORK_STATS_CHECKER_H

#include "../pdhmetricschecker.h"

class SystemNetworkStatsChecker : public CPdhMetricsChecker
{
    DECLARE_MERTIC_CHECKER(SystemNetworkStatsChecker)
    using Base = CPdhMetricsChecker;

public:
    SystemNetworkStatsChecker(QObject* pParent = nullptr);


    // IMetricsChecker interface
public:
    void Initialize() override;

private:
    // Helpers
    bool ContainesOneOf( QString const& sSourceString, QStringList const& lstLexems ) const;
};


REGISTER_METRIC_CHECKER( SystemNetworkStatsChecker )

#endif // SYSTEM_NETWORK_STATS_CHECKER_H
