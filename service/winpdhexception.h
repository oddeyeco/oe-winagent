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
////////////////////////////////////////////////////////////////


#endif // CWINPDHEXCEPTION_H
