#include <QApplication>
#include <Windows.h>
#include "guicontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // check another instance existance
    HANDLE hHandle = CreateMutex( NULL, TRUE, L"oe_agent_sys_tray" );
    if( ERROR_ALREADY_EXISTS == GetLastError() )
    {
       // Program already running somewhere
       return(1);
    }

    CGuiController c;

    int nResult = a.exec();

    // Upon app closing:
    ReleaseMutex( hHandle ); // Explicitly release mutex
    CloseHandle( hHandle );
    return nResult;
}
