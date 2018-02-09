#include "engineinitializer.h"
#include "configurationmanager.h"
#include "checkers/scriptsmetricschecker.h"

#include <QDebug>

void CEngineInitialzier::InitializeEngine(EngineSPtr pEngine)
{
    if( !pEngine )
    {
        Q_ASSERT(false);
        return;
    }

    // Setup Main Settings
    double dUpdateSecs = ConfMgr.GetMainConfiguration().Value<double>("SelfConfig/check_period_seconds", 1);
    int nMsec = static_cast<int>( dUpdateSecs * 1000 );
    pEngine->SetUpdateInterval( nMsec );

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
                if( pChecker )
                {
                    qDebug() << "Checker found!";

                    // Pass config section to checker
                    auto&& oSection = pCurrentConfig->GetSection(sSectionName);
                    pChecker->SetConfigSection( oSection );

                    pEngine->AddChecker(pChecker);
                }
                else
                {
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
        IMetricsCategoryCheckerSPtr pScriptsChecker = std::make_shared<CScriptsMetricsChecker>();
        pScriptsChecker->SetConfigSection( ConfMgr.GetEnabledScriptsConfigSection() );
        // Add to engine
        pEngine->AddChecker(pScriptsChecker);
    }

}

IMetricsCategoryCheckerSPtr CEngineInitialzier::CreateCheckerByConfigName(QString const& sConfigName,
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

QString CEngineInitialzier::SimplifyName(QString sName)
{
    QString sSimplifiedName = sName.simplified().toLower();
    sSimplifiedName.replace(' ', '_');

    return sSimplifiedName;
}

QString CEngineInitialzier::MakeCheckerName(const QString &sConfigName, const QString &sSectionName)
{
    QString sCheckerClassName = SimplifyName(sConfigName)
            + "_" + SimplifyName(sSectionName)
            + "_checker";
    return ToCamelCase( sCheckerClassName );
}

QString CEngineInitialzier::ToCamelCase(const QString &s)
{
    QStringList parts = s.split('_', QString::SkipEmptyParts);
    for (int i=0; i<parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    return parts.join("");
}
