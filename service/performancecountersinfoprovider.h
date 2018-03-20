#ifndef PERFORMANCECOUNTERSINFOPROVIDES_H
#define PERFORMANCECOUNTERSINFOPROVIDES_H

#include <QString>
#include <QStringList>
#include <windows.h>

struct SCounterInfo
{
    QString sPath;
    QString sDescription;
};

using CounterInfoList = QList<SCounterInfo>;

struct SPerformanceObjectInfo
{
    QString         sName;
    QString         sDescription;
    CounterInfoList lstCounters;
    QStringList     lstInstances;
};

using PerformanceObjectsInfoList = QList<SPerformanceObjectInfo>;


class CPerformanceCountersInfoProvider
{
public:
    CPerformanceCountersInfoProvider();

    static PerformanceObjectsInfoList RetrieveCountersInfo();

private:
    static PerformanceObjectsInfoList PrintObjectNames(DWORD dwNumberOfObjects, BOOL fIncludeCounters, BOOL fIncludeInstances);
};

#endif // PERFORMANCECOUNTERSINFOPROVIDES_H
