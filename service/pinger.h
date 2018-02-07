#ifndef PINGER_H
#define PINGER_H

#include <QString>



class CPinger
{
public:
    CPinger();

public:
    static qint64 RoundTripTime(QString const& sHostAddress);
};

#endif // PINGER_H
