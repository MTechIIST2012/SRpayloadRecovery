#ifndef ICOMMMANAGER_H
#define ICOMMMANAGER_H

class ICommand;
class ICommPort;

class ICommManager
{
public:
    virtual ~IinputManager() {}
    virtual void send(ICommand* cmd)=0;
    virtual ICommand* read()=0;
    virtual bool hasData()=0;
    virtual void setPort(ICommPort* port)=0;
    virtual ICommPort* getPort()=0;
};

#endif // ICOMMMANAGER_H
