#ifndef IGENERALMANAGER_H
#define IGENERALMANAGER_H

class ICommManager;
class IUiManager;

class IGeneralManager
{
public:
    virtual ~IGeneralManager() {}
    virtual bool init()=0;
    virtual void setCommManager(ICommManager* mgr)=0;
    virtual ICommManager* getCommManager()=0;
    virtual void setUiManager(IUiManager* mgr)=0;
    virtual IUiManager* getUiManager()=0;
};

#endif // IGENERALMANAGER_H
