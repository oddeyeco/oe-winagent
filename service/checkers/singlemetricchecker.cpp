#include "singlemetricchecker.h"


CSingleMetricChecker::CSingleMetricChecker(QString const& sMetricName,
                                           const wchar_t *psCounterPath,
                                           EMetricDataType eMetricDataType,
                                           QString const& sMetricType,
                                           WinPerformanceDataProviderSPtr pDataProvider,
                                           int nReaction,
                                           double dHighValue,
                                           double dSevereValue)
    : m_hCounter(NULL),
      m_sMetricName(sMetricName),
      m_sCounterPath(QString::fromWCharArray( psCounterPath )),
      m_eMetricDataType(eMetricDataType),
      m_sMetricType( sMetricType ),
      m_pDataProvider(pDataProvider),
      m_nReaction( nReaction ),
      m_dHighValue( dHighValue ),
      m_dSevereValue( dSevereValue )
{    
    Q_ASSERT( !sMetricName.isEmpty() );
    Q_ASSERT( psCounterPath );
    Q_ASSERT( pDataProvider );
    Q_ASSERT( nReaction >= -3 && nReaction <=0);

    Q_ASSERT(  dHighValue == -1 || dSevereValue == -1 || dHighValue < dSevereValue );
    // TODO: Handle the case when dHighValue >= dSevereValue

//    std::unique_ptr<wchar_t[]> pCounterPath( new wchar_t[psCounterPath.length() + 1] );
//    psCounterPath.toWCharArray(pCounterPath.get());
//    pCounterPath[psCounterPath.length()] = 0;

    m_hCounter = m_pDataProvider->AddCounter( psCounterPath );
}

MetricDataSPtr CSingleMetricChecker::CheckMetric() const
{
    Q_ASSERT( m_hCounter );
    if( !m_hCounter )
        return MetricDataSPtr();

    double dVal = m_pDataProvider->GetCounterValue( m_hCounter );

    // Create metric data
    MetricDataSPtr pMetric = std::make_shared<CMetricData>();
    pMetric->SetTime( QDateTime::currentDateTime() );
    pMetric->SetName(m_sMetricName);
    pMetric->SetValue( dVal );
    pMetric->SetDataType(m_eMetricDataType);
    pMetric->SetType(m_sMetricType);
    pMetric->SetReaction(m_nReaction);

    // Set data severity
    EMetricDataSeverity eSeverity = EMetricDataSeverity::Normal;
    if( m_dSevereValue != -1 && dVal >= m_dSevereValue )
        eSeverity = EMetricDataSeverity::Severe;
    else if( m_dHighValue != -1 && dVal > m_dHighValue )
        eSeverity = EMetricDataSeverity::High;
    pMetric->SetDataSeverity( eSeverity );

    return pMetric;
}
