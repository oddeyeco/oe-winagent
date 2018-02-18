#include <QApplication>
#include "guicontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGuiController c;

    return a.exec();
}
