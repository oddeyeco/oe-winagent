#ifndef CMETRICDATA_H
#define CMETRICDATA_H

#include <QDateTime>
#include <QVariant>
#include <memory>


enum class EMetricDataType
{
    None = 0,
    Rate,
    Percent,
    Counter
};

enum class EMetricDataSeverity
{
    Normal = 0,
    High,
    Severe
};

QString ToString( EMetricDataType eType );
QString ToString( EMetricDataSeverity eType );
EMetricDataType GetMetricDataTypeFromString( QString const& sDataTypeName );

////////////////////////////////////////////////////////////////////////////////////////
///
/// class CMetricSeverityDescriptor [OE Special metric]
///
class CMetricSeverityDescriptor
{
public:
    CMetricSeverityDescriptor( QString const& sMetricName,
                               QDateTime oTimestamp,
                               EMetricDataSeverity eSeverity,
                               double dAlertDurationHint = 0,
                               QString const& sMessage = QString(),
                               QString const& sInstanceType = QString(),
                               QString const& sInstanceName = QString()
                               );

public:
    inline void SetMetricName(QString const& sName);
    inline QString GetMetricName() const;

    inline void SetAlertDurationHint(double dValue);
    inline double GetAlertDurationHint() const;

    inline void SetTime(QDateTime const& oTime);
    inline QDateTime GetTime() const;

    inline void SetDataSeverity( EMetricDataSeverity eSeverity );
    inline EMetricDataSeverity GetDataSeverity() const;

    // metric instance info like core name, disk name, etc..
    inline void SetInstanceType(QString const& sType);
    inline QString GetInstanceType() const;

    inline void SetInstanceName(QString const& sInstanceName);
    inline QString GetInstanceName() const;

    inline void SetMessage( QString const& sMessage );
    inline QString GetMessage() const;

private:
    // Content
    QString         m_sName;
    double          m_dAlertDurationHint;
    QDateTime       m_oTime;
    EMetricDataSeverity m_eSeverity;
    QString         m_sMessage;
    QString         m_sInstanceType;
    QString         m_sInstanceName;
};

using MetricSeverityDescriptorSPtr = std::shared_ptr<CMetricSeverityDescriptor>;
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
///
/// class CMetricData
///
class CMetricData
{
public:
    CMetricData();
    CMetricData(QString const& sName,
                QVariant const& vtValue,
                EMetricDataType eDataType,
                QDateTime oTimestamp,
                QString const& sMetricType,
                int nReaction = 0,
                QString const& sInstanceType = QString(),
                QString const& sInstanceName = QString()
                );

public:
    inline void SetName(QString const& sName);
    inline QString GetName() const;

    inline void SetDataType(EMetricDataType eDataType);
    inline void SetDataType(QString const&  sDataType);
    inline EMetricDataType GetDataType() const;

    inline void SetValue(QVariant const& vtValue);
    inline QVariant GetValue() const;

    inline void SetTime(QDateTime const& oTime);
    inline QDateTime GetTime() const;

    inline void SetReaction(int nReaction );
    inline int GetReaction() const;

    inline void SetMetricType(QString const& sType);
    inline QString GetMetricType() const;

    // metric instance info like core name, disk name, etc..
    inline void SetInstanceType(QString const& sType);
    inline QString GetInstanceType() const;

    inline void SetInstanceName(QString const& sInstanceName);
    inline QString GetInstanceName() const;

    inline bool HasSeverityDescriptor() const;
    inline void SetSeverityDescriptor( MetricSeverityDescriptorSPtr pDescriptor );
    MetricSeverityDescriptorSPtr SetSeverityDescriptor( QString const& sMetricName,
                                                        EMetricDataSeverity eSeverity,
                                                        double dAlertDurationHint = 0,
                                                        QString const& sMessage = QString());
    inline MetricSeverityDescriptorSPtr GetSeverityDescriptor() const;

    inline bool IsNull() const;

private:
    // Content
    QString         m_sName;
    EMetricDataType m_eDataType;
    QVariant        m_vtValue;
    QDateTime       m_oTime;
    QString         m_sType;
    int             m_nReaction;
    QString         m_sInstanceType;
    QString         m_sInstanceName;

