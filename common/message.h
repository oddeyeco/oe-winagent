#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QVariant>


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
    AgentStopped,
    CountersInfoDumped
};

using CConfigInfo = QMap<QString, QVariant>;

class CMessage
{
public:
    inline CMessage() = default;
    inline CMessage( QString const& sTitle,
                     QString const& sMessage = QString(),
                     EMessageType eType = EMessageType::Information,
                     QString const& sCommand = QString(),
                     ENotificationEvent eEvent = ENotificationEvent::NoEvent);
    inline CMessage( QString const& sTitle,
                     EMessageType eType,
                     QString const& sMessage = QString(),
                     ENotificationEvent eEvent = ENotificationEvent::NoEvent,
                     QString const& sCommand = QString());
    inline CMessage( ENotificationEvent eEvent,
                     QString const& sCommand = QString(),
                     QString const& sTitle = QString(),
                     QString const& sMessage = QString(),
                     EMessageType eType = EMessageType::Information);

public:
    inline QString GetTitle() const;
    inline void SetTitle( QString const& sTitle );
    inline QString GetMessage() const;
    inline void SetMessage( QString const& sMessage );
    inline EMessageType GetType() const;
    inline void SetType( EMessageType eMessageType );
    inline QString  FullText() const;
    inline bool     HasMessage() const;
    inline bool     IsEmpty() const;

    inline ENotificationEvent GetEvent() const;
    inline void SetEvent( ENotificationEvent eEvent );

    inline QString GetCommand() const;
    inline void SetCommand( QString const& sCommand );

    inline CConfigInfo GetConfigInfo() const;
    inline void SetConfigInfo( CConfigInfo const& oInfo );

private:
    // Content
    QString             m_sTitle;
    QString             m_sMessage;
    EMessageType        m_eType;
    ENotificationEvent  m_eEvent;
    QString             m_sCommand;
    CConfigInfo         m_oConfInfo;
};

CMessage::CMessage(const QString &sTitle, const QString &sMessage, EMessageType eType, QString const& sCommand, ENotificationEvent eEvent)
    : m_sTitle(sTitle),
      m_sMessage(sMessage),
      m_eType(eType),
      m_eEvent( eEvent ),
      m_sCommand( sCommand )
{
}

QString CMessage::GetTitle() const
{
    return m_sTitle;
}

void CMessage::SetTitle(const QString &sTitle)
{
    m_sTitle = sTitle;
}

QString CMessage::GetMessage() const
{
    return m_sMessage;
}

void CMessage::SetMessage(const QString &sMessage)
{
    m_sMessage = sMessage;
}

EMessageType CMessage::GetType() const
{
    return m_eType;
}

void CMessage::SetType(EMessageType eMessageType)
{
    m_eType = eMessageType;
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

bool CMessage::IsEmpty() const
{
    return !HasMessage() && m_eEvent == ENotificationEvent::NoEvent;
}

ENotificationEvent CMessage::GetEvent() const
{
    return m_eEvent;
}

void CMessage::SetEvent(ENotificationEvent eEvent)
{
    m_eEvent = eEvent;
}

QString CMessage::GetCommand() const
{
    return m_sCommand;
}

void CMessage::SetCommand(const QString &sCommand)
{
    m_sCommand = sCommand;
}

CConfigInfo CMessage::GetConfigInfo() const
{
    return m_oConfInfo;
}

void CMessage::SetConfigInfo(const CConfigInfo &oInfo)
{
    m_oConfInfo = oInfo;
}

inline CMessage::CMessage(const QString &sTitle,
                          EMessageType eType,
                          const QString &sMessage,
                          ENotificationEvent eEvent,
                          QString const& sCommand)
    : m_sTitle(sTitle),
      m_sMessage(sMessage),
      m_eType(eType),
      m_eEvent(eEvent),
      m_sCommand(sCommand)
{
}

CMessage::CMessage(ENotificationEvent eEvent,
                   QString const& sCommand,
                   const QString &sTitle,
                   const QString &sMessage,
                   EMessageType eType)
    : m_sTitle(sTitle),
      m_sMessage(sMessage),
      m_eType(eType),
      m_eEvent(eEvent),
      m_sCommand( sCommand )
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
