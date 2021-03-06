#include "winperformancemetricschecker.h"
#include "winpdhexception.h"
#include "upload/basicoddeyeclient.h"
#include "upload/sendcontroller.h"
#include "logger.h"

#ifdef GetMessage
#   undef GetMessage
#endif

CWinPerformanceMetricsChecker::CWinPerformanceMetricsChecker(QObject *pParent)
    : Base( pParent )
{
}

PerformanceCounterCheckersList CWinPerformanceMetricsChecker::AddPerformanceCounterCheckerEx(
        const QString &sMetricName,
        const QString &sCounterPathOrWildcard,
        EMetricDataType eMetricDataType,
        const QString &sMetricType,
        int nReaction,
        double dHighValue,
        double dSevereValue,
        bool bCreateMultipleCheckersByInstanceNames,
        const QString &sInstanceObjectName,
        const QString &sInstanceType,
        ValueModifierFunc funcMetricModifier,
        QStringList lstAllowedInstanceNames )
{
    QList<PerformanceCounterCheckerSPtr> lstAddedCheckers;

    if( !bCreateMultipleCheckersByInstanceNames )
    {
        // complete counter path
        QString sFilledCounterPathOrWildcard = sCounterPathOrWildcard.arg("(_Total)");

        // fetch instance name
        QString sInstanceName;
        MakeMetricNameFromCounterPath( sFilledCounterPathOrWildcard, nullptr, &sInstanceName );

        auto pChecker = AddPerformanceCounterChecker(  sMetricName,
                                                       sFilledCounterPathOrWildcard,
                                                       eMetricDataType,
                                                       sMetricType,
                                                       nReaction,
                                                       dHighValue,
                                                       dSevereValue,
                                                       sInstanceType,
                                                       sInstanceName,
                                                       funcMetricModifier );

        lstAddedCheckers.append( pChecker );
    }
    else
    {
        // create multiple checkers by instance names
        Q_ASSERT( !sInstanceObjectName.isEmpty() );
        Q_ASSERT( !sInstanceType.isEmpty() );

        // complete counter path
        QString sFilledCounterPathOrWildcard = sCounterPathOrWildcard.arg("(*)");

        // fetch counter paths and instance names
        QStringList lstExpandedCounterPaths = CWinPerformanceDataProvider::ExpandCounterPath(sFilledCounterPathOrWildcard);
        QStringList lstInstanceNames        = CWinPerformanceDataProvider::GetObjectInstanceNames(sInstanceObjectName);
        Q_ASSERT( lstExpandedCounterPaths.size() == lstInstanceNames.size() );
        if( lstExpandedCounterPaths.size() != lstInstanceNames.size() )
            throw CCheckerInitializationException( QString("Failed to fetch per %1 information for metric %2").arg(sInstanceType.toLower(), sMetricName) );

        bool bAllInstancesAreAllowed = lstAllowedInstanceNames.isEmpty()? true : ContainesOneOf( "all", lstAllowedInstanceNames );

        for( int i = 0; i < lstExpandedCounterPaths.size(); ++i )
        {
            QString sCurrentCounterPath = lstExpandedCounterPaths[i];
            QString sCurrentInstanceName = lstInstanceNames[i];

            if( !bAllInstancesAreAllowed && !ContainesOneOf(sCurrentInstanceName, lstAllowedInstanceNames) )
            {
                // skip checker
                continue;
            }

            // create checkers
            auto pChecker = AddPerformanceCounterChecker(  sMetricName,
                                                           sCurrentCounterPath,
                                                           eMetricDataType,
                                                           sMetricType,
                                                           nReaction,
                                                           dHighValue,
                                                           dSevereValue,
                                                           sInstanceType,
                                                           sCurrentInstanceName,
                                                           funcMetricModifier );
            lstAddedCheckers.append(pChecker);
        }

    }

    return lstAddedCheckers;
}

