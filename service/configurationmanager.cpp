#include "configurationmanager.h"
#include "commonexceptions.h"
// Qt
#include <QDir>

// static member initialization
char const* CConfigurationManager::s_szConfigDirPath = "conf/";
char const* CConfigurationManager::s_szMainConfigName= "conf";

CConfigurationManager::CConfigurationManager()
{}

CConfigurationManager &CConfigurationManager::Instance()
{
    static CConfigurationManager oInst;
    return oInst;
}

void CConfigurationManager::RegisterLoadableConfigs(QStringList const& lstConfigNames)
{
    Q_ASSERT(!lstConfigNames.isEmpty());
    for( auto& sName : lstConfigNames)
    {
        Q_ASSERT(!sName.isEmpty());
        if( !m_lstLoadableConfigs.contains( sName ) )
            m_lstLoadableConfigs.append(sName);
    }
}

void CConfigurationManager::LoadConfigurations()
{
    UnloadConfigs();

    QDir oConfigDir( s_szConfigDirPath );
    if( !oConfigDir.exists() )
        throw CConfigLoadFailedException( "Configuration directory not found" );

    // Load Main Config
    QString sMainConfigPath = oConfigDir.filePath( s_szMainConfigName + QLatin1String(".ini"));
    if( !LoadConfigIfExists( sMainConfigPath ) )
        throw CConfigLoadFailedException( QString("Main configuration file not found (%1.ini)").arg(s_szMainConfigName) );

    // Load "loadable" configs
    for( auto sConfigName : m_lstLoadableConfigs )
    {
        QString sConfigPath = oConfigDir.filePath( sConfigName + ".ini");
        LoadConfigIfExists(sConfigPath);
    }

    // Notify [unused]
    emit sigConfigsLoaded();
}

QStringList CConfigurationManager::GetConfigurationsList() const
{
    return m_mapConfis.keys();
}

ConfigSPtr CConfigurationManager::GetConfiguration(const QString &sConfigName)
{
    return m_mapConfis.value(sConfigName, nullptr);
}

QList<ConfigSPtr> CConfigurationManager::GetAllConfigurations()
{
    return m_mapConfis.values();
}

const CConfiguraion &CConfigurationManager::GetMainConfiguration() const
{
    ConfigSPtr const& pMainConf = m_mapConfis.value(s_szMainConfigName);
    if( !pMainConf )
    {
        throw CInvalidConfigException("Main configuration is missing");
    }
    return *pMainConf;
}

CConfiguraion &CConfigurationManager::GetMainConfiguration()
{
    ConfigSPtr const& pMainConf = m_mapConfis.value(s_szMainConfigName);
    if( !pMainConf )
    {
        throw CInvalidConfigException("Main configuration is missing");
    }
    return *pMainConf;
}

void CConfigurationManager::UnloadConfigs()
{
    // Delete existing configs
    m_mapConfis.clear();
    emit sigConfigsUnloaded();
}

bool CConfigurationManager::LoadConfigIfExists(const QString &sConfFilePath)
{
    if( sConfFilePath.isEmpty() )
        return false;

    QFile oConfFile( sConfFilePath );
    if( oConfFile.exists() )
    {
        // create config object
        ConfigSPtr pConfig = std::make_shared<CConfiguraion>( sConfFilePath );
        // store config
        QString sConfName = pConfig->GetName();
        Q_ASSERT(!sConfName.isEmpty());
        m_mapConfis.insert( sConfName, pConfig );

        return true;
    }

    return false;
}
