#include "testmanager.h"
#include "ICommand.h"
#include "commanddata.h"
#include <QDebug>
#include <QTime>

TestManager::TestManager(int count,QObject *parent)
    : AbstractManager(parent)
{
    mCount = count;
}

bool TestManager::doAction(ICommand* command)
{
    qDebug() << "doing operation " << command->getType();
    qDebug() << "reading data";

    ByteCommandData* bytedata = dynamic_cast<ByteCommandData*>(command->getData());
    if(bytedata)
    {
       BYTE byte = bytedata->getData();
       qDebug() << "data is a byte :" << byte;

       if(1)//byte == 'n')
       {
           for(int i=0; i<mCount; i++)
           {
               qDebug() << byte;

               QTime time = QTime::currentTime().addMSecs(500);
               while(QTime::currentTime() < time);

           }
       }

    }
}
