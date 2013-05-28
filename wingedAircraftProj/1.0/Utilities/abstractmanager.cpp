#include "abstractmanager.h"
#include "project_consts.h"
#include "ICommand.h"
#include <QSet>

AbstractManager::AbstractManager(QObject *parent) :
    QObject(parent)
{
    mCurCommand = 0;
    mThread = 0;
    mReadMaxWait = MANAGER_COMMAND_MAX_WAIT;
    mWriteMaxWait = MANAGER_COMMAND_MAX_WAIT;
}

AbstractManager::~AbstractManager()
{
    stop();
}

bool AbstractManager::start()
{
    if(!mThread)
    {
        mThread = new ManagerThread(this,this);
        connect(mThread,
                SIGNAL(commandFinished()),
                this,
                SIGNAL(commandFinished()));
    }

    mThread->start();
    return true;
}

bool AbstractManager::stop()
{
    this->clearCommands();
    mThread->exit(0);
    delete mThread;
    mThread = 0;
}

void AbstractManager::setWriteMaxDelay(int ms)
{
    mWriteMaxWait = ms;
}

void AbstractManager::setReadMaxDelay(int ms)
{
    mReadMaxWait = ms;
}

bool AbstractManager::queueCommand(ICommand* command)
{
    if(!command)
        return false;

    command = command->cloneCommand();           //   creating a clone
    bool bSucces=false;
    if(mLock.tryLockForWrite(mWriteMaxWait))
    {
        int severity = (int)command->getSeverity();
        CommandQueue* queue = mHashCommandQueues.value(severity,0);
        if(!queue)
        {
            queue = new CommandQueue();
            mHashCommandQueues.insert(severity,queue);
        }
        queue->enqueue(command);
        mLock.unlock();
        bSucces = true;
        emit commandReceived(command);
    }
    return bSucces;
}

bool AbstractManager::removeCommand(ICommand* command)
{
    if(!command)
        return false;

    bool bSucces=false;
    if(mLock.tryLockForWrite(mWriteMaxWait))
    {
        int severity = (int)command->getSeverity();
        CommandQueue* queue = mHashCommandQueues.value(severity,0);
        if(queue)
        {
            queue->removeAll(command);
        }
        mLock.unlock();
        bSucces = true;
    }
    return bSucces;
}

ICommand* AbstractManager::currentCommand()
{
    return mCurCommand;
}

bool AbstractManager::isFree()
{
    return bool(mCurCommand);
}

int AbstractManager::commandCount(int severity)
{
    int count=0;

    if(severity != -1)
    {
        CommandQueue* queue = mHashCommandQueues.value(severity,0);
        if(queue)
        {
            count = queue->count();
        }
    }
    else
    {
        foreach(int sever,mHashCommandQueues.keys())
        {
            count += commandCount(sever);
        }
    }
    return count;
}

void AbstractManager::clearCommands(int severity)
{
    if(severity != -1)
    {
        if(mLock.tryLockForWrite(mWriteMaxWait))
        {
            CommandQueue* queue = mHashCommandQueues.value(severity,0);
            if(queue)
            {
                qDeleteAll(queue->toSet());
                queue->clear();
            }
            mLock.unlock();
        }
    }
    else
    {
        foreach(int sever,mHashCommandQueues.keys())
        {
            clearCommands(sever);
        }
    }
}

//protected
ICommand* AbstractManager::dequeueCommand()
{
    ICommand* command=0;
    if(mLock.tryLockForWrite(mReadMaxWait))
    {
        for(int severity=ICommand::HIGH;
            severity <= ICommand::LOW;
            severity++)
        {
            CommandQueue* queue = mHashCommandQueues.value(severity,0);
            if(queue)
            {
                if(!queue->isEmpty())
                {
                    command = queue->dequeue();
                    if(command)
                    {
                        break;
                    }
                }
            }
        }
        mLock.unlock();
    }
    return command;
}

void AbstractManager::deleteCommand(ICommand* command)
{
    delete command;
}

//////////////////////ManagerThread/////////////////////////////////////////////

ManagerThread::ManagerThread(AbstractManager* manager,QObject* parent)
    : QThread(parent)
{
    bHasCommand = false;
    bExited = false;
    bExitAccepted = false;
    mManager = manager;

    connect(mManager,
            SIGNAL(commandReceived(ICommand*)),
            this,
            SLOT(onCommandReceive()));
}

ManagerThread::~ManagerThread()
{
    bExited = true;
    while(!bExitAccepted);
}

void ManagerThread::run()
{
    while(!bExited)
    {
        if(bHasCommand && mManager)
        {
            try
            {
                ICommand* command = mManager->dequeueCommand();
                while(command && !bExited)
                {
                    if(command)
                    {
                        mManager->mCurCommand = command;
                        mManager->doAction(command);
                    }

                    if(!bExited)
                    {
                        mManager->deleteCommand(command);
                        command = mManager->dequeueCommand();
                    }
                };
            }
            catch(QString err)
            {
                emit errorOccured(err);
            }
            if(!bExited)
            {
                mManager->mCurCommand = 0;
                bHasCommand = false;
                emit commandFinished();
            }
        }
    }

    if(bExited)
    {
        bExitAccepted = true;
    }
}

bool ManagerThread::hasCommand()
{
    return bHasCommand;
}

void ManagerThread::exit(int retcode)
{
    bExited = true;
    while(!bExitAccepted);
    QThread::exit(retcode);
}

void ManagerThread::onCommandReceive()
{
    bHasCommand = true;
}
