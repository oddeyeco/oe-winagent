#include "configuration.h"
#include "configurationmanager.h"

#include <QFileInfo>
#include <QDebug>

CConfiguraion::CConfiguraion(const QString &sIniFileName)
    : Base( sIniFileName, Base::IniFormat )
{
}

QString CConfiguraion::GetName() const
{
    QString sName = QFileInfo( Base::fileName() ).baseName();
    return sName;
}

CConfigSection CConfiguraion::GetSection(const QString &sSectionName)
{
    CConfigSection oRes( GetName() );

    beginGroup( sSectionName );
    QStringList lstSectionKeys = Base::childKeys();
    for( auto& sKey : lstSectionKeys )
    {
        oRes.insert( sKey, Base::value(sKey) );
    }
    endGroup();

    return oRes;
}

QString CConfiguraion::GetValueAsPath(const QString &sKey, const QString &sDefaultVal)
{
    QString sPath = Value<QString>( sKey, sDefaultVal );
    sPath.replace("\\", "/");

    if( sPath.startsWith( "\\" ) || sPath.startsWith("/") )
        sPath.prepend( ConfMgr.GetAgentDirPath() );

    return sPath;

}

QStringList CConfiguraion::GetAllSectionNames() const
{
    return Base::childGroups();
}
