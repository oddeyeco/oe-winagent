#ifndef COMMONEXCEPTIONS_H
#define COMMONEXCEPTIONS_H

#include "exception.h"


////////////////////////////////////////////////////////////////
/// Configuration load failed exception
class CConfigLoadFailedException : public CException
{
public:
    inline CConfigLoadFailedException(QString sMsg) : CException(sMsg) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CConfigValueMissingException : public CException
{
public:
    inline CConfigValueMissingException(QString sValue)
        : CException("Cconfig value is missing: " + sValue) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CInvalidConfigValueException : public CException
{
public:
    inline CInvalidConfigValueException(QString sValue)
        : CException("Invalid config value: " + sValue) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CInvalidConfigException : public CException
{
public:
    inline CInvalidConfigException(QString sMsg)
        : CException("Invalid config: " + sMsg) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CCheckerInitializationException : public CException
{
public:
    inline CCheckerInitializationException(QString sMsg)
        : CException("Checker initialization failed: " + sMsg) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CUnableCheckMetricException : public CException
{
public:
    inline CUnableCheckMetricException(QString sMetricName, QString sMsg)
        : CException("Unable to check value of metric " + sMetricName + " : " + sMsg) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CPingFailedException : public CException
{
public:
    inline CPingFailedException(QString sMsg)
        : CException("Ping failed. " + sMsg) {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
class CPriceInfoFetchFailedException : public CException
{
public:
    inline CPriceInfoFetchFailedException(QString sMsg)
        : CException("Failed to retrieve pricing info. " + sMsg) {}
};
////////////////////////////////////////////////////////////////

#endif // COMMONEXCEPTIONS_H
