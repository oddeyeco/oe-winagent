#include "imetricschecker.h"

IMetricsChecker::IMetricsChecker(QObject *pParent)
    : Base( pParent )
{
}

void IMetricsChecker::SetConfigSection(const CConfigSection &oConfig)
{
    m_oConfigSection = oConfig;
}

void IMetricsChecker::SetPerformanceDataProvider(WinPerformanceDataProviderSPtr pDataProvider)
{
    m_pDataProvider = pDataProvider;
}

void IMetricsChecker::Initialize()
{
    // nothing to do
}
