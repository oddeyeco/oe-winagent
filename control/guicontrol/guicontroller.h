#ifndef AGENTCONTROLLER_H
#define AGENTCONTROLLER_H

#include <QtServiceController>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QLocalSocket>
#include <memory>
#include "agentcontrolclient.h"

using SystemTrayIconUPtr = std::unique_ptr<QSystemTrayIcon>;


class CGuiController : public QObject
{
    Q_OBJECT
    using Base = QObject;

public:
    CGuiController(QObject* pParent = nullptr);
    ~CGuiController();

private slots:
    void onStartClicked();
    void onStopClicked();
    void onRestartClicked();

    void onOpenFolder();

    void onExitClicked();

    void onNotification( CMessage const& oMsg );

    void ShowInGraphicalShell(const QString &pathIn);
    void SetStatus( ENotificationEvent eEvent );

private:
    // Content
    SystemTrayIconUPtr  m_pSystemTrayIcon;
    QAction*            m_pactStart;
    QAction*            m_pactStop;
    QAction*            m_pactRestart;
    QAction*            m_pactOpenConfDir;
    QAction*            m_pactOpenLogsDir;
    QString             m_sPriceInfo;
};

#endif // AGENTCONTROLLER_H
