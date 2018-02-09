#ifndef IMETRICCHECKER_H
#define IMETRICCHECKER_H

#include "metricdata.h"

/////////////////////////////////////////////////////////////////////////////////////
///
/// Single metric checking base interface
///
class IMetricChecker
{
public:
    IMetricChecker();
    virtual ~IMetricChecker() = default;

public:
    //
    //  Main Interface
    //
    virtual MetricDataSPtr CheckMetric() = 0;
};

using IMetricCheckerSPtr = std::shared_ptr<IMetricChecker>;
/////////////////////////////////////////////////////////////////////////////////////

#endif // IMETRICCHECKER_H
