#include "sendcontroller.h"
#include "oddeyeclient.h"
#include "oddeyecacheuploader.h"
#include "../configurationmanager.h"
#include "../logger.h"

#include "../pinger.h"

// Qt
#include <QDir>
#include <QHostInfo>


CSendController::CSendController(QObject *pParent)
    : Base(pParent),
      m_bIsReady(false)
{
    m_pNetworkManager = std::make_shared<QNetworkAccessManager>();
    //  setup OddEye client and OddEye cache uploader
    SetupOEClients();


    // Start Cache Uploading in worker thread
    emit sigStartCacheUploading();

    m_bIsReady = true;
}

CSendController::~CSendController()
{   
    Q_ASSERT(m_pCacheUploaderThread);
    m_pCacheUploaderThread->quit();
    m_pCacheUploaderThread->wait();
}


void CSendController::SetupOEClients()
{
    // create oddeye client
    m_pOEClient = std::make_unique<COddEyeClient>();

    // create cache uploader thread
    m_pCacheUploaderThread = new QThread(this);
    // create cache uploader
    m_pOECacheUploader = std::make_unique<COddEyeCacheUploader>();
    m_pOECacheUploader->moveToThread(m_pCacheUploaderThread);
    bool bOK = connect( this, SIGNAL(sigStartCacheUploading()), m_pOECacheUploader.get(), SLOT(Start()) );
    Q_ASSERT(bOK);

    m_pOECacheUploader->SetUpdateInterval( 2000 );

    //
    //  Read settings from config
    //

    // set network access manager
    m_pOEClient->SetNetworkAccessManager(m_pNetworkManager);
    m_pOECacheUploader->SetNetworkAccessManager( m_pNetworkManager );

    // set server url from
    QString sTsdbUrl = ConfMgr.GetMainConfiguration().Value<QByteArray>("TSDB/url");
    if( sTsdbUrl.isEmpty() )
        throw CInvalidConfigException("TSDB url is missing");
    m_pOEClient->SetTSDBUrl( sTsdbUrl );
    m_pOECacheUploader->SetTSDBUrl( sTsdbUrl );

    // set OddEye Uuid
    QByteArray aUuid = ConfMgr.GetMainConfiguration().Value<QByteArray>("TSDB/uuid");
    if( aUuid.isEmpty() )
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
    QString sCacheDir = ConfMgr.GetMainConfiguration().Value<QString>( "SelfConfig/tmpdir" );
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


    // Start thread
    m_pCacheUploaderThread->start();
}

void CSendController::SendMetricsData(const MetricDataList &lstMetrics)
{    
    Q_ASSERT(m_pOEClient);
    m_pOEClient->SendMetrics( lstMetrics );
}

void CSendController::SendMessage(const QString &sMessage, EMessageType eType)
{
    Q_ASSERT(m_pOEClient);
    if( !m_pOEClient->IsReady())
        return;

    //m_pOEClient->SendMessage( sMessage, eType );
}

NetworkAccessManagerWPtr CSendController::GetNetworkAccessManager()
{
    return m_pNetworkManager;
}

bool CSendController::IsReady() const
{
    return m_bIsReady;
}



