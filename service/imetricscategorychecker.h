#ifndef IMETRICSCHECKER_H
#define IMETRICSCHECKER_H

#include <QObject>
#include "metricdata.h"
#include "configuration.h"
#include "winperformancedataprovider.h"
#include "macros.h"
#include "logger.h"

////////////////////////////////////////////////////////////////////////////////////////
///
/// Interface IMetricsChecker
///
/// Base class for all metric checkers
///
class IMetricsChecker : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    explicit IMetricsChecker(QObject* pParent = nullptr);

public:
    virtual void SetConfigSection( CConfigSection const& oConfig );
    void    SetPerformanceDataProvider( WinPerformanceDataProviderSPtr pDataProvider );

    virtual void Initialize();
    virtual MetricDataList CheckMetrics() = 0;

protected:
    // accessors
    inline CConfigSection&  ConfigSection();
    inline CConfigSection const& ConfigSection() const;

    inline WinPerformanceDataProviderSPtr  PerfDataProvider();
    inline WinPerformanceDataProviderConstSPtr PerfDataProvider() const;

private:
    // Content
    CConfigSection m_oConfigSection;
    WinPerformanceDataProviderSPtr m_pDataProvider;
};
using IMetricsCheckerSPtr = std::shared_ptr<IMetricsChecker>;
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
/// inline implementations
CConfigSection       &IMetricsChecker::ConfigSection()      { return m_oConfigSection; }
const CConfigSection &IMetricsChecker::ConfigSection()const { return m_oConfigSection; }

WinPerformanceDataProviderSPtr      IMetricsChecker::PerfDataProvider()       { return m_pDataProvider; }
WinPerformanceDataProviderConstSPtr IMetricsChecker::PerfDataProvider() const { return m_pDataProvider; }
////////////////////////////////////////////////////////////////////////////////////////

#endif // IMETRICSCHECKER_H
