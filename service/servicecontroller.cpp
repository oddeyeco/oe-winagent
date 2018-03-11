#include "servicecontroller.h"
#include "configurationmanager.h"
#include "agentinitializer.h"
#include "pricinginfoprovider.h"
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
        // Create Engine if not exists
        if( !m_pEngine )
        {
            m_pEngine.reset( new CEngine() );
            QObject::connect( m_pEngine.get(), &CEngine::sigMetricsCollected, &CSendController::Instance(), &CSendController::SendMetricsData );
        }

        // Register Loadable Configs
        ConfMgr.RegisterLoadableConfigs( QStringList()
                                         << "system"
                                         << "oddeye"
                                         << ".net"
                                         << "hyper-v"

                                         );
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
        CSendController::Instance().TurnOn();

        // Initialize Engine
        CAgentInitialzier::InitializeEngine( m_pEngine.get() );

        // Start Engine
        m_pEngine->Start();
        LOG_INFO( ":::AGENT STARTED:::" );

        // Calculate aproximate price
        m_oPriceInfoFetcher.SetMetricsCount( m_pEngine->GetLastMetricsCount() );
        double dIntervalSec = double( m_pEngine->GetUpdateInterval() ) / 1000.;
        m_oPriceInfoFetcher.SetUpdatesIntervalSec( dIntervalSec );
        try {
        m_oPriceInfoFetcher.CalculatePrice();
        } catch(std::exception const& oEx)
        {
            LOG_ERROR( std::string("Calculate price failed on agent start: ") + oEx.what() );
        }
    }
    catch( std::exception& oExc )
    {
        LOG_ERROR( std::string("Start Failed: ") + oExc.what() );
        std::cout << "Start Failed: " << oExc.what() << std::endl;
        // rethrow
        throw oExc;
    }
    catch( ... )
    {
        LOG_ERROR( std::string("Start Failed: Unknown Exception") );
    }

    emit sigStarted();
}

void CServiceController::Stop()
{
    if( m_pEngine )
    {
        m_pEngine->Stop();
        m_pEngine->RemoveAllCheckers();
    }

    CSendController::Instance().TurnOff();
    LOG_INFO( "___AGENT_STOPPED___" );

    emit sigStopped();
}

bool CServiceController::IsStarted() const
{
    if( m_pEngine && m_pEngine->IsStarted() )
        return true;

    return false;
}

double CServiceController::GetPriceInfo()
{
    return m_oPriceInfoFetcher.GetLastCalculatedPrice();
}
