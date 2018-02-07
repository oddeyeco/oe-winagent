#include "../pdhmetricschecker.h"


class SystemCpuStatsChecker : public CPdhMetricsChecker
{
    DECLARE_MERTIC_CHECKER( SystemCpuStatsChecker )
    using Base = CPdhMetricsChecker;

public:
    SystemCpuStatsChecker(QObject *pParent = nullptr);

    // IMetricsChecker interface
public:
    void Initialize();
};


REGISTER_METRIC_CHECKER(SystemCpuStatsChecker)
