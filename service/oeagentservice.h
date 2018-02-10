#ifndef OEAGENTSERVICE_H
#define OEAGENTSERVICE_H

#include <QtService>
#include "application.h"

class COEAgentService : public QtService<CApplication>
{
    using Base = QtService<CApplication>;

public:
    COEAgentService(int argc, char **argv);

protected:
    // QtServiceBase interface
    void start();
    void stop();
};

#endif // OEAGENTSERVICE_H
