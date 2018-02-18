#include "guicontroller.h"

#include <QDesktopServices>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>
#include <QProcessEnvironment>
#include <QFileInfo>
#include <QDir>

#include "message.h"

CGuiController::CGuiController(QObject *pParent)
    : Base(pParent),
      m_pactStart(nullptr),
      m_pactStop(nullptr),
      m_pactRestart(nullptr),
      m_pactOpenConfDir(nullptr),
      m_pactOpenLogsDir( nullptr )
{
    m_pSystemTrayIcon = std::make_unique<QSystemTrayIcon>();
    QMenu* pMenu = new QMenu();
    m_pactStart   = pMenu->addAction( "Start", this, SLOT(onStartClicked()));
    m_pactStop    = pMenu->addAction( "Stop", this, SLOT(onStopClicked()) );
    m_pactRestart = pMenu->addAction( "Restart", this, SLOT(onRestartClicked()) );

    pMenu->addSeparator();
    m_pactOpenConfDir = pMenu->addAction( "Open Configs Folder", this, SLOT(onOpenFolder()));
    m_pactOpenLogsDir = pMenu->addAction( "Open Logs Folder", this, SLOT(onOpenFolder()));

    pMenu->addSeparator();
    auto pactExit = pMenu->addAction( "Exit", this, SLOT(onExitClicked()) );

    //
    m_pactStop->setEnabled(false);
    m_pactRestart->setEnabled(false);

    m_pSystemTrayIcon->setContextMenu( pMenu );
    m_pSystemTrayIcon->setIcon( QIcon("://icons/agentlogo.png") );

    // show tray icon
    m_pSystemTrayIcon->show();

    // connect
    connect( &AgentController, &CAgentControlClient::sigNotification, this, &CGuiController::onNotification );
    AgentController.Status();
}

CGuiController::~CGuiController()
{
    m_pSystemTrayIcon->hide();
}

void CGuiController::onStartClicked()
{
    AgentController.Start();
}

void CGuiController::onStopClicked()
{
    AgentController.Stop();
}

void CGuiController::onRestartClicked()
{
    AgentController.Restart();
}

void CGuiController::onOpenFolder()
{
    QObject* pSenderAct = sender();
    if( pSenderAct )
        pSenderAct->setProperty("clicked", true);

    AgentController.Status();
}

void CGuiController::onExitClicked()
{
    qApp->exit();
}

void CGuiController::onNotification(const CMessage &oMsg)
{
    Q_ASSERT(m_pSystemTrayIcon);
    Q_ASSERT( !oMsg.IsEmpty() );
    if( oMsg.IsEmpty() )
        return;

    if( oMsg.HasMessage() )
    {
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

    ENotificationEvent eEvent = oMsg.GetEvent();

    if( eEvent == ENotificationEvent::AgentStarted )
    {
        m_pSystemTrayIcon->setToolTip( "AddEye agent is running" );
        m_pactStop->setEnabled(true);
        m_pactRestart->setEnabled(true);
        m_pactStart->setEnabled(false);
    }

    if( eEvent == ENotificationEvent::AgentStopped )
    {
        m_pSystemTrayIcon->setToolTip( "AddEye agent is stopped!" );
        m_pactStop->setEnabled(false);
        m_pactRestart->setEnabled(false);
        m_pactStart->setEnabled(true);
    }

    if( !oMsg.GetConfigInfo().isEmpty() )
    {
        if( m_pactOpenConfDir->property( "clicked" ).toBool() )
        {
            m_pactOpenConfDir->setProperty("clicked", false );
            QString sConfigsDirPath = oMsg.GetConfigInfo().value("conf_dir").toString();
            ShowInGraphicalShell( sConfigsDirPath );
        }

        if( m_pactOpenLogsDir->property( "clicked" ).toBool() )
        {
            m_pactOpenLogsDir->setProperty("clicked", false );
            QString sLogsDirPath = oMsg.GetConfigInfo().value("log_dir").toString();
            ShowInGraphicalShell( sLogsDirPath );
        }
    }
}

void CGuiController::ShowInGraphicalShell(const QString &pathIn)
{
    QWidget *parent = nullptr;

    const QString explorer = "explorer.exe";
    if (explorer.isEmpty()) {
        QMessageBox::warning(parent,
                             tr("Launching Windows Explorer failed"),
                             tr("Could not find explorer.exe in path to launch Windows Explorer."));
        return;
    }
    QString param;
    if (!QFileInfo(pathIn).isDir())
        param = QLatin1String("/select,");
    param += QDir::toNativeSeparators(pathIn);
    QString command = explorer + " " + param;
    QProcess::startDetached(command);
}
