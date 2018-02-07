#include "singlemetricchecker.h"


CSingleMetricChecker::CSingleMetricChecker(QString const& sMetricName,
                                           const QString & sCounterPath,
                                           EMetricDataType eMetricDataType,
                                           QString const& sMetricType,
                                           WinPerformanceDataProviderSPtr pDataProvider,
                                           int nReaction,
                                           double dHighValue,
                                           double dSevereValue,
                                           const QString &sInstanceType,
                                           const QString &sInstanceName)
    : m_hCounter(NULL),
      m_sMetricName(sMetricName),
      m_sCounterPath( sCounterPath ),
      m_eMetricDataType(eMetricDataType),
      m_sMetricType( sMetricType ),
      m_pDataProvider(pDataProvider),
      m_nReaction( nReaction ),
      m_dHighValue( dHighValue ),
      m_dSevereValue( dSevereValue ),
      m_sInstanceType( sInstanceType ),
      m_sInstanceName( sInstanceName )
{    
    Q_ASSERT( !sMetricName.isEmpty() );
    Q_ASSERT( !sCounterPath.isEmpty() );
    Q_ASSERT( pDataProvider );
    Q_ASSERT( nReaction >= -3 && nReaction <=0);

    Q_ASSERT(  dHighValue == -1 || dSevereValue == -1 || dHighValue < dSevereValue );
    // TODO: Handle the case when dHighValue >= dSevereValue

    // convert qstring to wchar_t
    m_hCounter = m_pDataProvider->AddCounter( CWinPerformanceDataProvider::ToWCharArray( sCounterPath ).get() );
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

    if( !m_sInstanceType.isEmpty() && !m_sInstanceName.isEmpty() )
    {
        pMetric->SetInstanceType( m_sInstanceType );
        pMetric->SetInstanceName( m_sInstanceName );
    }

    // Set data severity
    EMetricDataSeverity eSeverity = EMetricDataSeverity::Normal;
    if( m_dSevereValue != -1 && dVal >= m_dSevereValue )
        eSeverity = EMetricDataSeverity::Severe;
    else if( m_dHighValue != -1 && dVal > m_dHighValue )
        eSeverity = EMetricDataSeverity::High;
    pMetric->SetDataSeverity( eSeverity );

    return pMetric;
}
