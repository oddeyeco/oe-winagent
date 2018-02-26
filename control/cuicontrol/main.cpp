#include <QCoreApplication>
#include <QTimer>
#include "consolcontroller.h"
#include <iostream>
#include <thread>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Process cmd arguments
    if( a.arguments().size() > 1 )
    {
        CConsolController oController(false);

        QStringList lstCmd = a.arguments();
        lstCmd.removeFirst();

        oController.SetArguments( lstCmd );
        oController.ProcessArguments();
        //QTimer::singleShot( 0, &oController, SLOT(ProcessArguments()) );
        std::this_thread::sleep_for( std::chrono::milliseconds(200) );
        qApp->quit();
        return 0;
    }

    CConsolController oController(true);
    oController.SetArguments( QStringList() << "-help");
    QTimer::singleShot( 0, &oController, SLOT(ProcessArguments()) );


    QTextStream s(stdin);
    //std::cout << "OddEye Agent>";

    while(true)
    {
        QString sValue = s.readLine();
        QStringList lstArgs = sValue.split( " ", QString::SkipEmptyParts );
        if( lstArgs.isEmpty() )
        {
            std::cout << "OddEye Agent>";
            continue;
        }
        // check for quit
        if (lstArgs.first() == QLatin1String("-q") || lstArgs.first() == QLatin1String("-quit")
            || lstArgs.first() == QLatin1String("q") || lstArgs.first() == QLatin1String("quit"))
        {
            qApp->quit();
            break;
        }

        // prepend dummy arg
        //lstArgs.prepend( "dummy" );

        // Process Input
        oController.SetArguments( lstArgs );
        QTimer::singleShot( 0, &oController, SLOT(ProcessArguments()) );
    }

    //oController.ProcessArguments( a.arguments() );

    //return a.exec();
    return 0;
}
