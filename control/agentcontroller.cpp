#include "agentcontroller.h"

#include <QFile>

CAgentController::CAgentController(QObject *pParent)
    : Base(pParent),
      m_pactStart(nullptr),
      m_pactStop(nullptr),
      m_pactRestart(nullptr),
      m_oServiceController( "OddEye Agent" )

{
    m_pSystemTrayIcon = std::make_unique<QSystemTrayIcon>();
    QMenu* pMenu = new QMenu();
    m_pactStart   = pMenu->addAction( "Start", this, SLOT(onStart()));
    m_pactStop    = pMenu->addAction( "Stop", this, SLOT(onStop()) );
    m_pactRestart = pMenu->addAction( "Restart", this, SLOT(onRestart()) );
    m_pSystemTrayIcon->setContextMenu( pMenu );

    m_pSystemTrayIcon->setIcon( QIcon("://icons/agentlogo.png") );
    CheckAgentState();

    m_pSystemTrayIcon->show();
}

CAgentController::~CAgentController()
{}

void CAgentController::CheckAgentState()
{
    if( !m_oServiceController.isInstalled() )
    {
        QString sFilePath = "../Service/Debug/debug/OE-Agent.exe";
        bool bOK = QFile( sFilePath ).exists();
        bOK = m_oServiceController.install(sFilePath);

        //m_pactStart->setDisabled(true);
        m_pactStop->setDisabled(true);
        m_pactRestart->setDisabled(true);
        m_pSystemTrayIcon->setToolTip( "OddEye Agent service not found" );
        return;
    }

    if( m_oServiceController.isRunning() )
    {
        m_pactStart->setDisabled(true);
        m_pactStop->setEnabled(true);
        m_pactRestart->setEnabled(true);
        m_pSystemTrayIcon->setToolTip( "OddEye Agent is running" );
    }
    else // stopped
    {
        m_pactStart->setEnabled(true);
        m_pactStop->setDisabled(true);
        m_pactRestart->setDisabled(true);
        m_pSystemTrayIcon->setToolTip( "OddEye Agent is stopped" );
    }
}

void CAgentController::onStart()
{
    int l = 88;

}

void CAgentController::onStop()
{

}

void CAgentController::onRestart()
{

}
