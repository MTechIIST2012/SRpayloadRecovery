#include "mdiplaneview.h"
#include "IPlane.h"
#include "IControlObject.h"
#include "PlanePartDefs.h"
#include <qgraphicsrotation3d.h>
#include <qglabstractscene.h>
#include <QSettings>
#include <QStringList>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

MdiPlaneView::MdiPlaneView(QString configFile,QWidget *parent)
    : Mdi3dView(parent)
{
    mConfigFile = configFile;
    initGraphicRotations();
    readSettings(configFile);
    initScene();

    mPlane = 0;
    mRefreshDelay = 50;
    mRefreshTimer = new QTimer(this);
    connect(mRefreshTimer,
            SIGNAL(timeout()),
            this,
            SLOT(refreshPlaneView()));
    setRefreshDelay(mRefreshDelay);
}

MdiPlaneView::~MdiPlaneView()
{
    mRefreshTimer->stop();
}

void MdiPlaneView::setPlane(IPlane* plane)
{
    mRefreshTimer->stop();
    mPlane = plane;
    mRefreshTimer->start();
}

IPlane* MdiPlaneView::getPlane()
{
    return mPlane;
}

void MdiPlaneView::setRefreshDelay(int ms)
{
    mRefreshTimer->stop();
    mRefreshDelay = ms;
    mRefreshTimer->setInterval(mRefreshDelay);
    mRefreshTimer->start();
}

int MdiPlaneView::getRefreshDelay()
{
    return mRefreshDelay;
}

void MdiPlaneView::refreshPlaneView()
{
    if(!mPlane)
        return;

    bool bValueChanged=false;
    foreach(int partId,mGraphicRotMap.keys())
    {
        QGraphicsRotation3D* rot = mGraphicRotMap.value(partId,0);
        IControlObject* ctrlObj = mPlane->getControlObject(partId);
        if(rot && ctrlObj)
        {
            double value = ctrlObj->getValue().toDouble();
            if(partId != FAN)
            {
                if(rot->angle() != value)
                {
                    rot->setAngle(value);
                    bValueChanged = true;
                }
            }
            else
            {
                double curAngle = rot->angle();
                double newAngle =  (curAngle + value*mRefreshDelay*360/60000);
                if(newAngle > 360)
                    newAngle-=360;
                rot->setAngle(newAngle);
                bValueChanged = true;
            }
        }
    }

    if(bValueChanged)
        getGLView()->update();
}

// protected
void MdiPlaneView::setScene(QGLAbstractScene* scene)
{
    Mdi3dView::setScene(scene);
}

void MdiPlaneView::readSettings(QString configFile)
{
    mObjectModelMap.clear();
    mObjectConfigMap.clear();

    mObjectConfigMap.insert(AILERON_LEFT,"aileron_left");
    mObjectConfigMap.insert(AILERON_RIGHT,"aileron_right");
    mObjectConfigMap.insert(ELEVATOR_LEFT,"elevator_left");
    mObjectConfigMap.insert(ELEVATOR_RIGHT,"elevator_right");
    mObjectConfigMap.insert(RUDDER,"rudder");
    mObjectConfigMap.insert(FAN,"fan");
    mObjectConfigMap.insert(BODY,"body");

    QSettings settings(configFile,QSettings::IniFormat);
    settings.beginGroup("file");
    mModelFileName =  settings.value("modelfile").toString().trimmed();
    settings.endGroup();

    settings.beginGroup("partmap");
    foreach(int partId,mObjectConfigMap.keys())
    {
        QString partName = mObjectConfigMap.value(partId);
        mObjectModelMap.insert(partId,settings.value(partName).toString().trimmed());
    }
    settings.endGroup();

    settings.beginGroup("part_rotation_detail");
    foreach(int partId,mObjectConfigMap.keys())
    {
        QGraphicsRotation3D* rotation = mGraphicRotMap.value(partId,0);
        if(rotation)
        {
            QString partName = mObjectConfigMap.value(partId);
            QString configFile_PosKey = partName + "_pos";
            QString configFile_AxisKey = partName  + "_axis";

            QString posStr = settings.value(configFile_PosKey).toString().trimmed();
            QString axisStr = settings.value(configFile_AxisKey).toString().trimmed();
            QVector3D pos = parseVector(posStr);
            QVector3D axis = parseVector(axisStr);

            rotation->setOrigin(pos);
            rotation->setAxis(axis);
        }
    }
    settings.endGroup();
}

void MdiPlaneView::initGraphicRotations()
{
    qDeleteAll(mGraphicRotMap.values());
    mGraphicRotMap.clear();

    QList<int> PartList;
    PartList << AILERON_LEFT
                << AILERON_RIGHT
                << ELEVATOR_LEFT
                << ELEVATOR_RIGHT
                << RUDDER
                << FAN;

    foreach(int partIndex,PartList)
    {
        QGraphicsRotation3D* rotation = new QGraphicsRotation3D(this);
        mGraphicRotMap.insert(partIndex,rotation);
    }
}

QVector3D MdiPlaneView::parseVector(QString str)
{
    QVector3D vector;
    QStringList parts = str.split(",");
    if(parts.count()>=3)
    {
        double x = parts.at(0).toDouble();
        double y = parts.at(1).toDouble();
        double z = parts.at(2).toDouble();
        vector.setX(x);
        vector.setY(y);
        vector.setZ(z);
    }
    return vector;
}

void MdiPlaneView::initScene()
{
    if(!QFile::exists(mModelFileName))
    {
        qDebug() << QString("Template file %0 does not exist").arg(mModelFileName);
        return;
    }
    QGLAbstractScene* scene = QGLAbstractScene::loadScene(mModelFileName);
    setScene(scene);

    if(!scene)
    {
        qDebug() << QString("An error occured in loading scene");
        return;
    }

    ObjectInfoHash objInfoHash;
    QHash<QString,QString> partLabelMap;
    foreach(int partId,mObjectConfigMap.keys())
    {
        QString partName = mObjectConfigMap.value(partId);
        QString actualName = mObjectModelMap.value(partId);
        partLabelMap.insert(partName,actualName);

        objInfoHash.insert(partName,ObjectViewInfo());
    }
    setObjectViewInfo(objInfoHash);
    getGLView()->setObjectLabelMap(partLabelMap);

    QString objname = mObjectModelMap.value(BODY);
    QObject* obj = scene->object(objname);
    QGLSceneNode* bodyNode = qobject_cast<QGLSceneNode*>(obj);
    if(bodyNode)
    {
        foreach(int partId,mGraphicRotMap.keys())
        {
            if(partId != BODY)
            {
                QGraphicsRotation3D* rot = mGraphicRotMap.value(partId,0);
                QString actualName = mObjectModelMap.value(partId);
                if(rot && !actualName.isEmpty())
                {
                    QGLSceneNode* node = qobject_cast<QGLSceneNode*>(scene->object(actualName));
                    if(node)
                    {
                        QGLSceneNode* curParent = qobject_cast<QGLSceneNode*>(node->parent());
                        if(curParent)
                        {
                            curParent->removeNode(node);
                        }

                        bodyNode->addNode(node);
                        node->addTransform(rot);
                    }
                }
            }
        }
    }
}

