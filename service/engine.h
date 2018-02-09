#ifndef CENGINE_H
#define CENGINE_H

#include "imetricscategorychecker.h"
#include "winperformancedataprovider.h"
// Qt
#include <QObject>
#include <QTimer>
#include <set>

////////////////////////////////////////////////////////////////////////////////////////
///
/// class CEngine
///
/// Performs periodical updates regarding with configurations,
/// collects metric date and passes to Send Controller
///
class CEngine : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    CEngine(QObject* pParent = nullptr);

public slots:
    void Start();
    void Stop();
    void SetUpdateInterval(int nMsecs);

    void AddChecker( IMetricsCategoryCheckerSPtr pChecker );
    void RemoveChecker( IMetricsCategoryCheckerSPtr pChecker );
    void RemoveAllCheckers();

signals:
    void sigMetricsCollected( MetricDataList const& lstAllMetrics );

private slots:
    void onTimerTik();

private:
    void CollectMetrics();

private:
    // Content
    QTimer*                        m_pTimer;
    std::set<IMetricsCategoryCheckerSPtr>  m_setCheckers;
    WinPerformanceDataProviderSPtr m_pDataProvider;
};

using EngineSPtr = std::shared_ptr<CEngine>;
////////////////////////////////////////////////////////////////////////////////////////

#endif // CENGINE_H
