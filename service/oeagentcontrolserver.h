#ifndef OEAGENTCONTROLSERVER_H
#define OEAGENTCONTROLSERVER_H

#include <QLocalServer>
#include "message.h"

class COEAgentControlServer : public QLocalServer
{
    Q_OBJECT
    using Base = QLocalServer;

public:
    COEAgentControlServer(QObject* pParent = nullptr);
    ~COEAgentControlServer();

public:
    void StartListening();
    void StopListening();

    //
    //  Controls
    //
    bool StartAgent( QLocalSocket* pRequestedClientSock, QString const& sCommand = QString() );
    bool StopAgent( QLocalSocket* pRequestedClientSock, QString const& sCommand = QString() );
    bool RestartAgent( QLocalSocket* pRequestedClientSock, QString const& sCommand = QString() );
    bool SendStatus( QLocalSocket* pRequestedClientSock, QString const& sCommand = QString() );

private slots:
    void onNewConnection();
    void onReadyRead();
    void onSocketAboutToClose();

private:
    void ProcessCommandJson(QJsonObject const& oCommand, QLocalSocket* pSenderSock );
    void NotifyToAllClients( CMessage const& oMsg );
    void NotifyToClient(QLocalSocket* pClientSock,
                         CMessage const& oMsg );
private:
    // content
    QList<QLocalSocket*> m_lstClientSockets;
};

#endif // OEAGENTCONTROLSERVER_H
