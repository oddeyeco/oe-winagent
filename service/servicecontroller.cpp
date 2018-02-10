#include "servicecontroller.h"
#include "configurationmanager.h"
#include "agentinitializer.h"
#include "upload/sendcontroller.h"

#include <iostream>

CServiceController::CServiceController(QObject *pParent)
    : QObject(pParent)
{

}

CServiceController &CServiceController::Instance()
{
    static CServiceController oInst;
    return oInst;
}

void CServiceController::Start()
{
    try
    {
        // Reset Engine
        m_pEngine.reset( new CEngine() );

        // Register Loadable Configs
        ConfMgr.RegisterLoadableConfigs( QStringList() << "system" << "oddeye" );
        // Load Configurations
        ConfMgr.LoadConfigurations();

        // Initialize Logger
        CAgentInitialzier::InitializeLogger();
    }
    catch( std::exception& oExc )
    {
        std::cout << "Start failed: " << oExc.what() << std::endl;
        // rethrow
        throw oExc;
    }

    try
    {
        // Create Send Controller
        m_pSendController.reset( new CSendController );

        // Initialize Engine
        CAgentInitialzier::InitializeEngine( m_pEngine.get() );

        QObject::connect( m_pEngine.get(), &CEngine::sigMetricsCollected, m_pSendController.get(), &CSendController::SendMetricsData );

        // Start Engine
        m_pEngine->Start();
    }
    catch( std::exception& oExc )
    {
        LOG_ERROR( std::string("Start Failed: ") + oExc.what() );
        std::cout << "Start Failed: " << oExc.what() << std::endl;
        // rethrow
        throw oExc;
    }
}

void CServiceController::Stop()
{
    if( m_pEngine )
    {
        m_pEngine->Stop();
        m_pEngine.reset();
    }

    if( m_pSendController )
    {
        m_pSendController.reset();
    }
}
