#include "missionviewer.h"
#include "mdi3dview.h"
#include "mdiplaneview.h"
#include "mdiplanemeterpannel.h"
#include "planecontrolswidget.h"
#include "plane.h"
#include "connectiondialog.h"
#include "Communication_E.h"
#include "DataPackets_E.h"
#include "tcpsocketpipe.h"
#include "googleearthconnection.h"
#include "aboutdialog.h"
#include "MissionViewerCommon.h"
#include <qglabstractscene.h>
#include <QMenu>
#include <QMenuBar>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTimer>
#include <QIcon>
#include <QApplication>

MissionViewer::MissionViewer(QWidget *parent) :
    Viewer(parent)
{
    setWindowTitle("MissionViewer");
    QIcon icon(":/icons/icons/IIST_Logo.png");
    setWindowIcon(icon);

    mPlane = new Plane(this);
    mComm = 0;
    mTcpSocket = 0;
    mPacketTimer = 0;
    mGEupdateTimer = 0;
    mGEconn = 0;

    createMdiWindows();
    createMenus();
    setViewTypes(glstViewTypes);

    connect(this,
            SIGNAL(aboutDialogReqest()),
            this,
            SLOT(showAbout()));
}

MissionViewer::~MissionViewer()
{
    if(mComm)
        delete mComm;
    if(mTcpSocket)
        delete mTcpSocket;
}

QMdiSubWindow* MissionViewer::createView(QString viewtype,QString windowname)
{
//    Mdi3dView* window = new Mdi3dView(this);
//    QGLAbstractScene* scene = QGLAbstractScene::loadScene(QLatin1String("../../models/caravanW.obj"));
//    window->setScene(scene);
//    ObjectInfoHash objInfoHash;
//    objInfoHash.insert("PlaneStruct",ObjectViewInfo());
//    objInfoHash.insert("Cylinder",ObjectViewInfo());
//    window->setScene(scene);
//    window->setObjectViewInfo(objInfoHash);
//    window->setWindowTitle(windowname);

    QMdiSubWindow* window = 0;
    if(viewtype == VIEWNAME_3DVIEW)
    {
        window = new MdiPlaneView(PLANEVIEWER_SETTINGS,this);
        ((MdiPlaneView*)window)->setPlane(mPlane);
        //addMdiSubWindow("planeview",planeview);
        window->setWindowTitle(windowname);
    }
    else if(viewtype == VIEWNAME_METERPANNEL)
    {
        window = new MdiPlaneMeterPannel(mPlane,this);
        //addMdiSubWindow("meterpannel",meterpannel);
        window->setWindowTitle(windowname);
    }
    return window;
}

void MissionViewer::onConnActionTriggerd()
{
    ConnectionDialog dlg;
    if(dlg.exec())
    {
        QString host = dlg.getHost();
        int port = dlg.getPort();
        createTcpComm(host,port);
    }
}

void MissionViewer::onGEactionTriggered()
{
    if(!mGEconn)
    {
        mGEconn = new GoogleEarthConnection(QCoreApplication::applicationDirPath(),
                                            GOOGLE_EARTH_SETTINGS,
                                            mPlane,
                                            this);
    }
    if(!mGEupdateTimer)
    {
        mGEupdateTimer = new QTimer(this);
        mGEupdateTimer->setInterval(1000);

        connect(mGEupdateTimer,
                SIGNAL(timeout()),
                mGEconn,
                SLOT(updateGE()));
    }
    mGEconn->startGE();
    mGEupdateTimer->start();
}

