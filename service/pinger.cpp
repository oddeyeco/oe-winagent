#include "pinger.h"
#include "logger.h"
#include "commonexceptions.h"

#include "winsock2.h"
#include "iphlpapi.h"
#include "icmpapi.h"

#include <QHostInfo>
#include <QElapsedTimer>

CPinger::CPinger()
{
}

qint64 CPinger::RoundTripTime(const QString &sHostAddress)
{
    QElapsedTimer oLookupTimer;
    oLookupTimer.start();

    QHostInfo oHostInfo = QHostInfo::fromName( sHostAddress );
    if( oHostInfo.addresses().isEmpty() )
        throw CPingFailedException( oHostInfo.errorString() );

    QString sIPAddress = oHostInfo.addresses().first().toString();

    quint64 nRoundTripTime = oLookupTimer.elapsed();

    // We declare variables
    HANDLE hIcmpFile;                       // Handler
    unsigned long ipaddr = INADDR_NONE;     // Destination address
    DWORD dwRetVal = 0;                     // Number of replies
    char SendData[32] = "Data Buffer";      // The buffer data being sent
    LPVOID ReplyBuffer = NULL;              // buffer replies
    DWORD ReplySize = 0;                    // Buffer Size responses

    // Set the IP-address of the field qlineEdit
    ipaddr = inet_addr(sIPAddress.toStdString().c_str());
    hIcmpFile = IcmpCreateFile();   // create a handler

    // Select the buffer memory responses
    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    ReplyBuffer = (VOID*) malloc(ReplySize);

    // Call the ICMP echo request function
    dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
                NULL, ReplyBuffer, ReplySize, 1000);

    if (dwRetVal != 0)
    {
        // The structure of the echo response
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
        nRoundTripTime += pEchoReply->RoundTripTime;
    }
    else
    {
        free(ReplyBuffer); // frees memory
        throw CPingFailedException( "ICMP error: " + QString::number(GetLastError() ));

    }
    free(ReplyBuffer); // frees memory

    return nRoundTripTime;

}
