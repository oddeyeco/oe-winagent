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

    if( !oMsg.GetConfigInfo().isEmpty() )
    {
        QJsonObject oConfigInfoJson = QJsonObject::fromVariantMap( oMsg.GetConfigInfo() );
        oMsgJson["notification_config_info"] = oConfigInfoJson;
    }

    QByteArray aNotif = QJsonDocument( oMsgJson ).toJson();

    Q_ASSERT(!aNotif.isEmpty() );
    if( aNotif.isEmpty() )
        return;

    pClientSock->write( aNotif );
    pClientSock->waitForBytesWritten(500);
}

bool COEAgentControlServer::StartAgent(QLocalSocket *pRequestedClientSock)
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

            // collect info about agent to notify
            QString sConfigsDirPath = ConfMgr.GetConfigsDirPath();
            QString sLogsDirPath = Logger::getInstance().GetLogDirPath();
            QString sInfo = QString("\nConfigs Dir: %1\n"
                                      "Logs Dir: %2").arg( sConfigsDirPath, sLogsDirPath );
            NotifyToClient( pRequestedClientSock, CMessage( ENotificationEvent::AgentStarted,
                                                            "OddEye Agent Started",
                                                            sInfo));

            LOG_INFO("Control SERVER: StartAgent succedded!")
            return true;
        }
        catch(std::exception const& oExc)
        {
            QString sMessageTitle = QString( "OE-Agent start faield: %1" ).arg( oExc.what() );
            NotifyToClient( pRequestedClientSock, CMessage("OE-Agent start faield",
                                                           oExc.what(),
                                                           EMessageType::Error) );
            LOG_ERROR("Control SERVER: StartAgent failed!" + std::string(oExc.what()));
            return false;
        }
        catch( ... )
        {
            QString sErrorMessage = "OE-Agent start faield: Unknown exception";
            NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
            LOG_ERROR("Control SERVER: StartAgent failed! Unknown exception");
            return false;
        }
    }
}

bool COEAgentControlServer::StopAgent(QLocalSocket *pRequestedClientSock)
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

            NotifyToClient( pRequestedClientSock, CMessage(ENotificationEvent::AgentStopped,"OddEye Agent Stopped"));
            LOG_INFO("Control SERVER: StopAgent succedded!")
            return true;
        }
        catch(std::exception const& oExc)
        {
            NotifyToClient( pRequestedClientSock, CMessage( "OE-Agent stop faield",
                                                            oExc.what(),
                                                            EMessageType::Error ) );
            LOG_ERROR("Control SERVER: StopAgent failed!" + std::string(oExc.what()) );
            return false;
        }
        catch( ... )
        {
            QString sErrorMessage = "OE-Agent stop faield: Unknown exception";
            NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
            LOG_ERROR("Control SERVER: StopAgent failed! Unknown exception");
            return false;
        }
    }
}

bool COEAgentControlServer::RestartAgent(QLocalSocket *pRequestedClientSock)
{    
    try
    {
        if( CServiceController::Instance().IsStarted() )
            CServiceController::Instance().Stop();
        CServiceController::Instance().Start();

        NotifyToClient( pRequestedClientSock, CMessage(ENotificationEvent::AgentStarted,
                                                       "OddEye Agent Restarted"));
        LOG_INFO("Control SERVER: RestartAgent succedded!")
        return true;
    }
    catch(std::exception const& oExc)
    {
        NotifyToClient( pRequestedClientSock, CMessage( "OE-Agent restart faield",
                                                        oExc.what(),
                                                        EMessageType::Error ) );
        LOG_ERROR("Control SERVER: RestartAgent failed!" + std::string( oExc.what()) );
        return false;
    }
    catch( ... )
    {
        QString sErrorMessage = "OE-Agent restart faield: Unknown exception";
        NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
        LOG_ERROR("Control SERVER: RestartAgent failed! Unknown exception");
        return false;
    }
}

bool COEAgentControlServer::SendStatus(QLocalSocket *pRequestedClientSock)
{
    try
    {
        // Notify Status
        ENotificationEvent eEvent = CServiceController::Instance().IsStarted()?
                    ENotificationEvent::AgentStarted : ENotificationEvent::AgentStopped;

        // collect info about agent to notify
        QString sConfigsDirPath = ConfMgr.GetConfigsDirPath();
        QString sLogsDirPath = Logger::getInstance().GetLogDirPath();
        CConfigInfo oConfInfo;
        oConfInfo["conf_dir"] = sConfigsDirPath;
        oConfInfo["log_dir"] = sLogsDirPath;

        CMessage oNotification(eEvent);
        oNotification.SetConfigInfo( oConfInfo );

        NotifyToClient(pRequestedClientSock, oNotification);
        LOG_INFO("Control SERVER: SendStatus Succedded");
        return true;
    }
    catch(std::exception const& oExc)
    {
        NotifyToClient( pRequestedClientSock, CMessage( "Failed to check OE-Agent status",
                                                        oExc.what(),
                                                        EMessageType::Error ) );
        LOG_ERROR("Control SERVER: SendStatus failed!" + std::string( oExc.what()) );
        return false;
    }
    catch( ... )
    {
        QString sErrorMessage = "Failed to check OE-Agent status: Unknown exception";
        NotifyToClient( pRequestedClientSock, CMessage( sErrorMessage, EMessageType::Error ) );
        LOG_ERROR("Control SERVER: SendStatus failed! Unknown exception");
        return false;
    }
}

void COEAgentControlServer::ProcessCommandJson(const QJsonObject &oCommand,
                                               QLocalSocket* pSenderSock)
{
    QString sCommand = oCommand.value( "Command" ).toString();

    if( sCommand.compare( "start", Qt::CaseInsensitive ) == 0 )
    {
        StartAgent( pSenderSock );
    }
    else if( sCommand.compare( "stop", Qt::CaseInsensitive ) == 0  )
    {
        StopAgent( pSenderSock );
    }
    else if( sCommand.compare( "restart", Qt::CaseInsensitive ) == 0  )
    {
        // Restart
        RestartAgent(pSenderSock);
    }
    else if( sCommand.compare( "status", Qt::CaseInsensitive ) == 0  )
    {
        // Restart
        SendStatus(pSenderSock);
    }
}
