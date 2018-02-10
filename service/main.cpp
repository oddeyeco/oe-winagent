#include "application.h"
#include "configurationmanager.h"
#include <iostream>


#include "commonexceptions.h"
#include "engine.h"
#include "agentinitializer.h"
#include "upload/sendcontroller.h"

int main(int argc, char *argv[])
{
    CApplication a(argc, argv);

    EngineSPtr pEngine = std::make_shared<CEngine>();

    try {
        ConfMgr.RegisterLoadableConfigs( QStringList() << "system" << "oddeye" );
        ConfMgr.LoadConfigurations();

        CAgentInitialzier::InitializeLogger();
        CAgentInitialzier::InitializeEngine( pEngine );

        auto pSendController = new CSendController(pEngine.get());
        QObject::connect(pEngine.get(), &CEngine::sigMetricsCollected, pSendController, &CSendController::SendMetricsData  );

        pEngine->Start();
    }
    catch(std::exception const& oEx)
    {
        std::cout << "Unhandled Exception: "<< oEx.what() << std::endl;
    }
    return a.exec();
}
