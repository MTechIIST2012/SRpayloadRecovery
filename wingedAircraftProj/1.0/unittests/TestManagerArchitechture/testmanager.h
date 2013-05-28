#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include "abstractmanager.h"

class TestManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit TestManager(int count=1,QObject *parent = 0);
protected:
    virtual bool doAction(ICommand* command);
private:
    int mCount;
};

#endif // TESTMANAGER_H
