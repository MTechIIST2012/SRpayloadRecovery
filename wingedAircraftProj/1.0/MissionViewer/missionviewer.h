#ifndef MISSIONVIEWER_H
#define MISSIONVIEWER_H

#include "viewer.h"

class IPlane;
class ICommunication_E;
class IDataPacket_E;
class QTcpSocket;
class QTimer;
class GoogleEarthConnection;

class MissionViewer : public Viewer
{
    Q_OBJECT

public:
    explicit MissionViewer(QWidget *parent = 0);
    ~MissionViewer();
protected:
    virtual QMdiSubWindow* createView(QString viewtype,QString windowname);
    virtual void processPacket(IDataPacket_E* packet);
private slots:
    void onConnActionTriggerd();
    void onGEactionTriggered();
    void readPosPacket(IDataPacket_E* packet);
    void onPacketTimerTimeout();
    void showAbout();
private:
    void createMdiWindows();
    void createMenus();
    void createTcpComm(QString host,int port);

    IPlane* mPlane;
    ICommunication_E* mComm;
    QTcpSocket* mTcpSocket;
    ICommunication_E* createSocketComm(QTcpSocket* socket);
    QTimer* mPacketTimer;
    QTimer* mGEupdateTimer;
    GoogleEarthConnection* mGEconn;
};

#endif // MISSIONVIEWER_H