PerformanceCounterCheckersList CWinPerformanceMetricsChecker::AddPerformanceCounterCheckerEx(QString sPerfCounterPath,
                                                                                             const QString &sMetricType,
                                                                                             QStringList lstAllowedInstances,
                                                                                             QString sMetricName)
{
    sPerfCounterPath = sPerfCounterPath.trimmed();
    Q_ASSERT(!sPerfCounterPath.isEmpty());

    EMetricDataType eDataType;
    QString sCounterTypeName;
    QString sMakedMetricName = MakeMetricNameFromCounterPath( sPerfCounterPath, &eDataType, nullptr, &sCounterTypeName );
    if( sMetricName.isEmpty() )
        sMetricName = sMakedMetricName;


    Q_ASSERT(!sMetricName.isEmpty());
    if( sMetricName.isEmpty() )
        throw CWinPDHException( QString("Metric name is empty!") );

    return AddPerformanceCounterCheckerEx( sMetricName, sPerfCounterPath, eDataType, sMetricType, 0, -1, -1, true, sCounterTypeName, "Instance", nullptr, lstAllowedInstances );
}

QString CWinPerformanceMetricsChecker::MakeMetricNameFromCounterPath(QString sCounterPath,
                                                                     EMetricDataType *pGuessedMetricDataType,
                                                                     QString *pInstanceName,
                                                                     QString *psCounterType)
{
    sCounterPath.replace( "ASP.NET", "ASP NET", Qt::CaseInsensitive );
    sCounterPath.replace( ".NET", "Dot NET", Qt::CaseInsensitive );

    QStringList lstPathSections = sCounterPath.split( "\\", QString::SkipEmptyParts );
    if( lstPathSections.size() < 2 )
        throw CWinPDHException( QString("Invalid counter path: %1").arg(sCounterPath));

    QString sCounterType = lstPathSections.at( lstPathSections.size() - 2 ).trimmed().simplified();
    QString sCounterName = lstPathSections.at( lstPathSections.size() - 1 ).trimmed().simplified();

    //
    // process CounterType string
    //
    int nBracketIdx = sCounterType.indexOf( "(" );
    if( nBracketIdx >= 0 )
    {
        // fetch instance name
        QString sInstanceName = sCounterType.mid(nBracketIdx + 1);
        sInstanceName.remove(sInstanceName.size() - 1, 1);
        // remove instance name from counter type string
        sCounterType.remove( nBracketIdx, sCounterType.size() - nBracketIdx );
        if( pInstanceName )
            *pInstanceName = sInstanceName;
    }

    if( psCounterType )
    {
        *psCounterType = sCounterType.left( nBracketIdx );
    }

    QString sMetricPartA = NormalizeAsName( sCounterType );

    //
    //  process CounterName string
    //

    // pre-fits
    sCounterName.replace( "I/O", "IO" );
    sCounterName.replace("Read/Write", "Read Write");
    sCounterName.replace('&', " and ");
    sCounterName.replace(">=", " Gr or Eq ");
    sCounterName.replace("<=", " Sm or Eq ");
    sCounterName.replace("=", " Eq ");
    sCounterName.replace(">", " Gr ");
    sCounterName.replace("<", " Sm ");

    EMetricDataType eGuessedType = EMetricDataType::None;
    if( sCounterName.contains("# of ") )
    {
        sCounterName.remove( "# of " );
        eGuessedType = EMetricDataType::Counter;
    }
    else if( sCounterName.contains("#") )
    {
        sCounterName.remove( "#" );
        eGuessedType = EMetricDataType::Counter;
    }
    else if( sCounterName.contains( "%" ) )
    {
        sCounterName.remove( "%" );
        eGuessedType = EMetricDataType::Percent;
    }

    // check if rated metric
    int nSlashIdx = sCounterName.lastIndexOf( '/' );
    if( nSlashIdx > 0 )
    {
        QString sAfterSlash = sCounterName.mid( nSlashIdx + 1 );
        QStringList lstAfterSlashWords = sAfterSlash.split(' ', QString::SkipEmptyParts);
        if( lstAfterSlashWords.size() <= 1)
        {
            // this is rated metric
            sCounterName.remove( nSlashIdx, sCounterName.size() - nSlashIdx );
            eGuessedType = EMetricDataType::Rate;
        }
    }

    QString sMetricPartB = NormalizeAsName( sCounterName );
    if( pGuessedMetricDataType )
        *pGuessedMetricDataType = eGuessedType;


    QString sMetricName = sMetricPartA + "_" + sMetricPartB;
    return sMetricName;
}

