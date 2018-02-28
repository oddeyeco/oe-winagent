#include "application.h"
#include <iostream>

#include "oeagentservice.h"

int main(int argc, char *argv[])
{
    COEAgentService oAgentService(argc, argv);
    return oAgentService.exec();
}
