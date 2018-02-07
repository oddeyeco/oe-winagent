#include <QCoreApplication>
#include "configurationmanager.h"
#include <iostream>


#include "commonexceptions.h"
#include "engine.h"
#include "engineinitializer.h"
#include "upload/sendcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EngineSPtr pEngine = std::make_shared<CEngine>();

    try {
        ConfMgr.RegisterLoadableConfigs( QStringList() << "system" );
        ConfMgr.LoadConfigurations();

        CEngineInitialzier::InitializeEngine( pEngine );

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
