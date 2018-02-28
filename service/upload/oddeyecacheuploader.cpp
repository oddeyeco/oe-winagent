#include "networkaccessmanager.h"
#include "oddeyecacheuploader.h"
#include "../logger.h"
#include <QDir>

COddEyeCacheUploader::COddEyeCacheUploader(QObject *parent)
    : Base( parent ),
      m_pTimer(nullptr)
{
    m_pTimer = new QTimer( this );
    m_pTimer->setInterval(5000);
    //connect(m_pTimer, &QTimer::timeout, this, &COddEyeCacheUploader::onCheckAndUpload);
    bool bOK = connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onCheckAndUpload()));
    Q_ASSERT(bOK);
}

void COddEyeCacheUploader::Start()
{
    Q_ASSERT(m_pTimer);
    m_pTimer->start();
    LOG_INFO("Cache checking started");
}

void COddEyeCacheUploader::Stop()
{
    Q_ASSERT(m_pTimer);
    m_pTimer->stop();
    m_qUploadingFiles.clear();
    LOG_INFO("Cache checking stopped");
}

void COddEyeCacheUploader::SetUpdateInterval(int nMsecs)
{
    Q_ASSERT( m_pTimer );
    m_pTimer->setInterval( nMsecs );
}

void COddEyeCacheUploader::onCheckAndUpload()
{
    QDir oCacheDir(m_sCacheDir);
    if( !oCacheDir.exists() && m_nMaxCacheCount > 0 )
    {
        LOG_ERROR( "Failed to check metric data. tmpdir not found!" );
        //TODO: emit appropriate error signal
    }

    // check max cache
    QStringList lstJsonFileList = oCacheDir.entryList(QStringList() << "*.json");
    int nCurrentJsonFileCount = lstJsonFileList.size();

    if( nCurrentJsonFileCount <= 0 )
        return;

    // reset upload queue
    m_qUploadingFiles.clear();
    for( QString const& sCurrentFile : lstJsonFileList )
    {
        QString sCurrentFilePath = oCacheDir.absoluteFilePath( sCurrentFile );
        m_qUploadingFiles.enqueue(sCurrentFilePath);
    }

    // stop checking
    Q_ASSERT(m_pTimer);
    m_pTimer->stop();

    //TODO:
    //m_pNetworkAccessManager.reset(new CNetworkAccessManager());
    m_pNetworkAccessManager->Reset();

    StartUploading();
}

void COddEyeCacheUploader::StartUploading()
{
    Q_ASSERT(!m_qUploadingFiles.isEmpty());
    if( m_qUploadingFiles.isEmpty() )
        return;

    LOG_INFO( QString("Try to upload cached metrics: %1 files").arg( m_qUploadingFiles.size()) );
    UploadHead();
}

void COddEyeCacheUploader::UploadHead()
{
    if( m_qUploadingFiles.isEmpty() )
        return;
    QString sFilePath = m_qUploadingFiles.head();
    QFile oFile( sFilePath );
    if( !oFile.open( QIODevice::ReadOnly ) )
    {
        LOG_DEBUG( "Failed to open file: " + sFilePath );
        DequeueHead();
    }

    QByteArray aJsonData = oFile.readAll();

    QJsonDocument oJsonDoc( QJsonDocument::fromJson(aJsonData) );
    Q_ASSERT( !oJsonDoc.isEmpty() );
    if( oJsonDoc.isEmpty() )
    {
        DequeueHead();
    }
    else
    {
        // Send data
        Base::SendJsonData( oJsonDoc );
    }
}

void COddEyeCacheUploader::DequeueHead()
{
    if( m_qUploadingFiles.isEmpty() )
        return;
    QString sFilePath = m_qUploadingFiles.dequeue();
    QFile oFile( sFilePath );

    // remove file
    if( !oFile.remove() )
    {
        LOG_DEBUG("Failed to remove file: " + sFilePath);
    }

    if( m_qUploadingFiles.isEmpty() )
    {
        m_pTimer->start();
    }
    else
    {
        // upload next file
        UploadHead();
    }
}

void COddEyeCacheUploader::HandleSendSuccedded(QNetworkReply *pReply, const QJsonDocument &oJsonData)
{
    LOG_INFO( "Cached file uploaded: " + pReply->readAll() );
    DequeueHead();
    if( m_qUploadingFiles.isEmpty() )
        LOG_INFO( "-All cached files uploaded!-" );
}

void COddEyeCacheUploader::HandleSendError(QNetworkReply *pReply, const QJsonDocument &oJsonData)
{
    LOG_ERROR( "Failed to uploaded file: " + pReply->errorString().toStdString() );
    LOG_INFO( QString("Chache uploading aborted! (%1 files left)").arg( m_qUploadingFiles.size() ) );
    m_qUploadingFiles.clear();
    Start();
}
