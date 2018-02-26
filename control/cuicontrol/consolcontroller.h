#ifndef CONSOLCONTROLLER_H
#define CONSOLCONTROLLER_H

#include <QObject>
#include <QThread>
#include "agentcontrolclient.h"

class CConsolController : public QObject
{
    Q_OBJECT
    using Base = QObject;
public:
    CConsolController( bool bRunEventLoop,
                       QObject* pParent = nullptr );
    ~CConsolController();

public slots:
    void SetArguments( QStringList lstArgs );
    void ProcessArguments();
    void Quit();

private slots:
    void onNotification( CMessage const& oMsg );

private:
    QThread* m_pThread;
    QStringList m_lstArgs;
};

#endif // CONSOLCONTROLLER_H