bool CWinPerformanceMetricsChecker::ContainesOneOf(const QString &sSourceString, const QStringList &lstLexems)
{
    for( QString const& sLex : lstLexems )
        if( sSourceString.contains(sLex, Qt::CaseInsensitive) )
            return true;
    return false;
}

QString CWinPerformanceMetricsChecker::NormalizeAsName(QString sText)
{
    return CBasicOddEyeClient::NormailzeAsOEName(sText);
}

PerformanceCounterCheckerSPtr CWinPerformanceMetricsChecker::AddPerformanceCounterChecker(  const QString &sMetricName,
                                                                                            const QString &sCurrentCounterPath,
                                                                                            EMetricDataType eMetricDataType,
                                                                                            const QString &sMetricType,
                                                                                            int nReaction,
                                                                                            double dHighValue,
                                                                                            double dSevereValue,
                                                                                            const QString &sInstanceType,
                                                                                            const QString &sInstanceName,
                                                                                            ValueModifierFunc funcMetricModifier)
{
    try
    {
        // create checker
        auto pChecker = std::make_shared<CPerformanceCounterChecker>( sMetricName,
                                                                      sCurrentCounterPath,
                                                                      eMetricDataType,
                                                                      sMetricType,
                                                                      PerfDataProvider(),
                                                                      nReaction,
                                                                      dHighValue,
                                                                      dSevereValue,
                                                                      sInstanceType,
                                                                      sInstanceName,
                                                                      funcMetricModifier );
        Base::AddMetricChecker( pChecker );
        return pChecker;
    }
    catch( CFailedToAddCounterException const& oExc )
    {
        LOG_ERROR( QString("Metric data source not found: Metric: %1").arg(oExc.GetMetricName()).toStdString() );
        LOG_DEBUG( QString("Metric %1: %2").arg( oExc.GetMetricName(), oExc.GetMessage() ) );
        // sned scpecial message
        SendController.SendSeverityMessage( oExc.GetMetricName(),
                                            EMetricDataSeverity::Severe,
                                            oExc.GetMessage(), 0,
                                            oExc.GetInstanceType(),
                                            oExc.GetInstanceName() );

        return nullptr;
    }
}

PerformanceCounterCheckerSPtr CWinPerformanceMetricsChecker::AddPerformanceCounterChecker( QString sPerfCounterPath,
                                                                                           const QString &sMetricType,
                                                                                           QString sMetricName )
{
    sPerfCounterPath = sPerfCounterPath.trimmed();
    Q_ASSERT(!sPerfCounterPath.isEmpty());

    EMetricDataType eDataType;
    QString sInstanceName;

    QString sMakedMetricName = MakeMetricNameFromCounterPath( sPerfCounterPath, &eDataType, &sInstanceName );
    if( sMetricName.isEmpty() )
        sMetricName = sMakedMetricName;


    Q_ASSERT(!sMetricName.isEmpty());
    if( sMetricName.isEmpty() )
        throw CWinPDHException( QString("Metric name is empty!") );

    return AddPerformanceCounterChecker( sMetricName, sPerfCounterPath, eDataType, sMetricType, 0, -1, -1, "Instance", sInstanceName );
}

