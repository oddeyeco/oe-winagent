#include "imetricscategorychecker.h"

IMetricsCategoryChecker::IMetricsCategoryChecker(QObject *pParent)
    : Base( pParent )
{
}

void IMetricsCategoryChecker::SetConfigSection(const CConfigSection &oConfig)
{
    m_oConfigSection = oConfig;
}

void IMetricsCategoryChecker::SetPerformanceDataProvider(WinPerformanceDataProviderSPtr pDataProvider)
{
    m_pDataProvider = pDataProvider;
}

void IMetricsCategoryChecker::Initialize()
{
    // nothing to do
}
