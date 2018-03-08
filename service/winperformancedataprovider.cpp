#include "winperformancedataprovider.h"
#include "winpdhexception.h"
#include "logger.h"

#include <pdhmsg.h>

#include <QStringList>

#pragma comment(lib, "pdh.lib")

// static member init
HANDLE CWinPerformanceDataProvider::m_hPdhLibrary = NULL;



CWinPerformanceDataProvider::CWinPerformanceDataProvider()
    : m_hQuery(NULL)
{
    Reset();
}

CWinPerformanceDataProvider::~CWinPerformanceDataProvider()
{
    if (m_hQuery)
    {
        PdhCloseQuery(m_hQuery);
    }
}

HCOUNTER CWinPerformanceDataProvider::AddCounter(const wchar_t *wszCounterPath)
{
    HCOUNTER hCounter = NULL;
    auto nStatus = PdhAddEnglishCounter(m_hQuery, wszCounterPath, 0, &hCounter);
    if (nStatus != ERROR_SUCCESS)
    {
        throw CWinPDHException( nStatus );
    }

    return hCounter;
}

void CWinPerformanceDataProvider::RemoveCounter(HCOUNTER hCounter) throw()
{
    Q_ASSERT(hCounter);
    PdhRemoveCounter( hCounter );
}

double CWinPerformanceDataProvider::GetCounterValue(HCOUNTER hCounter)
{
    PDH_FMT_COUNTERVALUE DisplayValue;
    DWORD CounterType;

    auto nStatus = PdhGetFormattedCounterValue( hCounter,
                                          PDH_FMT_DOUBLE,
                                          &CounterType,
                                          &DisplayValue );
    if (nStatus != ERROR_SUCCESS)
    {
        throw CWinPDHException( nStatus );
    }

    return DisplayValue.doubleValue;

}

void CWinPerformanceDataProvider::Reset()
{
    if (m_hQuery)
    {
        PdhCloseQuery(m_hQuery);
    }

    PDH_STATUS nStatus = PdhOpenQuery(NULL, NULL, &m_hQuery);
    if (nStatus != ERROR_SUCCESS)
    {
        throw CWinPDHException(nStatus);
    }

    //
    //  Try to load PDH module to fetch error messages
    //
    if( m_hPdhLibrary == NULL )
        m_hPdhLibrary = LoadLibrary(L"pdh.dll");
    if (NULL == m_hPdhLibrary)
    {
        // TODO: LOG
        //wprintf(L"LoadLibrary failed with %lu\n", GetLastError());
    }
}

void CWinPerformanceDataProvider::UpdateCounters()
{
    Q_ASSERT( m_hQuery );
    auto nStatus = PdhCollectQueryData(m_hQuery);
    if (nStatus != ERROR_SUCCESS)
    {
        throw CWinPDHException(nStatus);
    }
}

QString CWinPerformanceDataProvider::GetErrorDescription(PDH_STATUS nStatusCode)
{
    if( m_hPdhLibrary == NULL )
    {
        // PDH lib is not loaded, so description could not be fetched
        return QString("error code %1").arg(nStatusCode, 0, 16);
    }

    LPWSTR pMessage = NULL;
    DWORD_PTR pArgs[] = { (DWORD_PTR)L"<collectionname>" };
    DWORD dwErrorCode = nStatusCode;

    // Use the arguments array if the message contains insertion points, or you
    // can use FORMAT_MESSAGE_IGNORE_INSERTS to ignore the insertion points.

    if (!FormatMessage(FORMAT_MESSAGE_FROM_HMODULE |
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        /*FORMAT_MESSAGE_IGNORE_INSERTS |*/
        FORMAT_MESSAGE_ARGUMENT_ARRAY,
        m_hPdhLibrary,
        dwErrorCode,
        0,
        (LPWSTR)&pMessage,
        0,
        //NULL))
        (va_list*)pArgs)
        )
    {
        // Format message failed
        return QString("error code %1").arg(nStatusCode, 0, 16);
    }

    QString sMsg = QString::fromWCharArray(pMessage);
    return  sMsg;
}

