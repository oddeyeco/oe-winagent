#ifndef CPRICINGINFOPROVIDER_H
#define CPRICINGINFOPROVIDER_H

#include <QJsonObject>
#include <QObject>

class CPricingInfoProvider : public QObject
{
    Q_OBJECT
public:
    explicit CPricingInfoProvider(QObject *parent = 0);

public:
    void SetMetricsCount(int nMetricCount);
    void SetUpdatesIntervalSec(int nUpdateSec);
    double CalculatePrice();
    double GetLastCalculatedPrice() const;

private:
    QJsonObject RequestPriceingInfo();
signals:

public slots:

private:
    int m_nMetricCount;
    int m_nUpdateSec;
    double m_dLastCalculatedPrice;
};

#endif // CPRICINGINFOPROVIDER_H
