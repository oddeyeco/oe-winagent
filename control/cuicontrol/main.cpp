#include <QCoreApplication>
#include <QTimer>
#include "consolcontroller.h"
#include <iostream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CConsolController oController;

    // Process cmd arguments
    if( a.arguments().size() > 1 )
    {
        oController.SetArguments( a.arguments() );
        QTimer::singleShot( 0, &oController, SLOT(ProcessArguments()) );
    }

    QTextStream s(stdin);
    std::cout << "OddEye Agent>";

    while(true)
    {
        QString sValue = s.readLine();
        QStringList lstArgs = sValue.split( " ", QString::SkipEmptyParts );

        // check for quit
        if (lstArgs.first() == QLatin1String("-q") || lstArgs.first() == QLatin1String("-quit")
            || lstArgs.first() == QLatin1String("q") || lstArgs.first() == QLatin1String("quit"))
        {
            qApp->quit();
            break;
        }

        // prepend dummy arg
        lstArgs.prepend( "dummy" );

        // Process Input
        oController.SetArguments( lstArgs );
        QTimer::singleShot( 0, &oController, SLOT(ProcessArguments()) );
    }

    //oController.ProcessArguments( a.arguments() );

    //return a.exec();
    return 0;
}
