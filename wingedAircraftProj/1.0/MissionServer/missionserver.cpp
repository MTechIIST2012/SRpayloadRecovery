#include "missionserver.h"
#include "serialpipe.h"
#include "Communication_E.h"
#include "DataPackets_E.h"
#include "tcpserver.h"
#include <QTimer>
#include <QDebug>

MissionServer::MissionServer(QString deviceSerialport,
                             int deviceBaudRate,
                             QObject *parent) :
    QObject(parent)
{
    mDeviceSerialPort = deviceSerialport;
    mDeviceSerialBaud = deviceBaudRate;
    mDeviceComm = 0;
    mUpdateTimer = 0;

    mTcpServer = new TcpServer(1234,this);
    mTcpServer->startServer();
}

MissionServer::~MissionServer()
{

}

void MissionServer::setDeviceSerialPort(QString portname)
{
    mDeviceSerialPort = portname;
}

QString MissionServer::getDeviceSerialPort()
{
    return mDeviceSerialPort;
}

void MissionServer::setDeviceBaud(int baud)
{
    mDeviceSerialBaud = baud;
}

int MissionServer::getDeviceBaud()
{
    return mDeviceSerialBaud;
}

void MissionServer::init()
{
    qDebug() << "Initializing server";
    mDeviceComm = createDeviceComm();
    if(!mUpdateTimer)
    {
        mUpdateTimer = new QTimer(this);
        connect(mUpdateTimer,
                SIGNAL(timeout()),
                this,
                SLOT(onUpdateTimerTimeout()));
    }
    mUpdateTimer->setInterval(5);
    qDebug() << "Server init complete";
}

void MissionServer::start()
{
    qDebug() << "Server starting";
    if(mDeviceComm && mUpdateTimer)
    {
        mDeviceComm->start(mDeviceSerialBaud);
        mUpdateTimer->start();
    }
    qDebug() << "Server started";
}

void MissionServer::stop()
{
    if(mUpdateTimer)
        mUpdateTimer->stop();                 // Todo: needs to stop the serial port also.
}

bool MissionServer::run()
{
    if(!mDeviceComm)
        return false;

    mDeviceComm->updateBuffer();
    IDataPacket_E* packet = mDeviceComm->readPacket();
    while(packet)
    {
        qDebug() << "Packet available";
        processPacket(packet);
        delete packet;

        packet = mDeviceComm->readPacket();
    }
}

ICommunication_E* MissionServer::createDeviceComm()
{
    IControllerPipe* pipe = new SerialPipe(mDeviceSerialPort);
    IPacketFactory_E* factory = new PacketFactory_E();
    ICommunication_E* comm =  new Communication_E(factory,pipe,1000);
    return comm;
}

void MissionServer::processPacket(IDataPacket_E* packet)
{
    switch(packet->type())
    {
    case PACKET_CHECK_CONNECTION:
        acceptConnection();
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

void MissionServer::onUpdateTimerTimeout()
{
    run();
}

void MissionServer::acceptConnection()
{
    IPacketFactory_E* factory = mDeviceComm->getFactory();
    IDataPacket_E* packet = factory->createPacket(PACKET_CHECK_CONNECTION_REPLY);
    Packet_ConnReply* connReply = dynamic_cast<Packet_ConnReply*>(packet);
    if(connReply)
    {
        connReply->setConnectionStatus(CONNECTION_OK);
        mDeviceComm->sendPacket(connReply);

    }
    if(packet)
        delete packet;
}

void MissionServer::readPosPacket(IDataPacket_E* packet)
{
    Packet_Location* posPacket = dynamic_cast<Packet_Location*>(packet);       // Todo: needs to be modified for checksum.
    if(posPacket)
    {
        qDebug() << "Position reading succesfull ";
        QString posStr = QString("%0,%1,%2").arg(posPacket->getPos().altitude)
                         .arg(posPacket->getPos().latitude)
                         .arg(posPacket->getPos().longitude);
        QString orienStr = QString("%0,%1,%2").arg(posPacket->getPitch())
                           .arg(posPacket->getRoll())
                           .arg(posPacket->getYaw());

        qDebug() << "Position :" << posStr;
        qDebug() << "Orientaion :" << orienStr;


        if(posPacket->hasCheckSumMatched())
        {
            qDebug() << "Checksum matched";

            try              // because there is possibility of comm to be destructed early.
            {
                foreach(ICommunication_E* comm,mTcpServer->getCommSet())
                {
                    comm->sendPacket(posPacket);
                }
            }catch(QString str)
            {
                qDebug() << "Error :" << str;
            }
        }
        else
            qDebug() << "Checksum did not match";
    }
    else
    {
        qDebug() << "Position reading failed ";
    }

}

