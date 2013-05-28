#ifndef SERIALPIPE_H
#define SERIALPIPE_H

#include "ProjectCore_global.h"
#include "gscontrollerpipe.h"

class SerialPort;

class PROJECTCORESHARED_EXPORT SerialPipe : public GSControllerPipe
{
public:
    SerialPipe(QString portName);
    virtual ~SerialPipe();

    // serial
    virtual void _serialBegin(int baudrate);
    virtual int _serialAvailable();
    virtual void _serialPrintln(char* bytes);
    virtual void _serialWrite(_BYTE byte);
    virtual void _serialPrint(int value);
    virtual void _serialPrint(float value);
    virtual void _serialPrint(double value);
    virtual int _serialRead();

    void setPort(QString portName);
    QString getPort();
    int getBaud();
private:
    SerialPort* mSerialPort;
    QString mPortName;
    int mBaud;
};

#endif // SERIALPIPE_H
