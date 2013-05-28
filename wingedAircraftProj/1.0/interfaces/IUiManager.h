#ifndef IUIMANAGER_H
#define IUIMANAGER_H

#include <QString>

class ICommand;

class IUiManager
{
public:
    virtual ~IUiManager() {}
    virtual void updateUi(ICommand* command)=0;
    virtual void refreshUi()=0;
    virtual void refreshUi(QString window)=0;
};

#endif // IUIMANAGER_H
