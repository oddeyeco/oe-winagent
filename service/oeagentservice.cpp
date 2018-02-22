#include "oeagentservice.h"
#include "servicecontroller.h"
#include "configurationmanager.h"
#include <iostream>

#include "agentinitializer.h"

COEAgentService::COEAgentService(int argc, char **argv)
    : Base( argc, argv, "OddEye Agent" )
{
    setServiceDescription("Metric collection agent for OddEye");
    setStartupType( QtServiceController::AutoStartup );
    //setServiceFlags(QtServiceBase::CanBeSuspended);

    m_pControlServer = std::make_unique<COEAgentControlServer>();

    //CAgentInitialzier::InitializeLogger();
}

void COEAgentService::start()
{
    m_pControlServer->StartListening();

    bool bStartAgent = ConfMgr.GetRegistrySettings().value( "autostart" , QVariant(false) ).toBool();

    if( bStartAgent )
    {
        // Start
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
}

void COEAgentService::stop()
{
    try
    {
        // save state
        bool bAutostart = CServiceController::Instance().IsStarted();
        ConfMgr.GetRegistrySettings().setValue( "autostart", QVariant(bAutostart) );

        m_pControlServer->StopListening();
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
