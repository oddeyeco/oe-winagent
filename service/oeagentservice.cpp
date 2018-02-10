#include "oeagentservice.h"
#include "servicecontroller.h"
#include <iostream>

COEAgentService::COEAgentService(int argc, char **argv)
    : Base( argc, argv, "OddEye Agent" )
{

}

void COEAgentService::start()
{
    try
    {
        CServiceController::Instance().Start();
    }
    catch(std::exception const& oExc)
    {
        std::cout << "OE-Agent start faield: Exception: " << oExc.what() << std::endl;
        QString sErrorMessage = QString( "OE-Agent start faield: %1" ).arg( oExc.what() );
        logMessage( sErrorMessage, QtService::Error );
    }
    catch( ... )
    {
        QString sErrorMessage = "OE-Agent start faield: Unknown exception";
        logMessage( sErrorMessage, QtService::Error );
    }
}

void COEAgentService::stop()
{
    try
    {
        CServiceController::Instance().Stop();
    }
    catch(std::exception const& oExc)
    {
        std::cout << "OE-Agent stop faield: Exception: " << oExc.what() << std::endl;
        QString sErrorMessage = QString( "OE-Agent stop faield: %1" ).arg( oExc.what() );
        logMessage( sErrorMessage, QtService::Error );
    }
    catch( ... )
    {
        QString sErrorMessage = "OE-Agent stop faield: Unknown exception";
        logMessage( sErrorMessage, QtService::Error );
    }
}
