#ifndef IMETRICSCATEGORYCHECKER_H
#define IMETRICSCATEGORYCHECKER_H

#include <QObject>
#include "metricdata.h"
#include "configurationmanager.h"
#include "winperformancedataprovider.h"
#include "macros.h"
#include "logger.h"

////////////////////////////////////////////////////////////////////////////////////////
///
/// Interface IMetricsCategoryChecker
///
/// Base class for all category metric checkers
///
class IMetricsCategoryChecker : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    explicit IMetricsCategoryChecker(QObject* pParent = nullptr);
    virtual  ~IMetricsCategoryChecker() = default;

public:
    virtual void Initialize();
    virtual MetricDataList CheckMetrics() = 0;

    virtual void SetConfigSection( CConfigSection const& oConfig );
            void SetPerformanceDataProvider( WinPerformanceDataProviderSPtr pDataProvider );

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
using IMetricsCategoryCheckerSPtr = std::shared_ptr<IMetricsCategoryChecker>;
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
/// inline implementations
CConfigSection       &IMetricsCategoryChecker::ConfigSection()      { return m_oConfigSection; }
const CConfigSection &IMetricsCategoryChecker::ConfigSection()const { return m_oConfigSection; }

WinPerformanceDataProviderSPtr      IMetricsCategoryChecker::PerfDataProvider()       { return m_pDataProvider; }
WinPerformanceDataProviderConstSPtr IMetricsCategoryChecker::PerfDataProvider() const { return m_pDataProvider; }
////////////////////////////////////////////////////////////////////////////////////////

#endif // IMETRICSCATEGORYCHECKER_H
