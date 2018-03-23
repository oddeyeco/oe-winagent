#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//
//  Includes
//
#include <QSettings>
#include <memory>
#include <commonexceptions.h>

// Forward declarations
class CConfigSection;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// class CConfiguraion
///
class CConfiguraion : public QSettings
{
    using Base = QSettings;

public:
    CConfiguraion( QString const& sIniFileName );

public:
    QString GetName() const;
    QStringList GetAllSectionNames() const;
    CConfigSection GetSection( QString const& sSectionName );
    CConfigSection GetRootSection();

    template <typename T>
    T Value( QString const& sKey );
    template <typename T>
    T Value( QString const& sKey, T const& tDefaultVal );

    QString GetValueAsPath( QString const& sKey, QString const& sDefaultVal );
};
// usefull type definitions
using ConfigSPtr = std::shared_ptr<CConfiguraion>;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// class CConfigSection
///
class CConfigSection : public QHash<QString, QVariant>
{
    using Base = QHash<QString, QVariant>;
public:
    CConfigSection(QString const& sParentConfigName = QString()) : m_sParentConfigName(sParentConfigName)
    {}

public:
    template <typename T>
    T Value( QString const& sKey, T const& tDefaultVal );
    template <typename T>
    T Value( QString const& sKey );

    inline QString GetParentConfigName();
    inline void SetParentConfigName(QString const& sName);

private:
    QString m_sParentConfigName;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Inline Implementations
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T CConfigSection::Value(const QString &sKey, T const& tDefaultVal )
{
    QVariant vtVal = Base::value(sKey, QVariant( tDefaultVal ));
    if( !vtVal.convert( qMetaTypeId<T>()) )
    {
        QString sInfo = sKey + "=" + Base::value(sKey, QVariant( tDefaultVal )).toString()
                + " : " + GetParentConfigName() + ".ini";
        throw CInvalidConfigValueException(sInfo);
    }
    return vtVal.value<T>();
}

template <typename T>
T CConfigSection::Value(const QString &sKey )
{
    if( Base::find( sKey ) == this->end() )
        throw CConfigValueMissingException( sKey );

    QVariant vtVal = Base::value(sKey);
    if( !vtVal.convert( qMetaTypeId<T>()) )
    {
        QString sInfo = sKey + "=" + Base::value(sKey).toString()
                + " : " + GetParentConfigName() + ".ini";
        throw CInvalidConfigValueException(sInfo);
    }
    return vtVal.value<T>();
}

inline QString CConfigSection::GetParentConfigName() { return m_sParentConfigName; }
inline void    CConfigSection::SetParentConfigName(const QString &sName) { m_sParentConfigName = sName; }


//
//  class CConfiguraion
//
template<typename T>
T CConfiguraion::Value(const QString &sKey)
{
    if( !Base::contains( sKey ) )
        throw CConfigValueMissingException( sKey );

    QVariant vtVal = Base::value(sKey);
    if( !vtVal.convert( qMetaTypeId<T>()) )
    {
        QString sInfo = sKey + "=" + Base::value(sKey).toString()
                + " : " + GetName() + ".ini";
        throw CInvalidConfigValueException(sInfo);
    }
    return vtVal.value<T>();
}

template <typename T>
T CConfiguraion::Value(const QString &sKey, T const& tDefaultVal )
{
    QVariant vtVal = Base::value(sKey, QVariant( tDefaultVal ));
    if( !vtVal.convert( qMetaTypeId<T>()) )
    {
        QString sInfo = sKey + "=" + Base::value(sKey, QVariant( tDefaultVal )).toString()
                + " : " + GetName() + ".ini";
        throw CInvalidConfigValueException(sInfo);
    }
    return vtVal.value<T>();
}
#endif // CONFIGURATION_H
