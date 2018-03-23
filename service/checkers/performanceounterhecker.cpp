#include "performanceounterhecker.h"
#include "commonexceptions.h"

CPerformanceCounterChecker::CPerformanceCounterChecker(QString const& sMetricName,
                                                       const QString & sCounterPath,
                                                       EMetricDataType eMetricDataType,
                                                       QString const& sMetricType,
                                                       WinPerformanceDataProviderSPtr pDataProvider,
                                                       int nReaction,
                                                       double dHighValue,
                                                       double dSevereValue,
                                                       const QString &sInstanceType,
                                                       const QString &sInstanceName,
                                                       ValueModifierFunc funcMetricModifier )
    : Base( sMetricName, eMetricDataType, sMetricType, nReaction, dHighValue, dSevereValue, sInstanceType, sInstanceName ),
      m_hCounter( NULL ),
      m_sCounterPath( sCounterPath ),
      m_pDataProvider( pDataProvider ),
      m_pFuncMetricModifier( funcMetricModifier )
{    
    Q_ASSERT( !sCounterPath.isEmpty() );
    Q_ASSERT( pDataProvider );
    // convert qstring to wchar_t
    try
    {
        m_hCounter = m_pDataProvider->AddCounter( CWinPerformanceDataProvider::ToWCharArray( sCounterPath ).get() );
    }
    catch(std::exception& e)
    {
        // rethrow
        throw CFailedToAddCounterException( e.what(), sMetricName, sCounterPath, sInstanceType, sInstanceName );
    }
}

CPerformanceCounterChecker::~CPerformanceCounterChecker()
{
    Q_ASSERT( m_pDataProvider );
    m_pDataProvider->RemoveCounter( m_hCounter );
}

double CPerformanceCounterChecker::CheckMetricValue()
{
    Q_ASSERT( m_hCounter );

    double dVal = m_pDataProvider->GetCounterValue( m_hCounter );

    // Check if custom modifier function is set
    if( m_pFuncMetricModifier )
    {
        m_pFuncMetricModifier( dVal );
    }

    return dVal;
}
