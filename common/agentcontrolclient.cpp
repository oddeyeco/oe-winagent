#include "agentcontrolclient.h"

// Qt
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

CAgentControlClient::CAgentControlClient(QObject *parent)
    : QObject(parent),
      m_pServerSocket(nullptr),
      m_oServiceController( "OddEye Agent" )
{
    m_pServerSocket = new QLocalSocket(this);
    //connect(m_pServerSocket, &QLocalSocket::error, this, &CAgentControlClient::onSocketError);
    connect(m_pServerSocket, &QLocalSocket::readyRead, this, &CAgentControlClient::onReadyRead);
}

CAgentControlClient &CAgentControlClient::Instance()
{
    static CAgentControlClient oInst;
    return oInst;
}

void CAgentControlClient::Start()
{
    if( Connect() )
    {
        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Start";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);
    }
}

void CAgentControlClient::Stop()
{
    if( Connect() )
    {
        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Stop";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);

    }
}

void CAgentControlClient::Restart()
{
    if( Connect() )
    {
        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Restart";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);
    }
}

void CAgentControlClient::Status()
{
    if( Connect() )
    {
        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Status";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);
    }
}

bool CAgentControlClient::Connect()
{
    Q_ASSERT(m_pServerSocket);

    if( m_pServerSocket->state() != QLocalSocket::ConnectedState )
    {
        m_pServerSocket->connectToServer( "ODDEYEAGENT" );
        m_pServerSocket->waitForConnected( 500 );
    }

    if( !m_pServerSocket->open() )
    {
        // Notify Error
        QString sMessage;
        if( !m_oServiceController.isInstalled() )
            sMessage = "Service not found!";
        else if( !m_oServiceController.isRunning() )
            sMessage = "Service is stopped!";

        CMessage oMsg( "Failed to connect OddEye Agent Service",
                       sMessage,
                       EMessageType::Error,
                       "",
                       ENotificationEvent::AgentStopped );
        emit sigNotification( oMsg );
        return false;
    }

    return true;
}

void CAgentControlClient::SendData(const QByteArray &aData)
{
    if( aData.isEmpty() )
        return;

    Q_ASSERT(m_pServerSocket);

    // send terminated
    m_pServerSocket->write( aData + "\r\n\r\n" );
    m_pServerSocket->waitForBytesWritten(500);
}


void CAgentControlClient::onSocketError()
{
    // TODO
}

void CAgentControlClient::onReadyRead()
{
    Q_ASSERT(m_pServerSocket);

    QString sAllData = m_pServerSocket->readAll();
    QStringList lstNotifications = sAllData.split( "\r\n\r\n", QString::SkipEmptyParts );
    for( QString& sData : lstNotifications )
    {
        QByteArray aData = sData.toLatin1();
        QJsonDocument oJsonDoc = QJsonDocument::fromJson( aData );
        if( oJsonDoc.isEmpty())
        {
            Q_ASSERT_X(false, "onReadyRead Invalid DOC", aData);
            return;
        }

        if( !oJsonDoc.isObject() )
        {
            Q_ASSERT_X(false, "onReadyRead Not Object", aData);
        }

        // create message object
        CMessage oMsg;

        QJsonObject oJsonObj = oJsonDoc.object();
        if( oJsonObj.contains("notification_title") )
        {
            oMsg.SetTitle( oJsonObj["notification_title"].toString() );
            oMsg.SetMessage( oJsonObj["notification_message"].toString() );
            oMsg.SetType( MessageTypeFromString( oJsonObj["notification_type"].toString() ) );
        }

        if( oJsonObj.contains("notification_event") )
        {
            ENotificationEvent eEvent = static_cast<ENotificationEvent>( oJsonObj["notification_event"].toInt() );
            oMsg.SetEvent( eEvent );
        }

        if( oJsonObj.contains("notification_config_info") )
        {
            CConfigInfo oConfInfo = oJsonObj["notification_config_info"].toObject().toVariantMap();
            oMsg.SetConfigInfo( oConfInfo );
        }

        if( oJsonObj.contains("command") )
        {
            QString sCommand = oJsonObj["command"].toString();
            oMsg.SetCommand(sCommand);
        }

        // notify
        emit sigNotification( oMsg );
    }
}
