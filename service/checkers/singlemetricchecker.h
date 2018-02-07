#ifndef CSINGLEMETRICCHECKER_H
#define CSINGLEMETRICCHECKER_H

#include "metricdata.h"
#include "winperformancedataprovider.h"

class CSingleMetricChecker
{
public:
    CSingleMetricChecker(QString const& sMetricName,
                          wchar_t const* psCounterPath,
                          EMetricDataType eMetricDataType,
                          const QString &sMetricType,
                          WinPerformanceDataProviderSPtr pDataProvider,
                          int     nReaction = 0,
                          double  dHighValue = -1,
                          double  dSevereValue = -1
                          );

public:
    MetricDataSPtr CheckMetric() const;

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
};

using SingleMetricCheckerSPtr = std::shared_ptr<CSingleMetricChecker>;

#endif // CSINGLEMETRICCHECKER_H