QStringList CWinPerformanceDataProvider::ExpandCounterPath(QString const& sCounterPathWildcard)
{
    auto pCounterPathWildcard = ToWCharArray( sCounterPathWildcard );

    PDH_STATUS Status;
    PWSTR EndOfPaths;
    PWSTR Paths = NULL;
    DWORD BufferSize = 0;

    Status = PdhExpandCounterPath(pCounterPathWildcard.get(), Paths, &BufferSize);

    while (Status == PDH_MORE_DATA)
    {
        Paths = (PWSTR)malloc(BufferSize * sizeof(WCHAR));
        Status = PdhExpandCounterPath(pCounterPathWildcard.get(), Paths, &BufferSize);
    }

    if (Status != ERROR_SUCCESS)
    {
        if (Paths)
            free(Paths);
        throw CWinPDHException( Status );
    }

    if (Paths == NULL)
    {
        if (Paths)
            free(Paths);
        throw CWinPDHException( "The counter path %s cannot be expanded" );
    }

    EndOfPaths = Paths + BufferSize;

    // On Vista and later operating systems, the buffer is terminated with two
    // null-terminator characters; however, on earlier systems, the buffer is
    // not terminated with two null-terminator characters. This covers both cases.
    QStringList lstExpandedPaths;
    for (PWSTR p = Paths; ((p != EndOfPaths) && (*p != L'\0')); p += wcslen(p) + 1)
    {
        lstExpandedPaths.append( QString::fromWCharArray( p ) );
        //wprintf(L"\n%s", p);
    }

    return lstExpandedPaths;
}



QStringList CWinPerformanceDataProvider::GetObjectInstanceNames(const QString &sObjectName)
{
#define _THROW_FETCH_INSTANCE_FAILED(_msg_, _status_)                                  \
    if (pwsCounterListBuffer != NULL)                                                  \
        free(pwsCounterListBuffer);                                                    \
    if (pwsInstanceListBuffer != NULL)                                                 \
        free(pwsInstanceListBuffer);                                                   \
    throw CWinPDHException( _msg_, _status_);


    auto pObjectName = ToWCharArray( sObjectName );

    PDH_STATUS status = ERROR_SUCCESS;
    LPWSTR pwsCounterListBuffer = NULL;
    DWORD dwCounterListSize = 0;
    LPWSTR pwsInstanceListBuffer = NULL;
    DWORD dwInstanceListSize = 0;
    LPWSTR pTemp = NULL;

    QStringList lstInstanceNames;

    // Determine the required buffer size for the data.
    status = PdhEnumObjectItems(
        NULL,                   // real-time source
        NULL,                   // local machine
        pObjectName.get(),         // object to enumerate
        pwsCounterListBuffer,   // pass NULL and 0
        &dwCounterListSize,     // to get required buffer size
        pwsInstanceListBuffer,
        &dwInstanceListSize,
        PERF_DETAIL_WIZARD,     // counter detail level
        0);

    if (status == PDH_MORE_DATA)
    {
        // Allocate the buffers and try the call again.
        pwsCounterListBuffer = (LPWSTR)malloc(dwCounterListSize * sizeof(WCHAR));
        pwsInstanceListBuffer = (LPWSTR)malloc(dwInstanceListSize * sizeof(WCHAR));

        if (NULL != pwsCounterListBuffer && NULL != pwsInstanceListBuffer)
        {
            status = PdhEnumObjectItems(
                NULL,                   // real-time source
                NULL,                   // local machine
                pObjectName.get(),         // object to enumerate
                pwsCounterListBuffer,
                &dwCounterListSize,
                pwsInstanceListBuffer,
                &dwInstanceListSize,
                PERF_DETAIL_WIZARD,     // counter detail level
                0);

            if (status == ERROR_SUCCESS)
            {
                // Walk the instance list. The list can contain one
                // or more null-terminated strings. The list is terminated
                // using two null-terminator characters.
                for (pTemp = pwsInstanceListBuffer; *pTemp != 0; pTemp += wcslen(pTemp) + 1)
                {
                    lstInstanceNames.append( QString::fromWCharArray(pTemp) );
                }
            }
            else
            {
                _THROW_FETCH_INSTANCE_FAILED( QString("Failed to retrieve second instance names for %1 object").arg(sObjectName), status);
            }
        }
        else
        {
            _THROW_FETCH_INSTANCE_FAILED( QString("Failed to retrieve instance names for %1 object").arg(sObjectName), ERROR_OUTOFMEMORY);
        }
    }
    else
    {
        _THROW_FETCH_INSTANCE_FAILED( QString("Failed to retrieve instance names for %1 object").arg(sObjectName), status);
    }

    if (pwsCounterListBuffer != NULL)
        free( pwsCounterListBuffer );

    if (pwsInstanceListBuffer != NULL)
        free( pwsInstanceListBuffer );

    return lstInstanceNames;
}

