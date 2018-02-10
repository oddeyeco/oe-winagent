#include "agentinitializer.h"
#include "configurationmanager.h"
#include "checkers/scriptsmetricschecker.h"
#include "logger.h"

#include <QDebug>

void CAgentInitialzier::InitializeLogger()
{
    // log_rotate_seconds
    qint64 nLogRotateSeconds = ConfMgr.GetMainConfiguration().Value<qint64>("SelfConfig/log_rotate_seconds", 3600);
    Logger::getInstance().setLogRotateSeconds( nLogRotateSeconds );

    // log_rotate_backups
    int nBackupLogFilesCount = ConfMgr.GetMainConfiguration().Value<int>("SelfConfig/log_rotate_backups", 24);
    Logger::getInstance().setBackupFileCount( nBackupLogFilesCount );

    if( nLogRotateSeconds <= 0  || nBackupLogFilesCount <= 0)
        LOG_ERROR("Logging disabled");

    // log_dir
    QString sLogsDirPath = ConfMgr.GetMainConfiguration().Value<QString>( "SelfConfig/log_dir" );
    if( sLogsDirPath.isEmpty() )
    {
        throw CInvalidConfigValueException( "log_dir is empty" );
    }
    Logger::getInstance().setLogsFolderPath( sLogsDirPath );

    bool bDebugLoggingEnabled = ConfMgr.GetMainConfiguration().Value<bool>( "SelfConfig/debug_log", false );
    Logger::getInstance().SetDebugLoggingEnabled( bDebugLoggingEnabled );
}

void CAgentInitialzier::InitializeEngine(CEngine *pEngine)
{
    if( !pEngine )
    {
        Q_ASSERT(false);
        return;
    }
    LOG_INFO( "OE engine init started" );

    // Setup Main Settings
    double dUpdateSecs = ConfMgr.GetMainConfiguration().Value<double>("SelfConfig/check_period_seconds", 1);
    int nMsec = static_cast<int>( dUpdateSecs * 1000 );
    pEngine->SetUpdateInterval( nMsec );

    LOG_INFO( "Check period is: " + std::to_string(int(dUpdateSecs)) + " sec" );

    auto lstAllConfigs = ConfMgr.GetAllConfigurations();
    for( ConfigSPtr& pCurrentConfig : lstAllConfigs  )
    {
        Q_ASSERT(pCurrentConfig);
        if( !pCurrentConfig )
            continue;
        // skip if main config
        if( pCurrentConfig.get() == &ConfMgr.GetMainConfiguration() )
            continue;

        // Create checkers for specified sections
        QStringList lstSections = pCurrentConfig->GetAllSectionNames();
        for( QString sSectionName : lstSections )
        {
            // Check if checker enabled or not
            QString sEnabledProp = QString("%1/enabled").arg(sSectionName);
            bool bIsEnabled = pCurrentConfig->value( sEnabledProp, QVariant(true) ).toBool();

            if( bIsEnabled )
            {
                IMetricsCategoryCheckerSPtr pChecker = CreateCheckerByConfigName( pCurrentConfig->GetName(),
                                                                                  sSectionName );
                QString sCheckerName = MakeCheckerName( pCurrentConfig->GetName(), sSectionName );
                if( pChecker )
                {
                    LOG_INFO( "Checker loaded: " + sCheckerName.toStdString() );
                    pChecker->metaObject()->className();

                    // Pass config section to checker
                    auto&& oSection = pCurrentConfig->GetSection(sSectionName);
                    pChecker->SetConfigSection( oSection );

                    pEngine->AddChecker(pChecker);
                }
                else
                {
                    LOG_INFO( "Checker NOT found: " + sCheckerName.toStdString() );
                    qDebug() << "Checker NOT found!";
                    // TODO
                }
            }
        }
    }


    //
    //  Check if enabled cripts exists then add CScriptsMetricsChecker
    //
    if( !ConfMgr.GetEnabledScriptsConfigSection().isEmpty() )
    {
        // create scritps metrics checker
        std::shared_ptr<CScriptsMetricsChecker> pScriptsChecker = std::make_shared<CScriptsMetricsChecker>();
        pScriptsChecker->SetConfigSection( ConfMgr.GetEnabledScriptsConfigSection() );
        // Add to engine
        pEngine->AddChecker(pScriptsChecker);

        LOG_INFO( "Script(s) are enabled: " + pScriptsChecker->GetScriptFileNameList().join(", ").toStdString() );
    }
    else
    {
        LOG_INFO("No enabled scripts");
    }

}

IMetricsCategoryCheckerSPtr CAgentInitialzier::CreateCheckerByConfigName(QString const& sConfigName,
                                                                  QString const& sSectionName)
{
    Q_ASSERT(!sConfigName.isEmpty());
    Q_ASSERT(!sSectionName.isEmpty());

    // make checker class name from config section name
    QString sCheckerClassName = MakeCheckerName(sConfigName, sSectionName);

    qDebug() << "Checker Name is: " << sCheckerClassName;

    int nTypeID = QMetaType::type(sCheckerClassName.toLatin1());
    if (nTypeID == QMetaType::UnknownType)
        return nullptr;

    void* pCheckerPtr = QMetaType::create(nTypeID);
    if( pCheckerPtr )
    {
        IMetricsCategoryCheckerSPtr spChecker( static_cast<IMetricsCategoryChecker*>(pCheckerPtr) );
        return spChecker;
    }

    return nullptr;
}

QString CAgentInitialzier::SimplifyName(QString sName)
{
    QString sSimplifiedName = sName.simplified().toLower();
    sSimplifiedName.replace(' ', '_');

    return sSimplifiedName;
}

QString CAgentInitialzier::MakeCheckerName(const QString &sConfigName, const QString &sSectionName)
{
    QString sCheckerClassName = SimplifyName(sConfigName)
            + "_" + SimplifyName(sSectionName);
    return ToCamelCase( sCheckerClassName );
}

QString CAgentInitialzier::ToCamelCase(const QString &s)
{
    QStringList parts = s.split('_', QString::SkipEmptyParts);
    for (int i=0; i<parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    return parts.join("");
}
