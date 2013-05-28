#include "controllersimulationpipe.h"
#include "planecontrollersimulator.h"
#include "serialport.h"
#include <QTime>
#include <QTimer>

ControllerSimulationPipe::ControllerSimulationPipe(PlaneControllerSimulator* planeConSimulator)
{
    mPlaneConSimulator = planeConSimulator;
    mSerialPort = 0;
}

ControllerSimulationPipe::~ControllerSimulationPipe()
{
    if(mSerialPort)
    {
        mSerialPort->close();
        delete mSerialPort;
    }
}

void  ControllerSimulationPipe::_delay(unsigned long ms)
{
    QTime reqTime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < reqTime);
}

void ControllerSimulationPipe::_pinMode(INT_8 portid,INT_8 mode)
{
    mPlaneConSimulator->setPinMode(portid,mode);
}

int  ControllerSimulationPipe::_digitalRead(INT_8 portid)
{
    return mPlaneConSimulator->getPinValue(portid);
}

void    ControllerSimulationPipe::_digitalWrite(INT_8 portid,INT_8 value)
{
    mPlaneConSimulator->setPinValue_embedded(portid,value);
}

// serial
void   ControllerSimulationPipe::_serialBegin(int baudrate)
{
    if(!mSerialPort)
    {
        mSerialPort = new SerialPort(0); 
    }
    QString portname = mPlaneConSimulator->getSerialPort();
    mSerialPort->setPort(portname);
    mSerialPort->setRate(baudrate);
    mSerialPort->open(QIODevice::ReadWrite);
}

int   ControllerSimulationPipe::_serialAvailable()
{
    int bAvailable = 0;
    if(mSerialPort)
    {
        bAvailable = mSerialPort->bytesAvailable();
    }
    return bAvailable;
}

void   ControllerSimulationPipe::_serialPrintln(char* bytes)
{
    if(mSerialPort)
    {
        mSerialPort->write(bytes,qstrlen(bytes));
        mSerialPort->putChar('\0');
    }
}

void   ControllerSimulationPipe::_serialWrite(_BYTE byte)
{
    if(mSerialPort)
    {
        mSerialPort->putChar(byte);
    }
}

void   ControllerSimulationPipe::_serialPrint(int value)
{
    if(mSerialPort)
    {
        mSerialPort->write(QString::number(value).toAscii());
    }
}

void   ControllerSimulationPipe::_serialPrint(double value)
{
    if(mSerialPort)
    {
        mSerialPort->write(QString::number(value).toAscii());
    }
}

void   ControllerSimulationPipe::_serialPrint(float value)
{
    if(mSerialPort)
    {
        mSerialPort->write(QString::number(value).toAscii());
    }
}

int   ControllerSimulationPipe::_serialRead()
{
    char value=0;
    if(mSerialPort)
    {
        if(mSerialPort->bytesAvailable()>0)
            mSerialPort->read(&value,1);
    }
    return (int)value;
}

void ControllerSimulationPipe::_timer1_initialize(long microseconds)
{
    mPlaneConSimulator->_timer1_initialize(microseconds);
}

void ControllerSimulationPipe::_timer1_attachInterrupt(void (*isr)(), long microseconds)
{
    mPlaneConSimulator->_timer1_attachInterrupt(isr,microseconds);
}

void ControllerSimulationPipe::_timer1_detachInterrupt()
{
    mPlaneConSimulator->_timer1_detachInterrupt();
}

void ControllerSimulationPipe::serialClose()
{
    if(mSerialPort)
    {
        mSerialPort->close();
    }
}

