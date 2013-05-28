#include "tcpsocketpipe.h"
#include <QTcpSocket>

TcpSocketPipe::TcpSocketPipe(QTcpSocket* socket)
{
    mSocket = socket;
}

TcpSocketPipe::~TcpSocketPipe()
{

}

// serial
void TcpSocketPipe::_serialBegin(int baudrate)
{
    // nothing needs to be done here
}

int TcpSocketPipe::_serialAvailable()
{
    int bAvailable = 0;
    if(mSocket)
    {
        bAvailable = (mSocket->bytesAvailable() > 0);
    }
    return bAvailable;
}

void TcpSocketPipe::_serialPrintln(char* bytes)
{
    if(mSocket)
    {
        mSocket->write(bytes,qstrlen(bytes));
        mSocket->putChar('\0');
    }
}

void TcpSocketPipe::_serialWrite(_BYTE byte)
{
    if(mSocket)
    {
        mSocket->putChar(byte);
    }
}

void TcpSocketPipe::_serialPrint(int value)
{
    if(mSocket)
    {
        mSocket->write(QString::number(value).toAscii());
    }
}

void TcpSocketPipe::_serialPrint(float value)
{
    if(mSocket)
    {
        mSocket->write(QString::number(value).toAscii());
    }
}

void TcpSocketPipe::_serialPrint(double value)
{
    if(mSocket)
    {
        mSocket->write(QString::number(value).toAscii());
    }
}

int TcpSocketPipe::_serialRead()
{
    char value=0;
    if(mSocket)
    {
        if(mSocket->bytesAvailable()>0)
            mSocket->read(&value,1);
    }
    return (int)value;
}

void TcpSocketPipe::setSocket(QTcpSocket* socket)
{
    mSocket = socket;
}

QTcpSocket* TcpSocketPipe::getSocket()
{
    return mSocket;
}
