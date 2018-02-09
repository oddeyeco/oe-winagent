#include "metricdata.h"

CMetricData::CMetricData()
    : m_eDataType( EMetricDataType::None ),
      m_nReaction{0},
      m_eSeverity( EMetricDataSeverity::Normal )
{}

CMetricData::CMetricData(const QString &sName,
                         const QVariant &vtValue,
                         EMetricDataType eDataType,
                         QDateTime oTimestamp,
                         const QString &sMetricType,
                         int nReaction,
                         EMetricDataSeverity eSeverity,
                         QString const& sInstanceType,
                         QString const& sInstanceName )
    : m_nReaction{0}
{
    SetName(sName);
    SetValue(vtValue);
    SetDataType(eDataType);
    SetTime(oTimestamp);
    SetType( sMetricType );
    SetReaction(nReaction);
    SetDataSeverity( eSeverity );
    SetInstanceType(sInstanceType);
    SetInstanceType(sInstanceName);
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
