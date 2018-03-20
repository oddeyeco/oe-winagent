#ifndef CWINPDHEXCEPTION_H
#define CWINPDHEXCEPTION_H

#include "exception.h"
#include "winperformancedataprovider.h"

////////////////////////////////////////////////////////////////
class CWinPDHException : public CException
{
public:
    inline CWinPDHException(QString sDetails)
        : CException("Performance data collection error: " + sDetails) {}
    inline CWinPDHException(long nStatusCode )
        : CException("Performance data collection error: "
                     + CWinPerformanceDataProvider::GetErrorDescription(nStatusCode)) {}
    inline CWinPDHException(QString const& sMsg, long nStatusCode)
        : CException("Performance data collection error: " + sMsg + " : "
                     + CWinPerformanceDataProvider::GetErrorDescription(nStatusCode)) {}
};

class CWinCounterRetrieveException : public CException
{
public:
    inline CWinCounterRetrieveException(QString sDetails)
        : CException("Failed to retrieve performance counters info: " + sDetails) {}
};
////////////////////////////////////////////////////////////////


#endif // CWINPDHEXCEPTION_H
