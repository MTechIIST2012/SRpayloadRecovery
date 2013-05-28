#include "widget.h"
#include "ui_widget.h"
#include "serialpipe.h"
#include "Communication_E.h"
#include "DataPackets_E.h"
#include <QDebug>
#include <QStringList>

ICommunication_E* Widget::mServerComm = 0;
ICommunication_E* Widget::mClientComm = 0;
IControllerPipe* Widget::mServerPipe = 0;
IControllerPipe* Widget::mClientPipe = 0;

void updateServerBuffer()
{
    if(Widget::mServerComm)
        Widget::mServerComm->updateBuffer();
}

void updateClientBuffer()
{
    if(Widget::mClientComm)
        Widget::mClientComm->updateBuffer();
}

/////////////////////////////////////////////////////////////////

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    mServerPipe = new SerialPipe("");
    mClientPipe = new SerialPipe("");
    IPacketFactory_E* factory = new PacketFactory_E();
    mServerComm =  new Communication_E(factory,mServerPipe,1000);
    mClientComm =  new Communication_E(factory,mClientPipe,1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnServerCheckConnection_clicked()
{
    if(mServerComm->checkConnection() == CONNECTION_OK)
    {
        qDebug() << "Server : connection successfull";
    }
    else
    {
        qDebug() << "Server : connection fail";
    }
}

void Widget::on_btnServerSendPacket_clicked()
{
    QStringList posParts = ui->edtServerPos->text().split(",");
    QStringList orientParts = ui->edtServerOrientation->text().split(",");

    if(posParts.count()==3 and orientParts.count()==3)
    {
        IPacketFactory_E* factory = mServerComm->getFactory();
        IDataPacket_E* packet = factory->createPacket(PACKET_LOCATION);
        Packet_Location* posPacket = dynamic_cast<Packet_Location*>(packet);
        if(posPacket)
        {
            float altitude = posParts.at(0).toFloat();
            float latitude = posParts.at(1).toFloat();
            float longitude = posParts.at(2).toFloat();

            float pitch = orientParts.at(0).toFloat();
            float roll = orientParts.at(1).toFloat();
            float yaw = orientParts.at(2).toFloat();

            posPacket->setPos(_GPSPosition(latitude,longitude,altitude));
            posPacket->setOrientation(pitch,roll,yaw);

            mServerComm->sendPacket(posPacket);

        }

        if(packet)
            delete packet;
    }
}

void Widget::on_btnClientAcceptConn_clicked()
{
    IPacketFactory_E* factory = mClientComm->getFactory();
    IDataPacket_E* packet = factory->createPacket(PACKET_CHECK_CONNECTION_REPLY);
    Packet_ConnReply* connReply = dynamic_cast<Packet_ConnReply*>(packet);
    if(connReply)
    {
        connReply->setConnectionStatus(CONNECTION_OK);
        mClientComm->sendPacket(connReply);
        delete connReply;
    }
}

void Widget::on_btnClientRecvPacket_clicked()
{
    IDataPacket_E* packet = mClientComm->readPacket();
    if(packet)
    {
        qDebug() << "packet type :" << packet->type();
    }
    else
    {
        qDebug() << "no packet found";
    }

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

        ui->edtClientPos->setText(posStr);
        ui->edtClientOrientation->setText(orienStr);

        if(posPacket->hasCheckSumMatched())
            qDebug() << "Checksum matched";
        else
            qDebug() << "Checksum did not match";
    }
    else
    {
        qDebug() << "Position reading failed ";
    }

    if(packet)
        delete packet;

}

void Widget::on_btnServerUpdate_clicked()
{
    QString portname = ui->edtServerPort->text();
    ((SerialPipe*)mServerPipe)->setPort(portname);
    mServerPipe->_serialBegin(9600);
    mServerPipe->_timer1_initialize(5000);
    mServerPipe->_timer1_attachInterrupt(updateServerBuffer);
}

void Widget::on_btnClientUpdate_clicked()
{
    QString portname = ui->edtClientPort->text();
    ((SerialPipe*)mClientPipe)->setPort(portname);
    mClientPipe->_serialBegin(9600);
    mClientPipe->_timer1_initialize(5000);
    mClientPipe->_timer1_attachInterrupt(updateClientBuffer);
}
