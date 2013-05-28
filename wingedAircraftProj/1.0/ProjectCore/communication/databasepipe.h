#ifndef DATABASEPIPE_H
#define DATABASEPIPE_H

#include "ProjectCore_global.h"
#include "gscontrollerpipe.h"

class PROJECTCORESHARED_EXPORT DataBasePipe : public GSControllerPipe
{
public:
    DataBasePipe();
    virtual ~DataBasePipe();

    // serial
    virtual void _serialBegin(int baudrate);
    virtual int _serialAvailable();
    virtual void _serialPrintln(_BYTE* bytes);
    virtual void _serialWrite(_BYTE byte);
    virtual void _serialPrint(int value);
    virtual void _serialPrint(float value);
    virtual void _serialPrint(double value);
    virtual int _serialRead();

};

#endif // DATABASEPIPE_H