    MetricSeverityDescriptorSPtr m_pSeverityDescriptor;
};
using MetricDataSPtr = std::shared_ptr<CMetricData>;
using MetricDataList = QList<MetricDataSPtr>;
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
///
/// inline implementations
///
////////////////////////////////////////////////////////////////////////////////////////

//
//  class CMetricSeverityDescriptor
//
inline void CMetricSeverityDescriptor::SetMetricName(const QString &sName) { m_sName = sName; }
inline QString CMetricSeverityDescriptor::GetMetricName() const { return m_sName; }
inline void CMetricSeverityDescriptor::SetAlertDurationHint(double dValue) { m_dAlertDurationHint = dValue; }
inline double CMetricSeverityDescriptor::GetAlertDurationHint() const { return m_dAlertDurationHint; }
inline void CMetricSeverityDescriptor::SetTime(const QDateTime &oTime) { m_oTime = oTime; }
inline QDateTime CMetricSeverityDescriptor::GetTime() const { return m_oTime; }
inline void CMetricSeverityDescriptor::SetDataSeverity(EMetricDataSeverity eSeverity) { m_eSeverity = eSeverity; }
inline EMetricDataSeverity CMetricSeverityDescriptor::GetDataSeverity() const { return m_eSeverity; }
inline void CMetricSeverityDescriptor::SetInstanceType(const QString &sType) { m_sInstanceType = sType; }
inline QString CMetricSeverityDescriptor::GetInstanceType() const { return m_sInstanceType; }
inline void CMetricSeverityDescriptor::SetInstanceName(const QString &sInstanceName) { m_sInstanceName = sInstanceName; }
inline QString CMetricSeverityDescriptor::GetInstanceName() const { return m_sInstanceName; }
inline void CMetricSeverityDescriptor::SetMessage(const QString &sMessage) { m_sMessage = sMessage; }
inline QString CMetricSeverityDescriptor::GetMessage() const { return m_sMessage; }

//
//  class CMetricData
//
inline void CMetricData::SetName(QString const& sName) { Q_ASSERT(!sName.isEmpty()); m_sName = sName; }
inline QString CMetricData::GetName() const { return m_sName; }
inline void CMetricData::SetDataType(EMetricDataType eDataType) { m_eDataType = eDataType; }
inline void CMetricData::SetDataType(const QString &sDataType) { SetDataType( GetMetricDataTypeFromString( sDataType ) ); }
inline EMetricDataType CMetricData::GetDataType() const { return m_eDataType; }
inline void CMetricData::SetValue(QVariant const& vtValue) { m_vtValue = vtValue; }
inline QVariant CMetricData::GetValue() const { return m_vtValue; }
inline void CMetricData::SetTime(QDateTime const& oTime) { m_oTime = oTime; }
inline QDateTime CMetricData::GetTime() const { return m_oTime; }
inline void CMetricData::SetReaction(int nReaction ) { Q_ASSERT(nReaction >= -3 && nReaction <= 0); m_nReaction = nReaction; }
inline int CMetricData::GetReaction() const { return m_nReaction; }
inline void CMetricData::SetMetricType(const QString &sType) { Q_ASSERT(!sType.isEmpty()); m_sType = sType; }
inline QString CMetricData::GetMetricType() const { return m_sType; }
inline void CMetricData::SetInstanceType(const QString &sType) {  m_sInstanceType = sType; }
inline QString CMetricData::GetInstanceType() const { return m_sInstanceType; }
inline void CMetricData::SetInstanceName(const QString &sInstanceName) { m_sInstanceName = sInstanceName; }
inline QString CMetricData::GetInstanceName() const { return m_sInstanceName; }
inline bool CMetricData::HasSeverityDescriptor() const { return m_pSeverityDescriptor != nullptr; }
inline void CMetricData::SetSeverityDescriptor(MetricSeverityDescriptorSPtr pDescriptor) { m_pSeverityDescriptor = pDescriptor; }
inline MetricSeverityDescriptorSPtr CMetricData::GetSeverityDescriptor() const { return m_pSeverityDescriptor; }
inline bool CMetricData::IsNull() const { return m_sName.isNull(); }

#endif // CMETRICDATA_H
