#include "metricdata.h"

CMetricData::CMetricData()
    : m_eDataType( EMetricDataType::None ),
      m_nReaction{0}
{}

CMetricData::CMetricData(const QString &sName,
                         const QVariant &vtValue,
                         EMetricDataType eDataType,
                         QDateTime oTimestamp,
                         const QString &sMetricType,
                         int nReaction,
                         QString const& sInstanceType,
                         QString const& sInstanceName )
    : m_nReaction{0}
{
    SetName( sName );
    SetValue( vtValue );
    SetDataType( eDataType );
    SetTime( oTimestamp );
    SetMetricType( sMetricType );
    SetReaction( nReaction );
    SetInstanceType( sInstanceType );
    SetInstanceType( sInstanceName );
}

MetricSeverityDescriptorSPtr CMetricData::SetSeverityDescriptor(const QString &sMetricName, EMetricDataSeverity eSeverity, double dAlertDurationHint, const QString &sMessage)
{
    auto pDescriptor = std::make_shared<CMetricSeverityDescriptor>(sMetricName,
                                                                   QDateTime::currentDateTime(),
                                                                   eSeverity,
                                                                   dAlertDurationHint,
                                                                   sMessage,
                                                                   GetInstanceType(),
                                                                   GetInstanceName()
                                                                   );
    SetSeverityDescriptor( pDescriptor );
    return pDescriptor;
}


QString ToString( EMetricDataType eType )
{
    switch (eType) {
    case EMetricDataType::Rate:     return QString( "Rate" );
    case EMetricDataType::Percent:  return QString( "Percent" );
    case EMetricDataType::Counter:  return QString( "Counter" );

    default:
        return QString( "None" );
    }
}

QString ToString(EMetricDataSeverity eType)
{
    switch (eType) {
    case EMetricDataSeverity::High:         return QString( "High" );
    case EMetricDataSeverity::Severe:       return QString( "Severe" );
    default:
        case EMetricDataSeverity::Normal:   return QString( "Normal" );
    }
}

EMetricDataType GetMetricDataTypeFromString(const QString &sDataTypeName)
{
    if( sDataTypeName.compare( "Rate", Qt::CaseInsensitive ) == 0 )
        return EMetricDataType::Rate;
    else if( sDataTypeName.compare( "Percent", Qt::CaseInsensitive ) == 0 )
        return EMetricDataType::Percent;
    else if( sDataTypeName.compare( "Counter", Qt::CaseInsensitive ) == 0 )
        return EMetricDataType::Counter;
    else
        return EMetricDataType::None;
}

CMetricSeverityDescriptor::CMetricSeverityDescriptor( const QString &sMetricName,
                                                      QDateTime oTimestamp,
                                                      EMetricDataSeverity eSeverity,
                                                      double dAlertDurationHint,
                                                      const QString &sMessage,
                                                      const QString &sInstanceType,
                                                      const QString &sInstanceName )
    : m_sName( sMetricName ),
      m_oTime( oTimestamp ),
      m_eSeverity( eSeverity ),
      m_dAlertDurationHint( dAlertDurationHint ),
      m_sMessage( sMessage ),
      m_sInstanceType( sInstanceType ),
      m_sInstanceName( sInstanceName )
{
}
