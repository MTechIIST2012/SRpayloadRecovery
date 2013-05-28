#include <QtCore/QCoreApplication>
#include "testmanager.h"
#include "command.h"
#include "commanddata.h"
#include <QDebug>
#include <QTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestManager* manager1 = new TestManager(5);
    TestManager* manager2 = new TestManager(10);

    Command* cmd = new Command();
    cmd->setData(new ByteCommandData(TYPE_BYTE,'m'));

    Command* cmd2 = new Command();
    cmd2->setData(new ByteCommandData(TYPE_BYTE,'n'));

    Command* cmd3 = new Command();
    cmd3->setData(new ByteCommandData(TYPE_BYTE,'p'));

    manager1->start();
    manager2->start();
    manager1->queueCommand(cmd);
    manager1->queueCommand(cmd2);

    manager2->queueCommand(cmd);

    cmd3->setSeverity(ICommand::HIGH);
    //manager1->clearCommands();

    QTime time = QTime::currentTime().addMSecs(100);
    while(QTime::currentTime() < time);

    manager1->queueCommand(cmd);

    manager1->queueCommand(cmd3);

    time = QTime::currentTime().addMSecs(2000);
    while(QTime::currentTime() < time);

    //delete manager1;

    return a.exec();
}
