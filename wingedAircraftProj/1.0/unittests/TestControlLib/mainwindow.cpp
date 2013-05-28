#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenemanager.h"
#include "command.h"
#include "commanddata.h"
#include "ISceneOperator.h"
#include "logger.h"

#include <qglabstractscene.h>
#include <QDebug>


class TestOperator : public ISceneOperator
{
public:
    TestOperator() {}
    virtual ~TestOperator() {}
    virtual int getType() {  return 0; }
    virtual bool doAction(ICommand* command,QGLAbstractScene* scene)
    {
        qDebug() << "TestOperator::doAction-" << command->getType();

        ByteCommandData* byteData = dynamic_cast<ByteCommandData*>(command->getData());
        if(byteData)
        {
            BYTE byte = byteData->getData();
            qDebug() << "data = " << byte;
        }
    }
};



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGLAbstractScene* scene = QGLAbstractScene::loadScene(QLatin1String("../F8_Harrier.blend"));
    ui->glview->setScene(scene);

    QGLAbstractScene* scene2 = QGLAbstractScene::loadScene(QLatin1String("../F8_Harrier.blend"));
    ui->glview2->setScene(scene2);

    mSceneMgr = new SceneManager(this);
    mSceneMgr->registerOperator(0,new TestOperator());
    //mSceneMgr->unregisterOperator(0);

    mSceneMgr->addScene("scene",scene);
    mSceneMgr->addScene("scene2",scene2);
    mSceneMgr->start();

    ObjectInfoHash objInfoHash;
    objInfoHash.insert("Part1",ObjectViewInfo());
    objInfoHash.insert("Part2",ObjectViewInfo());
    objInfoHash.insert("AV8_HarrierMesh",ObjectViewInfo());
    objInfoHash.insert("Plane.011",ObjectViewInfo());
    objInfoHash.insert("PlaneStruct",ObjectViewInfo());
    objInfoHash.insert("Cylinder",ObjectViewInfo());

    ui->glview->setObjectViewInfo(objInfoHash);
    ui->glview2->setObjectViewInfo(objInfoHash);

    Logger logger("logs/log.log");
    logger.SetTraceLevel(3);
    logger.Log("Try logging",Logger::INFO);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAction1_clicked()
{
    ICommandData* comdData = new ByteCommandData(0,'a');
    ICommand* cmd = new Command(0);
    cmd->setData(comdData);

    mSceneMgr->queueCommand(cmd);
}

void MainWindow::on_btnAction2_clicked()
{
   ui->glview->setObjectColor("PlaneStruct",Qt::red);
   ui->glview->setObjectColor("Cylinder",Qt::blue);
}
