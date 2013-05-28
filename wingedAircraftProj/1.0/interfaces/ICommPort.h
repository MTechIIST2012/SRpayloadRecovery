#ifndef ICOMMPORT_H
#define ICOMMPORT_H

#include "typedefs.h"

class ICommPort
{
public:
    virtual ~ICommPort() {}
    virtual bool open()=0;
    virtual bool close()=0;
    virtual bool hasData()=0;
    virtual bool send(BYTE byte)=0;
    virtual BYTE read()=0;
};

#endif // ICOMMPORT_H
