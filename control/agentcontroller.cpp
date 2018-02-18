#include "agentcontroller.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "message.h"

CAgentController::CAgentController(QObject *pParent)
    : Base(pParent),
      m_pactStart(nullptr),
      m_pactStop(nullptr),
      m_pactRestart(nullptr),
      m_oServiceController( "OddEye Agent" ),
      m_pServerSocket(nullptr)

{
    m_pSystemTrayIcon = std::make_unique<QSystemTrayIcon>();
    QMenu* pMenu = new QMenu();
    m_pactStart   = pMenu->addAction( "Start", this, SLOT(onStartClicked()));
    m_pactStop    = pMenu->addAction( "Stop", this, SLOT(onStopClicked()) );
    m_pactRestart = pMenu->addAction( "Restart", this, SLOT(onRestartClicked()) );
    pMenu->addSeparator();
    auto pactExit = pMenu->addAction( "Exit", this, SLOT(onExitClicked()) );

    //
    m_pactStop->setEnabled(false);
    m_pactRestart->setEnabled(false);

    m_pSystemTrayIcon->setContextMenu( pMenu );
    m_pSystemTrayIcon->setIcon( QIcon("://icons/agentlogo.png") );


    m_pServerSocket = new QLocalSocket(this);
    //connect(m_pServerSocket, &QLocalSocket::error, this, &CAgentController::onSocketError);
    connect(m_pServerSocket, &QLocalSocket::readyRead, this, &CAgentController::onReadyRead);

    m_pSystemTrayIcon->show();
}

CAgentController::~CAgentController()
{}

void CAgentController::Start()
{
    Q_ASSERT(m_pServerSocket);

    m_pServerSocket->connectToServer( "ODDEYEAGENT" );
    if( m_pServerSocket->open() )
    {
        if( !m_pServerSocket->isOpen() )
        {
            m_pServerSocket->open();
        }

        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Start";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);
    }
    else
    {
        m_pSystemTrayIcon->showMessage( "Failed to connect OddEye Agent Service",
                                        "Service is missing or stopped!",
                                        QSystemTrayIcon::Critical );
    }
}

void CAgentController::Stop()
{
    Q_ASSERT(m_pServerSocket);

    m_pServerSocket->connectToServer( "ODDEYEAGENT" );
    if( m_pServerSocket->open() )
    {

        if( !m_pServerSocket->isOpen() )
        {
            m_pServerSocket->open();
        }

        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Stop";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);

    }
    else
    {
        m_pSystemTrayIcon->showMessage( "Failed to connect OddEye Agent Service",
                                        "Service is missing or stopped!",
                                        QSystemTrayIcon::Critical );
    }
}

void CAgentController::Restart()
{
    Q_ASSERT(m_pServerSocket);

    m_pServerSocket->connectToServer( "ODDEYEAGENT" );
    if( m_pServerSocket->open() )
    {
        if( !m_pServerSocket->isOpen() )
        {
            m_pServerSocket->open();
        }

        QJsonObject oCommandJson;
        oCommandJson["Command"] = "Restart";

        m_pServerSocket->write( QJsonDocument( oCommandJson ).toJson() );
        m_pServerSocket->waitForBytesWritten(500);
    }
    else
    {
        m_pSystemTrayIcon->showMessage( "Failed to connect OddEye Agent Service",
                                        "Service is missing or stopped!",
                                        QSystemTrayIcon::Critical );
    }
}

void CAgentController::onStartClicked()
{
    Start();
}

void CAgentController::onStopClicked()
{
    Stop();
}

void CAgentController::onRestartClicked()
{
    Restart();
}

void CAgentController::onExitClicked()
{
    qApp->exit();
}

void CAgentController::onSocketError()
{

}

void CAgentController::onReadyRead()
{
    Q_ASSERT(m_pServerSocket);
    Q_ASSERT(m_pSystemTrayIcon);

    QByteArray aData = m_pServerSocket->readAll();
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

    QJsonObject oJsonObj = oJsonDoc.object();
    if( oJsonObj.contains("notification_title") )
    {
        CMessage oMsg( oJsonObj["notification_title"].toString(),
                       oJsonObj["notification_message"].toString(),
                       MessageTypeFromString( oJsonObj["notification_type"].toString() ) );

        QSystemTrayIcon::MessageIcon eMessageType;
        switch (oMsg.GetType()) {
        case EMessageType::Error:
            eMessageType = QSystemTrayIcon::Critical;
            break;
        case EMessageType::Warning:
            eMessageType = QSystemTrayIcon::Warning;
            break;
        case EMessageType::Information:
            eMessageType = QSystemTrayIcon::Information;
            break;
        default:
            break;
        }

        m_pSystemTrayIcon->showMessage( oMsg.GetTitle(), oMsg.GetMessage(), eMessageType);
    }

    if( oJsonObj.contains("notification_event") )
    {
        ENotificationEvent eEvent = static_cast<ENotificationEvent>( oJsonObj["notification_event"].toInt() );

        if( eEvent == ENotificationEvent::AgentStarted )
        {
            m_pactStop->setEnabled(true);
            m_pactRestart->setEnabled(true);
            m_pactStart->setEnabled(false);
        }

        if( eEvent == ENotificationEvent::AgentStopped )
        {
            m_pactStop->setEnabled(false);
            m_pactRestart->setEnabled(false);
            m_pactStart->setEnabled(true);
        }
    }
}
