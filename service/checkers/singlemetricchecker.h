#ifndef CSINGLEMETRICCHECKER_H
#define CSINGLEMETRICCHECKER_H

#include "metricdata.h"
#include "winperformancedataprovider.h"
#include <functional>

using MetricModifierFunc = std::function<void(MetricDataSPtr)>;



class CSingleMetricChecker
{
public:
    CSingleMetricChecker( QString const& sMetricName,
                          QString const& sCounterPath,
                          EMetricDataType eMetricDataType,
                          const QString &sMetricType,
                          WinPerformanceDataProviderSPtr pDataProvider,
                          int     nReaction = 0,
                          double  dHighValue = -1,
                          double  dSevereValue = -1,
                          QString const& sInstanceType = QString(),
                          QString const& sInstanceName = QString(),
                          MetricModifierFunc funcMetricModifier = nullptr
                         );

public:
    MetricDataSPtr CheckMetric() const;

    inline QString GetMetricName() const;
    inline QString GetInstanceType() const;
    inline QString GetInstanceName() const;

    inline void SetMetricModifierFunc( MetricModifierFunc funcModifer );

private:
    // Content
    HCOUNTER                        m_hCounter;
    QString                         m_sMetricName;
    QString                         m_sCounterPath;
    EMetricDataType                 m_eMetricDataType;
    QString                         m_sMetricType;
    int                             m_nReaction;
    WinPerformanceDataProviderSPtr  m_pDataProvider;
    double                          m_dHighValue;
    double                          m_dSevereValue;
    QString                         m_sInstanceType;
    QString                         m_sInstanceName;
    MetricModifierFunc              m_pFuncMetricModifier;
};
using SingleMetricCheckerSPtr = std::shared_ptr<CSingleMetricChecker>;

//
//  Inline implementations
//
inline QString CSingleMetricChecker::GetMetricName()   const { return m_sMetricName; }
inline QString CSingleMetricChecker::GetInstanceType() const { return m_sInstanceType; }
inline QString CSingleMetricChecker::GetInstanceName() const { return m_sInstanceName; }
inline void CSingleMetricChecker::SetMetricModifierFunc(MetricModifierFunc funcModifer) { m_pFuncMetricModifier = funcModifer; }


#endif // CSINGLEMETRICCHECKER_H
