#include "consolcontroller.h"
#include <QDebug>
#include <iostream>

CConsolController::CConsolController(QObject* pParent)
    : Base( pParent ),
      m_pThread(nullptr)
{
    m_pThread = new QThread(this);

    AgentController.moveToThread( m_pThread );
    this->moveToThread( m_pThread );

    // connect
    connect( &AgentController, &CAgentControlClient::sigNotification,
             this,             &CConsolController::onNotification );

    m_pThread->start();
}

CConsolController::~CConsolController()
{
    m_pThread->quit();
    m_pThread->wait();
}

void CConsolController::SetArguments(QStringList lstArgs)
{
    m_lstArgs = lstArgs;
}

void CConsolController::ProcessArguments()
{
    QStringList args = m_lstArgs;

    if (args.size() > 1)
    {
        QString a =  args.at(1);
        if (a == QLatin1String("-start") || a == QLatin1String("start"))
        {
            //printf("OddEye Agent is Starting\n");
            AgentController.Start();
        }
        else if (a == QLatin1String("-stop") || a == QLatin1String("stop") )
        {
            AgentController.Stop();
        }
        else if (a == QLatin1String("-r") || a == QLatin1String("-restart")
                 || a == QLatin1String("r") || a == QLatin1String("restart"))
        {
            AgentController.Restart();
        }
        else if (a == QLatin1String("-status") || a == QLatin1String("status") )
        {
            AgentController.Status();
        }
        else if (a == QLatin1String("-v") || a == QLatin1String("-version")
                 || a == QLatin1String("v") || a == QLatin1String("version"))
        {
            std::cout << "Version: 0.5" << std::endl;
            std::cout << "OddEye Agent>";
        }
        else  if (   a == QLatin1String("-h") || a == QLatin1String("-help")
                  || a == QLatin1String("h")  || a == QLatin1String("help") )
        {
              printf("OddEye Agent Controller -[start|stop|r|status|v|q|h]\n"
                     "\t-start\t\t: Start OddEye Agent\n"
                     "\t-stop\t\t: Stop OddEye Agent\n"
                     "\t-r(estart)\t: Restart OddEye Agent\n"
                     "\t-r(estart)\t: Query OddEye Agent status\n"
                     "\t-v(ersion)\t: Print version information.\n"
                     "\t-q(uit)   \t: Quit terminal\n"
                     "\t-h(elp)   \t: Show this help\n");
              std::cout << "OddEye Agent>";
        }
        else
        {
            std::cerr << "Command not found: " << a.toStdString() << std::endl;
            std::cout << "OddEye Agent>";
        }
    }
}

void CConsolController::onNotification(const CMessage &oMsg)
{
    if( oMsg.IsEmpty() )
        return;

    if( oMsg.HasMessage() )
    {
        QString sMessageText =  ToString( oMsg.GetType() ) + ": " + oMsg.FullText();
        std::cout << "\r";
        if( oMsg.GetType() == EMessageType::Error )
            std::cerr << sMessageText.toStdString() << std::endl;
        else
            std::cout << sMessageText.toStdString() << std::endl;

        std::cout << "OddEye Agent>";
    }
    else
    {
        QString sEventText;
        switch (oMsg.GetEvent()) {
        case ENotificationEvent::AgentStarted:
            sEventText = "OddEye Agent is running";
            break;
        case ENotificationEvent::AgentStopped:
            sEventText = "OddEye Agent is stopped";
            break;
        default:
            break;
        }

        if( !sEventText.isEmpty() )
        {
            std::cout << "\r";
            std::cout << sEventText.toStdString() << std::endl;
            std::cout << "OddEye Agent>";
        }
    }
}


