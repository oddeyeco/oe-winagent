#ifndef SCRIPTSMETRICSCHECKER_H
#define SCRIPTSMETRICSCHECKER_H

#include "imetricscategorychecker.h"
// Qt

class QProcess;

class CScriptsMetricsChecker : public IMetricsCategoryChecker
{
    Q_OBJECT
    using Base = IMetricsCategoryChecker;

public:
    CScriptsMetricsChecker(QObject* pParent = nullptr);
    ~CScriptsMetricsChecker();

    // IMetricsCategoryChecker interface
public:
    MetricDataList CheckMetrics();

private:
    // helpers
    MetricDataList GetScriptFileResults( QString const& sSrcoptFilePath );

private:
    std::unique_ptr<QProcess> m_pProcess;
};

#endif // SCRIPTSMETRICSCHECKER_H
