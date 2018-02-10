#ifndef ODDEYESELFCHECK_H
#define ODDEYESELFCHECK_H

#include "metricsgroupchecker.h"


class OddeyeSelfCheck : public CMetricsGroupChecker
{
    DECLARE_MERTIC_CHECKER(OddeyeSelfCheck)
    using Base = CMetricsGroupChecker;

public:
    OddeyeSelfCheck( QObject* pParent = nullptr );

    // IMetricsCategoryChecker interface
public:
    void Initialize() override;

private:
    // Content
    QString m_sOddEyeAddress;
};

REGISTER_METRIC_CHECKER( OddeyeSelfCheck )

#endif // ODDEYESELFCHECK_H
