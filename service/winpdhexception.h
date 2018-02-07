#ifndef COMMONEXCEPTIONS_H
#define COMMONEXCEPTIONS_H

#include "exception.h"
#include "winperformancedataprovider.h"

////////////////////////////////////////////////////////////////
class CWinPDHException : public CException
{
public:
    inline CWinPDHException(QString sDetails)
        : CException("Performance data collection failed: " + sDetails) {}
    inline CWinPDHException(long nStatusCode )
        : CException("Performance data collection failed: "
                     + CWinPerformanceDataProvider::GetErrorDescription(nStatusCode)) {}
};
////////////////////////////////////////////////////////////////


#endif // COMMONEXCEPTIONS_H
