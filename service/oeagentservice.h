#ifndef OEAGENTSERVICE_H
#define OEAGENTSERVICE_H

#include <QtService>
#include "application.h"
#include "oeagentcontrolserver.h"
#include <memory>

using  OEAgentControlServerUPtr = std::unique_ptr<COEAgentControlServer>;

class COEAgentService : public QtService<CApplication>
{
    using Base = QtService<CApplication>;

public:
    COEAgentService(int argc, char **argv);

protected:
    // QtServiceBase interface
    void start();
    void stop();

private:
    OEAgentControlServerUPtr m_pControlServer;
};

#endif // OEAGENTSERVICE_H
