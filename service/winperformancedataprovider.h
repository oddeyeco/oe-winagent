#ifndef CWINPERFORMANCEDATAPROVIDER_H
#define CWINPERFORMANCEDATAPROVIDER_H

//
//  Includes
//
#include <QString>
#include <pdh.h>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////
///
/// class CWinPerformanceDataProvider
///
class CWinPerformanceDataProvider
{    
public:
    CWinPerformanceDataProvider();
    ~CWinPerformanceDataProvider();

public:
    //
    //	Main Interface
    //
    HCOUNTER AddCounter(wchar_t const* wszCounterPath);
    void	 RemoveCounter(HCOUNTER hCounter);
    double   GetCounterValue(HCOUNTER hCounter);
    void     Reset();

    void UpdateCounters();

    static QString GetErrorDescription( PDH_STATUS nStatusCode );
    static QStringList ExpandCounterPath( wchar_t* pCounterPathWildcard );
    static QStringList FetchMissingCounterPathValues( wchar_t* pCounterPathWildcard );

private:
    //
    //	Content
    //
    HQUERY m_hQuery;
    static HANDLE m_hPdhLibrary;
};

using WinPerformanceDataProviderSPtr = std::shared_ptr<CWinPerformanceDataProvider>;
using WinPerformanceDataProviderConstSPtr = std::shared_ptr<const CWinPerformanceDataProvider>;
////////////////////////////////////////////////////////////////////////////////////////

#endif // CWINPERFORMANCEDATAPROVIDER_H
