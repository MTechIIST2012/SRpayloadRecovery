#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H

#include "IManager.h"
#include "Utilities_global.h"
#include <QObject>
#include <QReadWriteLock>
#include <QHash>
#include <QQueue>
#include <QThread>

class ManagerThread;

class UTILITIESSHARED_EXPORT AbstractManager : public QObject,public IManager
{
    Q_OBJECT

    friend class ManagerThread;
public:
    explicit AbstractManager(QObject *parent = 0);
    virtual ~AbstractManager();

    //IManager interface
    virtual bool start();
    virtual bool stop();
    virtual void setWriteMaxDelay(int ms);
    virtual void setReadMaxDelay(int ms);
    virtual bool queueCommand(ICommand* command);
    virtual bool removeCommand(ICommand* command);
    virtual ICommand* currentCommand();
    virtual bool isFree();
    virtual int commandCount(int severity=-1);
    virtual void clearCommands(int severity=-1);
signals:
    void errorOccured(QString err);
    void commandReceived(ICommand* command);
    void commandFinished();
protected:
    virtual bool doAction(ICommand* command)=0;
    virtual ICommand* dequeueCommand();
    void deleteCommand(ICommand* command);
private:
    typedef QQueue<ICommand*> CommandQueue;

    ManagerThread* mThread;
    QReadWriteLock mLock;
    QHash<int,CommandQueue*> mHashCommandQueues;
    ICommand* mCurCommand;
    int mReadMaxWait;
    int mWriteMaxWait;
};

class ManagerThread : public QThread
{
    Q_OBJECT
public:
    explicit ManagerThread(AbstractManager* manager,QObject* parent=0);
    ~ManagerThread();
    void run();
    bool hasCommand();
    void exit(int retcode);
signals:
    void errorOccured(QString err);
    void commandFinished();
private slots:
    void onCommandReceive();
private:
    AbstractManager* mManager;
    bool bHasCommand;
    bool bExited;
    bool bExitAccepted;
};

#endif // ABSTRACTMANAGER_H
