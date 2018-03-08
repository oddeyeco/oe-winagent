#ifndef DOTNETCLRJIT_H
#define DOTNETCLRJIT_H

#include <winperformancemetricschecker.h>

// Jit
class DotNetClrJit : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(DotNetClrJit)
    using Base = CWinPerformanceMetricsChecker;

public:
    DotNetClrJit(QObject* pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};

// LocksAndThreads
class DotNetClrLocksAndThreads : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(DotNetClrLocksAndThreads)
    using Base = CWinPerformanceMetricsChecker;

public:
    DotNetClrLocksAndThreads(QObject* pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};

// Memory
class DotNetClrMemory : public CWinPerformanceMetricsChecker
{
    DECLARE_MERTIC_CHECKER(DotNetClrMemory)
    using Base = CWinPerformanceMetricsChecker;

public:
    DotNetClrMemory(QObject* pParent = nullptr);

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;
};


REGISTER_METRIC_CHECKER( DotNetClrJit )
REGISTER_METRIC_CHECKER( DotNetClrLocksAndThreads )
REGISTER_METRIC_CHECKER( DotNetClrMemory )

#endif // DOTNETCLRJIT_H
