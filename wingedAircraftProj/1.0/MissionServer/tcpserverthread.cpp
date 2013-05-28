#include "tcpserverthread.h"
#include "ICommunication_E.h"

TcpServerThread::TcpServerThread(QTcpSocket* socket,ICommunication_E* comm,int ID,QObject *parent)
    : QThread(parent)
{
    mSocketDescriptor = ID;
    mSocket = socket;
    mComm = comm;
}

TcpServerThread::~TcpServerThread()
{
    if(mSocket)
        delete mSocket;
    if(mComm)
        delete mComm;
}

void TcpServerThread::run()
{
    qDebug() << mSocketDescriptor << " Thread started";
    //mSocket = new QTcpSocket(this);
    if(!mSocket->setSocketDescriptor(mSocketDescriptor))
    {
        emit error(mSocket->error());
        return;
    }

    connect(mSocket,
            SIGNAL(readyRead()),
            this,
            SLOT(readyRead()),
            Qt::DirectConnection);
    connect(mSocket,
            SIGNAL(disconnected()),
            this,
            SLOT(disconnected()),
            Qt::DirectConnection);

    qDebug() << mSocketDescriptor << " Socket connected";
    exec();
}

void TcpServerThread::setCommunication(ICommunication_E* comm)
{
    mComm = comm;
}

ICommunication_E* TcpServerThread::getCommunication()
{
    return mComm;
}

void TcpServerThread::readyRead()
{
//    QByteArray Data = mSocket->readAll();
//    qDebug() << mSocketDescriptor << " Data in :" << Data;
//    //reflecting data
//    mSocket->write(Data);

    if(mComm)
        mComm->updateBuffer();
}

void TcpServerThread::disconnected()
{
    qDebug() << mSocketDescriptor << " Disconnected";
    emit commDisconnected(mComm);
    deleteLater();
    exit(0);
}



