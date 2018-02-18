#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "agentcontroller.h"


class CApplication : public QApplication
{
    using Base = QApplication;
public:
    CApplication(int &argc, char **argv);

private:
    // Content
    CAgentController m_oController;
};

#endif // APPLICATION_H
