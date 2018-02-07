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
class CPingFailedException : public CException
{
public:
    inline CPingFailedException(QString sMsg)
        : CException("Ping failed. " + sMsg) {}
};
////////////////////////////////////////////////////////////////

#endif // COMMONEXCEPTIONS_H
