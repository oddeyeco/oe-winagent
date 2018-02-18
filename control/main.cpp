#include "agentcontroller.h"
#include "application.h"
#include <QMessageBox>

#include <iostream>

int main(int argc, char *argv[])
{
    CApplication a(argc, argv);
    //CAgentController w;
    //w.show();

    //std::cout << "AAAA" << std::endl;

    //CAgentController c;

    return a.exec();
}
