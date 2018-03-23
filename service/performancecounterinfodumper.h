#ifndef CPERFORMANCECOUNTERINFODUMPER_H
#define CPERFORMANCECOUNTERINFODUMPER_H

#include <QSet>
#include <QString>

class CPerformanceCounterInfoDumper
{
    CPerformanceCounterInfoDumper();
public:
    static CPerformanceCounterInfoDumper& Instance();

public:
    void DumpCountersInfo();
    void SetDumpDirPath(QString const& sPath);
    QString GetDumpFilePath() const;

    void AddToFilter(QString sFilter );

private:
    bool ContainesOneOf(const QString &sSourceString, const QStringList &lstLexems);

private:
    // content
    QString m_sDumpFileName;
    QSet<QString> m_setFilter;
};

#endif // CPERFORMANCECOUNTERINFODUMPER_H
