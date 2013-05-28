#include "command.h"
#include "ICommandData.h"

Command::Command(int type)
{
    mTypeName = type;
    mData = 0;
    mUsage = 0;
    mSeverity = MEDIUM;
}

Command::~Command()
{
    if(mData)
        delete mData;
}

void Command::setType(int type)
{
    mTypeName = type;
}

int Command::getType()
{
    return mTypeName;
}

void Command::setId(QString id)
{
    mId = id;
}

QString Command::getId()
{
    return mId;
}

void Command::setData(ICommandData* data)
{
    mData = data;
    if(mData)
    {
        setType(mData->getType());
    }
}

ICommandData* Command::getData()
{
    return mData;
}

void Command::setSeverity(CommandSeverity serverity)
{
    mSeverity = serverity;
}

ICommand::CommandSeverity Command::getSeverity()
{
    return mSeverity;
}

ICommand* Command::cloneCommand()
{
    ICommand* command = new Command(mTypeName);
    command->setSeverity(mSeverity);
    command->setId(mId);
    command->setData(mData->cloneData());
    return command;
}
