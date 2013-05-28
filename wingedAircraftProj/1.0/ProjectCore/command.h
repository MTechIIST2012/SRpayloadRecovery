#ifndef COMMAND_H
#define COMMAND_H

#include "ICommand.h"
#include "commandtypes.h"
#include "ProjectCore_global.h"

class PROJECTCORESHARED_EXPORT Command : public ICommand
{
public:
    Command(int type=COMMANDTYPE_UNKNOWN);
    virtual ~Command();
    virtual void setType(int type);

    // ICommand interface
    virtual int getType();
    virtual void setId(QString id);
    virtual QString getId();
    virtual void setData(ICommandData* data);
    virtual ICommandData* getData();
    virtual void setSeverity(CommandSeverity serverity);
    virtual CommandSeverity getSeverity();
    virtual ICommand* cloneCommand();
private:
    int mTypeName;
    QString mId;
    ICommandData* mData;
    CommandSeverity mSeverity;
    int mUsage;
};

#endif // COMMAND_H
