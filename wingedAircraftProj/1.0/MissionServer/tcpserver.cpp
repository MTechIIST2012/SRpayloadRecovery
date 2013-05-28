#include "tcpserver.h"
#include "tcpserverthread.h"
#include "tcpsocketpipe.h"
#include "Communication_E.h"
#include "DataPackets_E.h"
#include <QTcpSocket>
#include <QDebug>

TcpServer::TcpServer(int port,QObject* parent)
    : QTcpServer(parent)
{
    mPort = port;
}

TcpServer::~TcpServer()
{

}

int TcpServer::getPort()
{
    return mPort;
}

void TcpServer::startServer()
{
    qDebug() << "Starting server , port :" << mPort;
    if(listen(QHostAddress::Any,mPort))
    {
        qDebug() << "Server started..";
    }
    else
    {
        qDebug() << "Could not start server";
    }
}

QSet<ICommunication_E*> TcpServer::getCommSet()
{
    return mCommList;
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting..";
    QTcpSocket* socket = new QTcpSocket(this);
    ICommunication_E* comm = createSocketComm(socket);
    mCommList.insert(comm);
    TcpServerThread* thread = new TcpServerThread(socket,comm,socketDescriptor,this);
    connect(thread,
            SIGNAL(commDisconnected(ICommunication_E*)),
            this,
            SLOT(onConnDisconnect(ICommunication_E*)));
    connect(thread,
            SIGNAL(finished()),
            thread,
            SLOT(deleteLater()));
    thread->start();
}

ICommunication_E* TcpServer::createSocketComm(QTcpSocket* socket)
{
    TcpSocketPipe* socketpipe = new TcpSocketPipe(socket);
    IPacketFactory_E* factory = new PacketFactory_E();
    ICommunication_E* comm =  new Communication_E(factory,socketpipe,1000);
    return comm;
}

void TcpServer::onConnDisconnect(ICommunication_E* comm)
{
    mCommList.remove(comm);
}
