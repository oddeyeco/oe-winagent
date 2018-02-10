#include "application.h"
#include <iostream>

#include "servicecontroller.h"

int main(int argc, char *argv[])
{
    CApplication a(argc, argv);

    try {
        CServiceController::Instance().Start();
    }
    catch(std::exception const& oEx)
    {
        std::cout << "Unhandled Exception: "<< oEx.what() << std::endl;
    }
    return a.exec();
}
