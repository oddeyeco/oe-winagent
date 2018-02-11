#ifndef AGENTCONTROLLER_H
#define AGENTCONTROLLER_H

#include <QtServiceController>
#include <QMenu>
#include <QSystemTrayIcon>
#include <memory>

using SystemTrayIconUPtr = std::unique_ptr<QSystemTrayIcon>;


class CAgentController : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    CAgentController(QObject* pParent = nullptr);
    ~CAgentController();

public:
    void CheckAgentState();

private slots:
    void onStart();
    void onStop();
    void onRestart();

private:
    // Content
    SystemTrayIconUPtr  m_pSystemTrayIcon;
    QAction*            m_pactStart;
    QAction*            m_pactStop;
    QAction*            m_pactRestart;
    QtServiceController m_oServiceController;
};

#endif // AGENTCONTROLLER_H
