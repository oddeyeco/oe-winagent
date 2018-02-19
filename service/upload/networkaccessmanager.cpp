#include "networkaccessmanager.h"

#include <QNetworkReply>

CNetworkAccessManager::CNetworkAccessManager(QObject *parent)
    : QObject(parent),
      m_pNAM(nullptr)
{
    m_pNAM = new QNetworkAccessManager(this);
}

CNetworkAccessManager::~CNetworkAccessManager()
{
    //CancelAll();
}

QNetworkReply* CNetworkAccessManager::Get(const QNetworkRequest &oRequest)
{
    Q_ASSERT( m_pNAM );
    QNetworkReply* pReply = m_pNAM->get( oRequest );
    Add(pReply);
    return pReply;
}

QNetworkReply *CNetworkAccessManager::Post(const QNetworkRequest &oRequest, const QByteArray &aData)
{
    Q_ASSERT( m_pNAM );
    QNetworkReply* pReply = m_pNAM->post( oRequest, aData );
    Add(pReply);
    return pReply;
}

void CNetworkAccessManager::SetNetworkAccessible(QNetworkAccessManager::NetworkAccessibility eAcc)
{
    Q_ASSERT( m_pNAM );
    m_pNAM->setNetworkAccessible( eAcc );
}

void CNetworkAccessManager::CancelAll()
{
    //QMutexLocker oLocker(&m_oMutex);
    for( auto pReply : m_setReplies )
    {
        if( !pReply )
            return;

        // abort
        //pReply->abort();
    }
}

void CNetworkAccessManager::Reset()
{
//    CancelAll();
//    m_pNAM->deleteLater();

//    // create new one
//    m_pNAM = new QNetworkAccessManager(this);
    m_pNAM->setNetworkAccessible( QNetworkAccessManager::NotAccessible );
    m_pNAM->setNetworkAccessible( QNetworkAccessManager::Accessible );
}

void CNetworkAccessManager::onReplyFinished()
{
    QNetworkReply* pReply = dynamic_cast<QNetworkReply*>( sender() );
    Remove( pReply );
}

void CNetworkAccessManager::Add(QNetworkReply *pReply)
{
    if( !pReply )
        return;
    QMutexLocker oLocker( &m_oMutex );
    m_setReplies.insert( pReply );
    connect( pReply, &QNetworkReply::finished, this, &CNetworkAccessManager::onReplyFinished );
}

void CNetworkAccessManager::Remove(QNetworkReply *pReply)
{
    if( !pReply )
        return;
    QMutexLocker oLocker( &m_oMutex );
    disconnect( pReply, &QNetworkReply::finished, this, &CNetworkAccessManager::onReplyFinished );
    m_setReplies.remove( pReply );
    //pReply->deleteLater();
}
