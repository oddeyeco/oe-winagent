#ifndef CCONFIGURATIONMANAGER_H
#define CCONFIGURATIONMANAGER_H

//
//  Includes
//
#include "configuration.h"
#include <QObject>

////////////////////////////////////////////////////////////////////////////////////////
///
/// singltone class CConfigurationManager
///
class CConfigurationManager : public QObject
{
    Q_OBJECT

private:
    CConfigurationManager();
public:
    static CConfigurationManager& Instance();

public:
    // Register config name that might be load (if exists)
    // Note: ConfName should not contain ".ini" extention
    void RegisterLoadableConfigs( QStringList const& lstConfigNames );
    // Reload configurations from .ini files
    void        LoadConfigurations();
    QStringList GetConfigurationsList() const;
    ConfigSPtr  GetConfiguration( QString const& sConfigName );
    QList<ConfigSPtr> GetAllConfigurations();

    CConfiguraion const& GetMainConfiguration() const;
    CConfiguraion& GetMainConfiguration();
    // clears all loaded configs
    void UnloadConfigs();

    CConfigSection GetEnabledScriptsConfigSection();
    QString GetAgentDirPath() const;
    QString GetConfigsDirPath() const;

    QSettings& GetRegistrySettings();

signals:
    void sigConfigsLoaded();
    void sigConfigsUnloaded();

private:
    // Tools
    bool LoadConfigIfExists(QString const& sConfFilePath);

private:
    // content
    QMap<QString, ConfigSPtr> m_mapConfis;

    QStringList m_lstLoadableConfigs;
    CConfigSection m_oEnabledScriptsConfSection;
    QSettings m_oRegistrySettings;

    // Constatns
    static char const* s_szConfigDirPath;
    static char const* s_szMainConfigName;
    static char const* s_szEnabledScriptsDirPath;
};

#define ConfMgr CConfigurationManager::Instance()
////////////////////////////////////////////////////////////////////////////////////////


#endif // CCONFIGURATIONMANAGER_H
