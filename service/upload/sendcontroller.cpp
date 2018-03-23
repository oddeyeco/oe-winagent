#include "sendcontroller.h"
#include "oddeyeclient.h"
#include "oddeyecacheuploader.h"
#include "../configurationmanager.h"
#include "../logger.h"

#include "../pinger.h"
// Qt
#include <QCoreApplication>
#include <QDir>
#include <QHostInfo>


CSendController::CSendController()
    : m_bIsReady(false)
{
    m_pNetworkManager = std::make_shared<CNetworkAccessManager>();

    // create oddeye client
    m_pOEClient = std::make_unique<COddEyeClient>();

    // create cache uploader thread
    m_pCacheUploaderThread = new QThread(this);
    // create cache uploader
    m_pOECacheUploader = std::make_unique<COddEyeCacheUploader>();
    m_pOECacheUploader->moveToThread(m_pCacheUploaderThread);

    bool bOK = connect( this, SIGNAL(sigStartCacheUploading()), m_pOECacheUploader.get(), SLOT(Start()) );
    Q_ASSERT(bOK);
    bOK      = connect( this, SIGNAL(sigStopCacheUploading()),  m_pOECacheUploader.get(), SLOT(Stop()) );
    Q_ASSERT(bOK);

    // set network access manager
    m_pOEClient->SetNetworkAccessManager(m_pNetworkManager);
    m_pOECacheUploader->SetNetworkAccessManager( m_pNetworkManager );

    // Start thread
    m_pCacheUploaderThread->start();
}

CSendController &CSendController::Instance()
{
    static CSendController oInst;
    return oInst;
}

CSendController::~CSendController()
{   
    Q_ASSERT(m_pCacheUploaderThread);
    m_pCacheUploaderThread->quit();
    m_pCacheUploaderThread->wait();
}

void CSendController::SendMetricsData(const MetricDataList &lstMetrics)
{
    Q_ASSERT(m_pOEClient);
    if( m_pOEClient )
        m_pOEClient->SendMetrics( lstMetrics );
}

void CSendController::SendSeverityMessage(MetricSeverityDescriptorSPtr pSeverityDescriptor)
{
    Q_ASSERT( m_pOEClient );
    m_pOEClient->SendSpecialMessage( pSeverityDescriptor );
}

void CSendController::SendSeverityMessage(const QString &sMetricName,
                                          EMetricDataSeverity eSeverity,
                                          const QString &sMessage,
                                          double dAlertDurationHint,
                                          const QString &sInstanceType,
                                          const QString &sInstanceName)
{
    MetricSeverityDescriptorSPtr pDescriptor = std::make_shared<CMetricSeverityDescriptor>(sMetricName,
                                                                                           QDateTime::currentDateTime(),
                                                                                           eSeverity,
                                                                                           dAlertDurationHint,
                                                                                           sMessage,
                                                                                           sInstanceType,
                                                                                           sInstanceName);
    SendSeverityMessage( pDescriptor );
}

void CSendController::SetupOEClients()
{
    m_pOECacheUploader->SetUpdateInterval( 2000 );

    //
    //  Read settings from config
    //
    // set server url from
    QString sTsdbUrl = ConfMgr.GetMainConfiguration().Value<QByteArray>("TSDB/url");
    if( sTsdbUrl.isEmpty() )
        throw CInvalidConfigException("TSDB url is missing");
    m_pOEClient->SetTSDBUrl( sTsdbUrl );
    m_pOECacheUploader->SetTSDBUrl( sTsdbUrl );

    // set OddEye Uuid
    QByteArray aUuid = ConfMgr.GetMainConfiguration().Value<QByteArray>("TSDB/uuid");
    if( aUuid.isEmpty() || aUuid.startsWith("xxxxxxxx") )
        throw CInvalidConfigException("OddEye UUID is missing");
    m_pOEClient->SetUuid( aUuid );
    m_pOECacheUploader->SetUuid( aUuid );

    // set cluster name
    QString sClastername = ConfMgr.GetMainConfiguration().Value<QString>( "SelfConfig/cluster_name" );
    if( sClastername.isEmpty() )
        throw CInvalidConfigException("Cluster name is missing");
    m_pOEClient->SetClusterName( sClastername );
    m_pOECacheUploader->SetClusterName( sClastername );

    // set host group name
    QString sGroup  = ConfMgr.GetMainConfiguration().Value<QString>( "SelfConfig/host_group" );
    if( sGroup.isEmpty() )
        throw CInvalidConfigException("Host group name is missing");
    m_pOEClient->SetGroupName( sGroup );
    m_pOECacheUploader->SetGroupName( sGroup );

    // set host name
    QString sHostName = QHostInfo::localHostName();
    m_pOEClient->SetHostName( sHostName );
    m_pOECacheUploader->SetHostName( sHostName );

    // set cache dir
    QString sCacheDir = ConfMgr.GetMainConfiguration().GetValueAsPath( "SelfConfig/tmpdir", /*"/tmp/oddeye_tmp"*/ QString() );
    if( sCacheDir.isEmpty() )
        throw CInvalidConfigException("tempdir is missing");

    QDir oCacheDir(sCacheDir);
    if(!oCacheDir.exists())
    {
        // try create
        if( !oCacheDir.mkpath( sCacheDir ) )
            throw CInvalidConfigException("Failed to create tempdir " + sCacheDir);
    }
    m_pOEClient->SetCacheDir( oCacheDir.absolutePath() );
    m_pOECacheUploader->SetCacheDir( oCacheDir.absolutePath() );

    // Set max cache count
    int nMaxCacheCount = ConfMgr.GetMainConfiguration().Value<int>( "SelfConfig/max_cache", -1 );
    if( nMaxCacheCount <= 0 )
        LOG_INFO( "Caching is disabled" );

    m_pOEClient->SetMaxCacheCount( nMaxCacheCount );
    m_pOECacheUploader->SetMaxCacheCount( nMaxCacheCount );
}


NetworkAccessManagerWPtr CSendController::GetNetworkAccessManager()
{
    return m_pNetworkManager;
}

void CSendController::TurnOn()
{
    m_pNetworkManager->SetNetworkAccessible( QNetworkAccessManager::Accessible );
    //  setup OddEye client and OddEye cache uploader
    SetupOEClients();


    // Start Cache Uploading in worker thread
    emit sigStartCacheUploading();

    m_bIsReady = true;
}

void CSendController::TurnOff()
{
    // stop cache checking

    emit sigStopCacheUploading();

    // delete Network Manager
    m_pNetworkManager->SetNetworkAccessible( QNetworkAccessManager::NotAccessible );

    m_bIsReady = false;
}

bool CSendController::IsReady() const
{

    return m_bIsReady;
}
