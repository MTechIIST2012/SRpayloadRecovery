#ifndef IMANAGER_H
#define IMANAGER_H

#include <QList>

class ICommand;

class IManager
{
public:
    virtual ~IManager() {}
    virtual bool start()=0;
    virtual bool stop()=0;
    virtual void setWriteMaxDelay(int ms)=0;
    virtual void setReadMaxDelay(int ms)=0;
    virtual bool queueCommand(ICommand* command)=0;
    virtual bool removeCommand(ICommand* command)=0;
    virtual ICommand* currentCommand()=0;
    virtual bool isFree()=0;
    virtual int commandCount(int severity=-1)=0;
    virtual void clearCommands(int severity=-1)=0;
};

#endif // IMANAGER_H
