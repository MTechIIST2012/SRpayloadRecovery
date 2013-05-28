#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QString>

class ICommandData;

class ICommand
{
public:
    enum CommandSeverity
    {
        HIGH,
        MEDIUM,
        LOW
    };

    virtual ~ICommand() {}
    virtual int getType()=0;
    virtual void setId(QString id)=0;
    virtual QString getId()=0;
    virtual void setData(ICommandData* data)=0;
    virtual ICommandData* getData()=0;
    virtual void setSeverity(CommandSeverity serverity)=0;
    virtual CommandSeverity getSeverity()=0;
    virtual ICommand* cloneCommand()=0;
};


#endif  // ICOMMAND_H
