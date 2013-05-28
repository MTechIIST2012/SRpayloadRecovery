#include "serialpipe.h"
#include "serialport.h"

SerialPipe::SerialPipe(QString portName)
{
    mSerialPort = 0;
    mPortName = portName;
    mBaud = -1;
}

SerialPipe::~SerialPipe()
{
    if(mSerialPort)
        delete mSerialPort;
}


// serial
void SerialPipe::_serialBegin(int baudrate)
{
    if(!mSerialPort)
    {
        mSerialPort = new SerialPort(0);
    }
    mBaud = baudrate;
    mSerialPort->setPort(mPortName);
    mSerialPort->setRate(mBaud);
    mSerialPort->open(QIODevice::ReadWrite);
}

int SerialPipe::_serialAvailable()
{
    int bAvailable = 0;
    if(mSerialPort)
    {
        bAvailable = (mSerialPort->bytesAvailable() > 0);
    }
    return bAvailable;
}

void SerialPipe::_serialPrintln(char* bytes)
{
    if(mSerialPort)
    {
        mSerialPort->write(bytes,qstrlen(bytes));
        mSerialPort->putChar('\0');
    }
}

void SerialPipe::_serialWrite(_BYTE byte)
{
    if(mSerialPort)
    {
        mSerialPort->putChar(byte);
    }
}

void SerialPipe::_serialPrint(int value)
{
    if(mSerialPort)
    {
        mSerialPort->write(QString::number(value).toAscii());
    }
}

void SerialPipe::_serialPrint(float value)
{
    if(mSerialPort)
    {
        mSerialPort->write(QString::number(value).toAscii());
    }
}

void SerialPipe::_serialPrint(double value)
{
    if(mSerialPort)
    {
        mSerialPort->write(QString::number(value).toAscii());
    }
}

int SerialPipe::_serialRead()
{
    char value=0;
    if(mSerialPort)
    {
        if(mSerialPort->bytesAvailable()>0)
            mSerialPort->read(&value,1);
    }
    return (int)value;
}

void SerialPipe::setPort(QString portName)
{
    mPortName = portName;
}

QString SerialPipe::getPort()
{
    return mPortName;
}

int SerialPipe::getBaud()
{
    return mBaud;
}
