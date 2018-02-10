#include "cservicecontroller.h"

CServiceController::CServiceController(QObject *pParent) : QObject(pParent)
{

}

CServiceController &CServiceController::Instance()
{
    static CServiceController oInst;
    return oInst;
}
