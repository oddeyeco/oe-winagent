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


////////////////////////////////////////////////////////////////
class CFailedToAddCounterException : public CException
{
    using Base = CException;
public:
    CFailedToAddCounterException( QString const& sMessage,
                                  QString const& sMetricName,
                                  QString const& sCounterPath,
                                  QString const& sInstanceType,
                                  QString const& sInstanceName)
        : Base(sMessage),
          m_sMetricName(sMetricName),
          m_sCounterPath( sCounterPath ),
          m_sInstanceType(sInstanceType),
          m_sInstanceName(sInstanceName)
    {}

public:
    QString GetMetricName() const { return m_sMetricName; }
    QString GetInstanceType() const { return m_sInstanceType; }
    QString GetInstanceName() const { return m_sInstanceName; }

private:
    QString m_sMetricName;
    QString m_sCounterPath;
    QString m_sInstanceType;
    QString m_sInstanceName;
};
////////////////////////////////////////////////////////////////
#endif // COMMONEXCEPTIONS_H
