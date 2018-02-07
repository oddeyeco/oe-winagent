#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <QString>
#include <exception>

//////////////////////////////////////////////////////////////////////////////
///
/// Base class for OE exceptions
class CException : public std::exception
{
    using Base = std::exception;
public:
    inline CException(QString const& sMessage);

public:
    inline QString GetMessage() const;
};

// Inline Implementations
inline CException::CException(const QString &sMessage) : Base(sMessage.toLatin1().data()) {}
inline QString CException::GetMessage() const {return QString(Base::what());}
//////////////////////////////////////////////////////////////////////////////


#endif // CEXCEPTION_H
