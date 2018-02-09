#ifndef CPERFORMANCECOUNTERCHECKER_H
#define CPERFORMANCECOUNTERCHECKER_H

#include "../basicmetricchecker.h"
#include "winperformancedataprovider.h"
#include <functional>

using ValueModifierFunc = std::function<void(double&)>;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// class CPerformanceCounterChecker
///
class CPerformanceCounterChecker : public CBasicMetricChecker
{
    using Base = CBasicMetricChecker;

public:
    CPerformanceCounterChecker( QString const&  sMetricName,
                                QString const&  sCounterPath,
                                EMetricDataType eMetricDataType,
                                const QString & sMetricType,
                                WinPerformanceDataProviderSPtr pDataProvider,
                                int     nReaction = 0,
                                double  dHighValue = -1,
                                double  dSevereValue = -1,
                                QString const& sInstanceType = QString(),
                                QString const& sInstanceName = QString(),
                                ValueModifierFunc funcMetricModifier = nullptr
                              );

    ~CPerformanceCounterChecker();

public:
    inline void SetValueModifierFunc( ValueModifierFunc funcModifer );

    // CBasicMetricChecker interface
protected:
    double CheckMetricValue() override;

private:
    // Content
    QString                        m_sCounterPath;
    HCOUNTER                       m_hCounter;
    WinPerformanceDataProviderSPtr m_pDataProvider;
    ValueModifierFunc              m_pFuncMetricModifier;
};
using PerformanceCounterCheckerSPtr = std::shared_ptr<CPerformanceCounterChecker>;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  Inline implementations
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void CPerformanceCounterChecker::SetValueModifierFunc( ValueModifierFunc funcModifer ) { m_pFuncMetricModifier = funcModifer; }

#endif // CPERFORMANCECOUNTERCHECKER_H