void MissionViewer::readPosPacket(IDataPacket_E* packet)
{
    Packet_Location* posPacket = dynamic_cast<Packet_Location*>(packet);       // Todo: needs to be modified for checksum.
    if(posPacket)
    {
        if(posPacket->hasCheckSumMatched())
        {
            float altitude = posPacket->getPos().altitude * 0.3048;  // in meters
            float latitude = posPacket->getPos().latitude;
            float longitude = posPacket->getPos().longitude;

            IPlane::PlaneOrientation orientation;
            orientation.pitch = posPacket->getPitch();
            orientation.roll = posPacket->getRoll();
            orientation.yaw = posPacket->getYaw();

            mPlane->setAltitude(altitude);
            mPlane->setLatitude(latitude);
            mPlane->setLongitude(longitude);
            mPlane->setOrientation(orientation);

        }
    }
}

void MissionViewer::onPacketTimerTimeout()
{
    if(!mComm)
        return;

    mComm->updateBuffer();
    IDataPacket_E* packet = mComm->readPacket();
    while(packet)
    {
        processPacket(packet);
        delete packet;
        packet = mComm->readPacket();
    }
}

void MissionViewer::showAbout()
{
    AboutDialog dlg;
    dlg.exec();
}

void MissionViewer::processPacket(IDataPacket_E* packet)
{
    switch(packet->type())
    {
    case PACKET_CHECK_CONNECTION:
        // connection is handled by tcp
        break;
    case PACKET_CHECK_CONNECTION_REPLY:
        break;
    case PACKET_REQUEST:
        break;
    case PACKET_RESEND_REQUEST:
        break;
    case PACKET_MODECHANGE_CMD:
        break;
    case PACKET_COMMAND:
        break;
    case PACKET_LOCATION:
        readPosPacket(packet);
        break;
    case PACKET_PATH:
        break;
    case PACKET_DATA:
        break;
    case PACKET_HUMAN_CONTROL:
        break;
    case PACKET_DEBUG_INFO:
        break;
    };
}

void MissionViewer::createMdiWindows()
{
    foreach(QString viewtype,glstViewTypes)
    {
        QMdiSubWindow* view = createView(viewtype,viewtype);
        addMdiSubWindow(viewtype,view);
    }
}

void MissionViewer::createMenus()
{
    QMenu* settingsMenu = menuBar()->addMenu(tr("Settings"));
    QAction* connectionAction = settingsMenu->addAction(tr("Connection"));

    QMenu* trackingMenu = menuBar()->addMenu(tr("Tracking"));
    QAction* GEAction = trackingMenu->addAction(tr("Google earth"));


    connect(connectionAction,
            SIGNAL(triggered()),
            this,
            SLOT(onConnActionTriggerd()));
    connect(GEAction,
            SIGNAL(triggered()),
            this,
            SLOT(onGEactionTriggered()));
}

void MissionViewer::createTcpComm(QString host,int port)
{
    if(mComm)
        delete mComm;
    mComm = 0;
    if(mTcpSocket)
        delete mTcpSocket;
    mTcpSocket = 0;

    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost(host,port);
    if(mTcpSocket->waitForConnected(3000))
    {
        qDebug() << "Connection succesfull";
        mComm = createSocketComm(mTcpSocket);

        if(!mPacketTimer)
        {
            mPacketTimer = new QTimer(this);
            mPacketTimer->setInterval(5);
            connect(mPacketTimer,
                    SIGNAL(timeout()),
                    this,
                    SLOT(onPacketTimerTimeout()));
        }
        mPacketTimer->start();

        QMessageBox::information(this,
                                 tr("Connection"),
                                 tr("Connection succesfull"));
    }
    else
    {
        qDebug() << "Connection failed";
        QMessageBox::critical(this,
                                 tr("Connection"),
                                 tr("Connection failed"));
        delete mTcpSocket;
        mPacketTimer->stop();
        mTcpSocket = 0;
    }
}

ICommunication_E* MissionViewer::createSocketComm(QTcpSocket* socket)
{
    TcpSocketPipe* socketpipe = new TcpSocketPipe(socket);
    IPacketFactory_E* factory = new PacketFactory_E();
    ICommunication_E* comm =  new Communication_E(factory,socketpipe,1000);
    return comm;
}
