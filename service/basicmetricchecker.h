#ifndef BASICMETRICCHECKER_H
#define BASICMETRICCHECKER_H

#include "imetricchecker.h"
#include <functional>

using ValueCheckerFunc = std::function<double(void)>;

////////////////////////////////////////////////////////////////////////////////////////////
///
/// class CBasicMetricChecker
/// Implemets IMetricChecker and provides basic interface for metric data finalization
class CBasicMetricChecker : public IMetricChecker
{
    using Base = IMetricChecker;

public:
    CBasicMetricChecker( QString const& sMetricName,
                         EMetricDataType eMetricDataType,
                         const QString &sMetricType,
                         int     nReaction            =  0,
                         double  dHighValue           = -1,
                         double  dSevereValue         = -1,
                         QString const& sInstanceType = QString(),
                         QString const& sInstanceName = QString()  );

public:
    // IMetricChecker interface
    MetricDataSPtr CheckMetric() override;

    // Own Interface
    inline QString GetMetricName() const;
    inline QString GetInstanceType() const;
    inline QString GetInstanceName() const;
    inline void SetInstanceName( QString const& sName );

    inline void SetValueCheckerFunction( ValueCheckerFunc pFunc );

protected:
    virtual double CheckMetricValue();

private:
    //
    //  Content
    //
    QString          m_sMetricName;
    EMetricDataType  m_eMetricDataType;
    QString          m_sMetricType;
    int              m_nReaction;
    double           m_dHighValue;
    double           m_dSevereValue;
    QString          m_sInstanceType;
    QString          m_sInstanceName;
    ValueCheckerFunc m_pValueCheckerFunc;
    bool             m_bWereLastValueHighOrSevery;
};

using BasicMetricCheckerSPtr = std::shared_ptr<CBasicMetricChecker>;
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
///
/// Inline Implementations
///
////////////////////////////////////////////////////////////////////////////////////////////
inline QString CBasicMetricChecker::GetMetricName()   const               { return m_sMetricName; }
inline QString CBasicMetricChecker::GetInstanceType() const               { return m_sInstanceType; }
inline QString CBasicMetricChecker::GetInstanceName() const               { return m_sInstanceName; }
inline void    CBasicMetricChecker::SetInstanceName(const QString &sName) { m_sInstanceName = sName; }

inline void CBasicMetricChecker::SetValueCheckerFunction(ValueCheckerFunc pFunc) { m_pValueCheckerFunc = pFunc; }

#endif // BASICMETRICCHECKER_H
