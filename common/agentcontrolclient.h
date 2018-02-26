#ifndef AGENTCONTROLCLIENT_H
#define AGENTCONTROLCLIENT_H

#include <QObject>
#include <QLocalSocket>
#include <QtServiceController>
#include <memory>
#include "message.h"

class CAgentControlClient : public QObject
{
    Q_OBJECT
    using Base = QObject;

private:
    CAgentControlClient(QObject *parent = nullptr);
public:
    static CAgentControlClient& Instance();

public slots:
    void Start();
    void Stop();
    void Restart();
    void Status();
signals:
    void sigNotification( CMessage const& oMsg );

protected:
    bool Connect();
    void SendData( QByteArray const& aData );

private slots:
    void onSocketError();
    void onReadyRead();

private:
    QLocalSocket*       m_pServerSocket;
    QtServiceController m_oServiceController; // unused
};

#define AgentController CAgentControlClient::Instance()

#endif // AGENTCONTROLCLIENT_H
