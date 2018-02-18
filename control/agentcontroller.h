#ifndef AGENTCONTROLLER_H
#define AGENTCONTROLLER_H

#include <QtServiceController>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QLocalSocket>

#include <memory>

using SystemTrayIconUPtr = std::unique_ptr<QSystemTrayIcon>;


class CAgentController : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    CAgentController(QObject* pParent = nullptr);
    ~CAgentController();

    void Start();
    void Stop();
    void Restart();

private slots:
    void onStartClicked();
    void onStopClicked();
    void onRestartClicked();
    void onExitClicked();

    void onSocketError();
    void onReadyRead();

private:
    // Content
    SystemTrayIconUPtr  m_pSystemTrayIcon;
    QAction*            m_pactStart;
    QAction*            m_pactStop;
    QAction*            m_pactRestart;
    QtServiceController m_oServiceController;
    QLocalSocket*       m_pServerSocket;
};

#endif // AGENTCONTROLLER_H
