#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>


enum class EMessageType
{
    Information = 0,
    Warning,
    Error
};

enum class ENotificationEvent : qint32
{
    NoEvent = 0,
    AgentStarted,
    AgentStopped
};

class CMessage
{
public:
    inline CMessage() = default;
    inline CMessage( QString const& sTitle,
                     QString const& sMessage = QString(),
                     EMessageType eType = EMessageType::Information,
                     ENotificationEvent eEvent = ENotificationEvent::NoEvent );
    inline CMessage( QString const& sTitle,
                     EMessageType eType,
                     QString const& sMessage = QString(),
                     ENotificationEvent eEvent = ENotificationEvent::NoEvent );
    inline CMessage( ENotificationEvent eEvent,
                     QString const& sTitle = QString(),
                     QString const& sMessage = QString(),
                     EMessageType eType = EMessageType::Information );

public:
    inline QString GetTitle() const;
    inline QString GetMessage() const;
    inline EMessageType GetType() const;
    inline QString  FullText() const;
    inline bool     HasMessage() const;
    inline ENotificationEvent GetEvent() const;


private:
    // Content
    QString m_sTitle;
    QString m_sMessage;
    EMessageType m_eType;
    ENotificationEvent m_eEvent;
};

CMessage::CMessage(const QString &sTitle, const QString &sMessage, EMessageType eType, ENotificationEvent eEvent)
    : m_sTitle(sTitle),
      m_sMessage(sMessage),
      m_eType(eType),
      m_eEvent( eEvent )
{
}

QString CMessage::GetTitle() const
{
    return m_sTitle;
}

QString CMessage::GetMessage() const
{
    return m_sMessage;
}

EMessageType CMessage::GetType() const
{
    return m_eType;
}

QString CMessage::FullText() const
{
    QString sMessageText = GetTitle();
    if( !GetMessage().isEmpty() )
        sMessageText += (" : " + GetMessage());

    return sMessageText;
}

bool CMessage::HasMessage() const
{
    return !m_sMessage.isEmpty() || !m_sTitle.isEmpty();
}

ENotificationEvent CMessage::GetEvent() const
{
    return m_eEvent;
}

inline CMessage::CMessage(const QString &sTitle,
                          EMessageType eType,
                          const QString &sMessage,
                          ENotificationEvent eEvent)
    : m_sTitle(sTitle),
      m_sMessage(sMessage),
      m_eType(eType),
      m_eEvent(eEvent)
{

}

CMessage::CMessage(ENotificationEvent eEvent,
                   const QString &sTitle,
                   const QString &sMessage,
                   EMessageType eType)
    : m_sTitle(sTitle),
      m_sMessage(sMessage),
      m_eType(eType),
      m_eEvent(eEvent)
{

}

inline QString ToString( EMessageType eType )
{
    switch (eType) {
    case  EMessageType::Warning:
        return QString( "Warning" );
    case  EMessageType::Error:
        return QString( "Error" );

    default:
        return QString( "Information" );
    }
}

inline EMessageType MessageTypeFromString( QString const& sType )
{
    if( sType.compare("Warning", Qt::CaseInsensitive) == 0 )
        return EMessageType::Warning;

    if( sType.compare("Error", Qt::CaseInsensitive) == 0 )
        return EMessageType::Warning;

    return EMessageType::Information;
}

//inline QString ToString( ENotificationEvent eEvent )
//{
//    switch (eEvent) {
//    case  ENotificationEvent::AgentStarted:
//        return QString( "agent_started" );
//    case  ENotificationEvent::AgentStopped:
//        return QString( "agent_stopped" );

//    default:
//        Q_ASSERT(false);
//        return QString();
//    }
//}

//inline ENotificationEvent NotivicationEventFromString( QString const& sType )
//{
//    if( sType.compare("agent_started", Qt::CaseInsensitive) == 0 )
//        return ENotificationEvent::AgentStarted;

//    if( sType.compare("agent_stopped", Qt::CaseInsensitive) == 0 )
//        return ENotificationEvent::AgentStopped;

//    return ENotificationEvent::
//}



#endif // MESSAGE_H
