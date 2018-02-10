#ifndef CSERVICECONTROLLER_H
#define CSERVICECONTROLLER_H

#include <QObject>


///////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Service controller singltone class
///
class CServiceController : public QObject
{
    Q_OBJECT
    using Base = QObject;

private:
    explicit CServiceController(QObject* pParent = nullptr);

public:
    static CServiceController& Instance();

public:
    //
    //  Main Interface
    //
    void Start();
    void Stop();

private:
    //
    //  Content
    //

};

#endif // CSERVICECONTROLLER_H
