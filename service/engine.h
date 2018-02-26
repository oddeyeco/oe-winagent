#ifndef CENGINE_H
#define CENGINE_H

#include "imetricscategorychecker.h"
#include "message.h"
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
    int  GetUpdateInterval() const;

    void AddChecker( IMetricsCategoryCheckerSPtr pChecker );
    void RemoveChecker( IMetricsCategoryCheckerSPtr pChecker );
    void RemoveAllCheckers();

    int  GetLastMetricsCount()  const;

public:
    bool IsStarted();

signals:
    void sigMetricsCollected( MetricDataList const& lstAllMetrics );
    void sigNotify( CMessage const& oMessage );

private slots:
    void onTimerTik();

private:
    void CollectMetrics();

private:
    // Content
    QTimer*                                m_pTimer;
    std::set<IMetricsCategoryCheckerSPtr>  m_setCheckers;
    WinPerformanceDataProviderSPtr         m_pDataProvider;
    int                                    m_nLastMetricsCount;
};
////////////////////////////////////////////////////////////////////////////////////////

#endif // CENGINE_H
