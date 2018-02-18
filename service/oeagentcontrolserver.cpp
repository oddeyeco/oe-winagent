#include "oeagentcontrolserver.h"
#include "servicecontroller.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QLocalSocket>
#include <iostream>

#include "agentinitializer.h"
#include "configurationmanager.h"

COEAgentControlServer::COEAgentControlServer(QObject* pParent )
    : Base(pParent)
{
    setSocketOptions( QLocalServer::WorldAccessOption );

    connect( this, &COEAgentControlServer::newConnection,
             this, &COEAgentControlServer::onNewConnection );

//    connect( &CServiceController::Instance(), &CServiceController::sigStarted,
//             this, [this]()
//    {
//        NotifyToAllClients( CMessage( ENotificationEvent::AgentStarted) );
//    });

//    connect( &CServiceController::Instance(), &CServiceController::sigStopped,
//             this, [this]()
//    {
//        NotifyToAllClients( CMessage( ENotificationEvent::AgentStopped) );
//    });
}

COEAgentControlServer::~COEAgentControlServer()
{
    NotifyToAllClients( CMessage( ENotificationEvent::AgentStopped, "OddEye Agent Service has been terminated" ) );
}

void COEAgentControlServer::StartListening()
{
    bool bOk = Base::listen( "ODDEYEAGENT" );
    if( bOk )
    {
        std::cout << "OEAgent control server starts listening..." << std::endl;
        std::cout << "Name: " << serverName().toStdString() << std::endl;
        //LOG_INFO( "OEAgent control server started" );
    }
    else
    {
        std::cout << "OEAgent control server start failed!" << std::endl;
        //LOG_INFO( "OEAgent control server start failed!" );
    }
    // TODO: handle false result
}

void COEAgentControlServer::StopListening()
{
    Base::removeServer( Base::serverName() );
    std::cout << "OEAgent control server stopped" << std::endl;
    //LOG_INFO( "OEAgent control server stopped" );
}

void COEAgentControlServer::onNewConnection()
{
    QLocalSocket* pClientSock = Base::nextPendingConnection();
    Q_ASSERT(pClientSock);
    if( !pClientSock )
        return;

    connect( pClientSock, &QLocalSocket::readyRead, this,
             &COEAgentControlServer::onReadyRead );

    connect( pClientSock, &QLocalSocket::aboutToClose, this,
             &COEAgentControlServer::onSocketAboutToClose );

    m_lstClientSockets.append(pClientSock);

    std::cout << "New Connection!" << "[" << m_lstClientSockets.size() << "]" << std::endl;
}

void COEAgentControlServer::onReadyRead()
{
    QLocalSocket* pClientSock = dynamic_cast<QLocalSocket*>( sender() );
    Q_ASSERT(pClientSock);
    if( !pClientSock )
        return;

    QByteArray aCommand = pClientSock->readAll();
    QJsonDocument oJsonDoc = QJsonDocument::fromJson( aCommand );
    if( oJsonDoc.isEmpty() || !oJsonDoc.isObject() )
    {
        Q_ASSERT(false);
        return;
    }

    QJsonObject oCommandJson = oJsonDoc.object();
    ProcessCommandJson( oCommandJson, pClientSock );
}

void COEAgentControlServer::onSocketAboutToClose()
{
    QLocalSocket* pClientSock = dynamic_cast<QLocalSocket*>( sender() );
    Q_ASSERT(pClientSock);
    if( !pClientSock )
        return;

    m_lstClientSockets.removeAll( pClientSock );
}

void COEAgentControlServer::NotifyToAllClients(const CMessage &oMsg)
{
    for( QLocalSocket* pClientSock : m_lstClientSockets )
    {
        if( !pClientSock )
        {
            Q_ASSERT(false);
            continue;
        }

        NotifyToClient( pClientSock, oMsg );
    }
}

void COEAgentControlServer::NotifyToClient(QLocalSocket *pClientSock,
                                           const CMessage &oMsg)
{
    if( !pClientSock )
    {
        return;
    }

    QJsonObject oMsgJson;


    if( oMsg.HasMessage() )
    {
        oMsgJson["notification_title"] = oMsg.GetTitle();
#ifdef GetMessage
#   undef GetMessage
        oMsgJson["notification_message"] = oMsg.GetMessage();
#endif
        oMsgJson["notification_type"] = ToString(oMsg.GetType());
    }

    if( oMsg.GetEvent() != ENotificationEvent::NoEvent)
    {
        oMsgJson["notification_event"] = static_cast<qint32>(oMsg.GetEvent());
    }

    QByteArray aNotif = QJsonDocument( oMsgJson ).toJson();

    Q_ASSERT(!aNotif.isEmpty() );
    if( aNotif.isEmpty() )
        return;

    pClientSock->write( aNotif );
    pClientSock->waitForBytesWritten(500);
}

