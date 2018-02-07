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
                EMetricDataSeverity eSeverity = EMetricDataSeverity::Normal,
                QString const& sInstanceType = QString(),
                QString const& sInstanceName = QString()
                );

public:
    inline void SetName(QString const& sName);
    inline QString GetName() const;

    inline void SetDataType(EMetricDataType eDataType);
    inline EMetricDataType GetDataType() const;

    inline void SetValue(QVariant const& vtValue);
    inline QVariant GetValue() const;

    inline void SetTime(QDateTime const& oTime);
    inline QDateTime GetTime() const;

    inline void SetReaction(int nReaction );
    inline int GetReaction() const;

    inline void SetDataSeverity( EMetricDataSeverity eSeverity );
    inline EMetricDataSeverity GetDataSeverity() const;

    inline void SetType(QString const& sType);
    inline QString GetType() const;

    // metric instance info like core name, disk name, etc..
    inline void SetInstanceType(QString const& sType);
    inline QString GetInstanceType() const;

    inline void SetInstanceName(QString const& sInstanceName);
    inline QString GetInstanceName() const;



    inline bool IsNull() const;

private:
    // Content
    QString         m_sName;
    EMetricDataType m_eDataType;
    QVariant        m_vtValue;
    QDateTime       m_oTime;
    QString         m_sType;
    int             m_nReaction;
    EMetricDataSeverity m_eSeverity;
    QString         m_sInstanceType;
    QString         m_sInstanceName;
};

using MetricDataSPtr = std::shared_ptr<CMetricData>;
using MetricDataList = QList<MetricDataSPtr>;
////////////////////////////////////////////////////////////////////////////////////////


// inline implementations
inline void CMetricData::SetName(QString const& sName) { Q_ASSERT(!sName.isEmpty()); m_sName = sName; }
inline QString CMetricData::GetName() const { return m_sName; }

inline void CMetricData::SetDataType(EMetricDataType eDataType) { m_eDataType = eDataType; }
inline EMetricDataType CMetricData::GetDataType() const { return m_eDataType; }

inline void CMetricData::SetValue(QVariant const& vtValue) { m_vtValue = vtValue; }
inline QVariant CMetricData::GetValue() const { return m_vtValue; }

inline void CMetricData::SetTime(QDateTime const& oTime) { m_oTime = oTime; }
inline QDateTime CMetricData::GetTime() const { return m_oTime; }

inline void CMetricData::SetReaction(int nReaction ) { Q_ASSERT(nReaction >= -3 && nReaction <= 0); m_nReaction = nReaction; }
inline int CMetricData::GetReaction() const { return m_nReaction; }

inline void CMetricData::SetDataSeverity(EMetricDataSeverity eSeverity) { m_eSeverity = eSeverity; }
inline EMetricDataSeverity CMetricData::GetDataSeverity() const { return m_eSeverity; }

inline void CMetricData::SetType(const QString &sType) { Q_ASSERT(!sType.isEmpty()); m_sType = sType; }
inline QString CMetricData::GetType() const { return m_sType; }

inline void CMetricData::SetInstanceType(const QString &sType) {  m_sInstanceType = sType; }
inline QString CMetricData::GetInstanceType() const { return m_sInstanceType; }
inline void CMetricData::SetInstanceName(const QString &sInstanceName) { m_sInstanceName = sInstanceName; }
inline QString CMetricData::GetInstanceName() const { return m_sInstanceName; }

bool CMetricData::IsNull()          const { return m_sName.isNull(); }

#endif // CMETRICDATA_H
