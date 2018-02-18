#ifndef METRICSGROUPCHECKER_H
#define METRICSGROUPCHECKER_H

#include "imetricscategorychecker.h"
#include "imetricchecker.h"

using MetricCheckersList = QList<IMetricCheckerSPtr>;

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// class CMetricsGroupChecker
/// Containes multiple IMetricChecker's group and provides metrics category checking
/// by collecting metrig data from each IMetricChecker
class CMetricsGroupChecker : public IMetricsCategoryChecker
{
    using Base = IMetricsCategoryChecker;

public:
    CMetricsGroupChecker(QObject* pParent = nullptr);

public:
    // IMetricsCategoryChecker interface
    MetricDataList CheckMetrics() override;

    // Own Interface
    void AddMetricChecker( IMetricCheckerSPtr pMetricChecker );
    void RemoveMetricChecker( IMetricCheckerSPtr pMetricChecker );

private:
    //
    //  Content
    //
    MetricCheckersList m_lstMetricCheckers;
};
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // METRICSGROUPCHECKER_H
