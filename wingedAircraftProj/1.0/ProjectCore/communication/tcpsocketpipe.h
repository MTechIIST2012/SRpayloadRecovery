#ifndef TCPSOCKETPIPE_H
#define TCPSOCKETPIPE_H

#include "ProjectCore_global.h"
#include "gscontrollerpipe.h"

class QTcpSocket;

class PROJECTCORESHARED_EXPORT TcpSocketPipe : public GSControllerPipe
{
public:
    TcpSocketPipe(QTcpSocket* socket);
    virtual ~TcpSocketPipe();

    // serial
    virtual void _serialBegin(int baudrate);
    virtual int _serialAvailable();
    virtual void _serialPrintln(char* bytes);
    virtual void _serialWrite(_BYTE byte);
    virtual void _serialPrint(int value);
    virtual void _serialPrint(float value);
    virtual void _serialPrint(double value);
    virtual int _serialRead();

    void setSocket(QTcpSocket* socket);
    QTcpSocket* getSocket();
private:
    QTcpSocket* mSocket;
};

#endif // TCPSOCKETPIPE_H
