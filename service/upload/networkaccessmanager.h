#ifndef NETWORK_ACCESSMANAGER_H
#define NETWORK_ACCESSMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QMutex>
#include <QQueue>

class CNetworkAccessManager : public QObject
{
    Q_OBJECT
public:
    explicit CNetworkAccessManager(QObject *parent = nullptr);
    ~CNetworkAccessManager();

public slots:
    QNetworkReply* Get(const QNetworkRequest& oRequest);
    QNetworkReply* Post(const QNetworkRequest& oRequest, const QByteArray& aData);

    void SetNetworkAccessible( QNetworkAccessManager::NetworkAccessibility eAcc );

    void CancelAll();
    void Reset();

private slots:
    void onReplyFinished();

private:
    void Add( QNetworkReply* pReply );
    void Remove(QNetworkReply* pReply);

private:
    // content
    QNetworkAccessManager*  m_pNAM;
    QMutex                  m_oMutex;
    QSet<QNetworkReply*>    m_setReplies;
};

#endif // NETWORK_ACCESSMANAGER_H
