#ifndef CSINGLEMETRICCHECKER_H
#define CSINGLEMETRICCHECKER_H

#include "metricdata.h"
#include "winperformancedataprovider.h"

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
                          QString const& sInstanceName = QString()
                          );

public:
    MetricDataSPtr CheckMetric() const;

    inline QString GetMetricName() const;
    inline QString GetInstanceType() const;
    inline QString GetInstanceName() const;

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
};


//
//  Inline implementations
//
QString CSingleMetricChecker::GetMetricName()   const { return m_sMetricName; }
QString CSingleMetricChecker::GetInstanceType() const { return m_sInstanceType; }
QString CSingleMetricChecker::GetInstanceName() const { return m_sInstanceName; }

using SingleMetricCheckerSPtr = std::shared_ptr<CSingleMetricChecker>;

#endif // CSINGLEMETRICCHECKER_H