QVector<QString> CWinPerformanceDataProvider::GetAllAvailableCounterPaths()
{
#define WIN32_LEAN_AND_MEAN 1

    PDH_STATUS Status;

    DWORD lenObjectList = 0;

    // Get the size to alloc
    Status = PdhEnumObjects(0, 0, 0, &lenObjectList, PERF_DETAIL_WIZARD, false);
    if (Status != PDH_MORE_DATA) {
        throw CWinPDHException( "Unable to retrieve available counter paths", Status );
    }

    //		wprintf(L"Allocation of %u bytes for objectList \n", len * sizeof(_TCHAR));
    PZZTSTR objectList = (PZZTSTR)malloc(lenObjectList * sizeof(wchar_t));

    Status = PdhEnumObjects(0, 0, objectList, &lenObjectList, PERF_DETAIL_WIZARD, false);
    if (Status != ERROR_SUCCESS) {
       throw CWinPDHException( "Unable to retrieve available counter paths", Status );
    }


    QVector<QString> aCounterPaths;

    for (PZZWSTR objectListCurrent = objectList; *objectListCurrent != 0; objectListCurrent += wcslen(objectListCurrent) + 1) {
        DWORD lenCounterList = 0;
        DWORD lenInstanceList = 0;

        Status = PdhEnumObjectItems(0, 0, objectListCurrent, 0, &lenCounterList, 0, &lenInstanceList, PERF_DETAIL_WIZARD, true);
        if (Status != PDH_MORE_DATA) {
            LOG_DEBUG(QString("Unable to retrieve available counter paths (1): %1").arg( GetErrorDescription(Status) ));
            continue;
        }

        //		wprintf(L"Allocation of %u bytes for counterList \n", lenCounterList * sizeof(_TCHAR));
        PZZWSTR counterList = (PZZWSTR)malloc(lenCounterList * sizeof(wchar_t));
        //		wprintf(L"Allocation of %u bytes for instanceList \n", lenInstanceList * sizeof(_TCHAR));
        PZZWSTR instanceList = (PZZWSTR)malloc(lenInstanceList * sizeof(wchar_t));

        Status = PdhEnumObjectItems(0, 0, objectListCurrent, counterList, &lenCounterList, instanceList, &lenInstanceList, PERF_DETAIL_WIZARD, true);
        if (Status != ERROR_SUCCESS) {
            LOG_DEBUG(QString("Unable to retrieve available counter paths (2): %1").arg( GetErrorDescription(Status) ));
            continue;
        }

        if (lenInstanceList == 0) {
            // Walk the counters list. The list can contain one
            // or more null-terminated strings. The list is terminated
            // using two null-terminator characters.
            for (PZZWSTR counterListCurrent = counterList; *counterListCurrent != 0; counterListCurrent += wcslen(counterListCurrent) + 1)
            {
                QString sObjectListCurrent = QString::fromWCharArray( objectListCurrent );
                QString sCounterListCurrent = QString::fromWCharArray( counterListCurrent );
                aCounterPaths.append( QString("\\%1\\%2").arg( sObjectListCurrent , sCounterListCurrent ) );
            }
        }
        else {
            // Same as before, but both
            for (PZZWSTR instanceListCurrent = instanceList; *instanceListCurrent != 0; instanceListCurrent += wcslen(instanceListCurrent) + 1) {
                for (PZZWSTR counterListCurrent = counterList; *counterListCurrent != 0; counterListCurrent += wcslen(counterListCurrent) + 1)
                {
                    QString sObjectListCurrent = QString::fromWCharArray( objectListCurrent );
                    QString sInstanceListCurrent = QString::fromWCharArray( instanceListCurrent );
                    QString sCounterListCurrent = QString::fromWCharArray( counterListCurrent );

                    aCounterPaths.append( QString("\\%1(%2)\\%3").arg(sObjectListCurrent, sInstanceListCurrent, sCounterListCurrent) );
                    //wprintf(L"\\%s(%s)\\%s\n", objectListCurrent, instanceListCurrent, counterListCurrent);
                }
            }
        }

        //		wprintf(L"Free of counterList \n");
        free(counterList);

        //		wprintf(L"Free of instanceList \n");
        free(instanceList);
    }

    free(objectList);

    return aCounterPaths;
}

std::unique_ptr<wchar_t[]> CWinPerformanceDataProvider::ToWCharArray(const QString &sText)
{
    std::unique_ptr<wchar_t[]> pWcharArray( new wchar_t[sText.length() + 1] );
    sText.toWCharArray(pWcharArray.get());
    pWcharArray[sText.length()] = 0;

    return pWcharArray;
}