bool COEAgentControlServer::onStartAgent(QLocalSocket *pRequestedClientSock)
{
    if( CServiceController::Instance().IsStarted() )
    {
        NotifyToClient(pRequestedClientSock, CMessage("OddEye Agent is already running"));
        return true;
    }
    else
    {
        // Start
        try
        {
            CServiceController::Instance().Start();
        }
        catch(std::exception const& oExc)
        {
            QString sMessageTitle = QString( "OE-Agent start faield: %1" ).arg( oExc.what() );
            NotifyToClient( pRequestedClientSock, CMessage("OE-Agent start faield",
                                                           oExc.what(),
                                                           EMessageType::Error) );
            return false;
        }
        catch( ... )
        {
            QString sErrorMessage = "OE-Agent start faield: Unknown exception";
            NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
            return false;
        }

        // collect info about agent to notify
        QString sConfigsDirPath = ConfMgr.GetConfigsDirPath();
        QString sLogsDirPath = Logger::getInstance().GetLogDirPath();
        QString sInfo = QString("\nConfigs Dir: %1\n"
                                  "Logs Dir: %2").arg( sConfigsDirPath, sLogsDirPath );
        NotifyToClient( pRequestedClientSock, CMessage( ENotificationEvent::AgentStarted,
                                                        "OddEye Agent Started",
                                                        sInfo));
        return true;
    }
}

bool COEAgentControlServer::onStopAgent(QLocalSocket *pRequestedClientSock)
{
    if( !CServiceController::Instance().IsStarted() )
    {
        NotifyToClient(pRequestedClientSock, CMessage( "OddEye Agent is not running" ) );
        return true;
    }
    else
    {
        // Stop
        try
        {
            CServiceController::Instance().Stop();
        }
        catch(std::exception const& oExc)
        {
            NotifyToClient( pRequestedClientSock, CMessage( "OE-Agent stop faield",
                                                            oExc.what(),
                                                            EMessageType::Error ) );
            return false;
        }
        catch( ... )
        {
            QString sErrorMessage = "OE-Agent stop faield: Unknown exception";
            NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
            return false;
        }

        NotifyToClient( pRequestedClientSock, CMessage(ENotificationEvent::AgentStopped,"OddEye Agent Stopped"));
        return true;
    }
}

bool COEAgentControlServer::onRestartAgent(QLocalSocket *pRequestedClientSock)
{    
    try
    {
        if( CServiceController::Instance().IsStarted() )
            CServiceController::Instance().Stop();
        CServiceController::Instance().Start();

        NotifyToClient( pRequestedClientSock, CMessage(ENotificationEvent::AgentStarted,
                                                       "OddEye Agent Restarted"));
        return true;
    }
    catch(std::exception const& oExc)
    {
        NotifyToClient( pRequestedClientSock, CMessage( "OE-Agent restart faield",
                                                        oExc.what(),
                                                        EMessageType::Error ) );
        return false;
    }
    catch( ... )
    {
        QString sErrorMessage = "OE-Agent restart faield: Unknown exception";
        NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
        return false;
    }
}

bool COEAgentControlServer::onSendStatus(QLocalSocket *pRequestedClientSock)
{
    try
    {
        // Notify Status
        ENotificationEvent eEvent = CServiceController::Instance().IsStarted()?
                    ENotificationEvent::AgentStarted : ENotificationEvent::AgentStopped;

        NotifyToClient(pRequestedClientSock, CMessage(eEvent));
        return true;
    }
    catch(std::exception const& oExc)
    {
        NotifyToClient( pRequestedClientSock, CMessage( "Failed to check OE-Agent status",
                                                        oExc.what(),
                                                        EMessageType::Error ) );
        return false;
    }
    catch( ... )
    {
        QString sErrorMessage = "Failed to check OE-Agent status: Unknown exception";
        NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
        return false;
    }


}

void COEAgentControlServer::ProcessCommandJson(const QJsonObject &oCommand,
                                               QLocalSocket* pSenderSock)
{
    QString sCommand = oCommand.value( "Command" ).toString();

    if( sCommand.compare( "start", Qt::CaseInsensitive ) == 0 )
    {
        onStartAgent( pSenderSock );
    }
    else if( sCommand.compare( "stop", Qt::CaseInsensitive ) == 0  )
    {
        onStopAgent( pSenderSock );
    }
    else if( sCommand.compare( "restart", Qt::CaseInsensitive ) == 0  )
    {
        // Restart
        onRestartAgent(pSenderSock);
    }
    else if( sCommand.compare( "status", Qt::CaseInsensitive ) == 0  )
    {
        // Restart
        onSendStatus(pSenderSock);
    }
}
