#include "advancedglview.h"
#include "ui_advancedglview.h"
#include "qglabstractscene.h"
#include "objectinfolistdialog.h"
#include <QDebug>




//////////////////////////////////////////////////////////////////
AdvancedGLView::AdvancedGLView(QWidget *parent) :
    QGLView(parent),
    ui(new Ui::AdvancedGLView)
{
    ui->setupUi(this);
    m_lightModel=0;
    m_scene = 0;
    m_lightParameters=0;
    mZoomInFactor = 1.1;
    mZoomOutFactor = 0.9;
    mMoveTrnIncr = 2;
    mProjDist = 50;
    mMatIndex = 0;
}

AdvancedGLView::~AdvancedGLView()
{
    delete ui;
    if(m_scene)
        delete m_scene;
}

void AdvancedGLView::setScene(QGLAbstractScene* scene)
{
    m_scene = scene;
    populateSceneNodeHash(m_scene);
}

void AdvancedGLView::setZoomInFactor(double factor)
{
    mZoomInFactor = factor;
}

void AdvancedGLView::setZoomOutFactr(double factor)
{
    mZoomOutFactor = factor;
}

void AdvancedGLView::setMoveTrnIncement(int incr)
{
    mMoveTrnIncr = incr;
}

void AdvancedGLView::setProjDistance(double dist)
{
    mProjDist = dist;
}

void AdvancedGLView::setObjectViewInfo(ObjectInfoHash objInfo)
{
    mObjViewInfoHash = objInfo;
}

QGLAbstractScene* AdvancedGLView::getScene()
{
    return m_scene;
}

double AdvancedGLView::getZoomInFactor()
{
    return mZoomInFactor;
}

double AdvancedGLView::getZoomOutFactr()
{
    return mZoomOutFactor;
}

int AdvancedGLView::getMoveTrnIncement()
{
    return mMoveTrnIncr;
}

double AdvancedGLView::getProjDistance()
{
    return mProjDist;
}

ObjectInfoHash AdvancedGLView::getObjectViewInfo()
{
    return mObjViewInfoHash;
}

void AdvancedGLView::updateObject(QString objname,ObjectViewInfo objViewInfo)
{
    if(m_scene)
    {
        foreach(QGLSceneNode* node,mHashSceneNode.values(objname))
        {
            if(node)
            {
                updateObject_internal(node,objViewInfo);
            }
        }
        update();
    }
}

void AdvancedGLView::setObjectColor(QString objname,QColor color)
{
    if(m_scene)
    {
        ObjectViewInfo objViewInfo = mObjViewInfoHash.value(objname);
        objViewInfo.setColor(color);
        foreach(QGLSceneNode* node,mHashSceneNode.values(objname))
        {
            if(node)
            {
                updateObject_internal(node,objViewInfo);
                mObjViewInfoHash.insert(objname,objViewInfo);
            }
        }
        update();
    }
}

void AdvancedGLView::setObjectLabelMap(QHash<QString,QString> map)
{
    mObjectLabelMap = map;
}

QHash<QString,QString> AdvancedGLView::getObjectLabelMap()
{
    return mObjectLabelMap;
}

void AdvancedGLView::initializeGL(QGLPainter *painter)
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    painter->setStandardEffect(QGL::LitMaterial);
}

void AdvancedGLView::paintGL(QGLPainter *painter)
{
    if(m_scene)
    {
        QGLSceneNode *o = m_scene->mainNode();
        o->draw(painter);
    }
}

void AdvancedGLView::on_btnRotUp_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->rotateCenter(Camera->tilt(10));
    }
}

void AdvancedGLView::on_btnRotLeft_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->rotateCenter(Camera->roll(10));
    }
}

void AdvancedGLView::on_btnRotDown_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->rotateCenter(Camera->tilt(-10));
    }
}

void AdvancedGLView::on_btnRotRight_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->rotateCenter(Camera->roll(-10));
    }
}

void AdvancedGLView::on_btnZoomIn_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        QVector3D eyePos = Camera->eye();
        eyePos = mZoomOutFactor * eyePos;
        Camera->setEye(eyePos);
    }
}

void AdvancedGLView::on_btnZoomOut_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        QVector3D eyePos = Camera->eye();
        eyePos = mZoomInFactor * eyePos;
        Camera->setEye(eyePos);
    }
}

void AdvancedGLView::on_btnMoveUp_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->translateCenter(0,-mMoveTrnIncr,0);
    }
}

void AdvancedGLView::on_btnMoveLeft_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->translateCenter(-mMoveTrnIncr,0,0);
    }
}

void AdvancedGLView::on_btnMoveDown_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->translateCenter(0,mMoveTrnIncr,0);
    }
}

void AdvancedGLView::on_btnMoveRight_clickUpdate()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->translateCenter(mMoveTrnIncr,0,0);
    }
}

void AdvancedGLView::on_btnProjTop_clicked()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->setEye(QVector3D(0,0,mProjDist));
        Camera->setUpVector(QVector3D(1,0,0));
    }
}

void AdvancedGLView::on_btnProjBottom_clicked()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->setEye(QVector3D(0,0,-mProjDist));
        Camera->setUpVector(QVector3D(1,0,0));
    }
}

void AdvancedGLView::on_btnProjRight_clicked()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->setEye(QVector3D(0,-mProjDist,0));
        Camera->setUpVector(QVector3D(0,0,1));
    }
}

void AdvancedGLView::on_btnProjLeft_clicked()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->setEye(QVector3D(0,mProjDist,0));
        Camera->setUpVector(QVector3D(0,0,1));
    }
}

void AdvancedGLView::on_btnProjFront_clicked()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->setEye(QVector3D(-mProjDist,0,0));
        Camera->setUpVector(QVector3D(0,0,1));
    }
}

void AdvancedGLView::on_btnProjBack_clicked()
{
    QGLCamera* Camera = camera();
    if(Camera)
    {
        Camera->setEye(QVector3D(mProjDist,0,0));
        Camera->setUpVector(QVector3D(0,0,1));
    }
}

void AdvancedGLView::on_btnViewCompDlg_clicked()
{
    qDebug() << m_scene->objectNames();

    ObjectInfoListDialog objListDlg(mObjViewInfoHash);
    objListDlg.exec();
    objListDlg.recalculate();
    if(objListDlg.hasChanged())
    {
        mObjViewInfoHash = objListDlg.getObjectInfoHash();
        foreach(QString objName,mObjViewInfoHash.keys())
        {
            QString actualName = mObjectLabelMap.value(objName);
            if(actualName.isEmpty())
                actualName = objName;

            updateObject(actualName,mObjViewInfoHash.value(objName));
        }
    }
}

/////Private

void AdvancedGLView::updateObject_internal(QGLSceneNode* node,ObjectViewInfo objViewInfo)
{
    switch(objViewInfo.getViewType())
    {
    case ObjectViewInfo::LINES:
        node->setOption(QGLSceneNode::HideNode,false);
        node->setDrawingMode(QGL::Lines);
        node->setDrawingWidth(1);
        break;
    case ObjectViewInfo::HIDDEN:
        node->setOption(QGLSceneNode::HideNode,true);
        break;
    default:
        node->setOption(QGLSceneNode::HideNode,false);
        node->setDrawingMode(QGL::Triangles);
        node->setEffect(QGL::LitMaterial);
    }


    int matIndex = node->materialIndex();
    if( matIndex <= 0 )
    {
        QString objName = node->objectName();
        node->setMaterialIndex(mHashMatIndex.value(objName));  //(++mMatIndex);
    }
    QGLMaterial* mat = node->material();
    if(!mat)
    {
        mat = new QGLMaterial(this);
        node->setMaterial(mat);
    }

    QColor color = objViewInfo.getColor();
    mat->setAmbientColor(color);
    node->setMaterial(mat);   
}

void AdvancedGLView::populateSceneNodeHash(QGLAbstractScene* scene)
{
    mHashSceneNode.clear();
    mHashMatIndex.clear();
    if(scene)
    {
        QGLSceneNode* mainnd = scene->mainNode();
        if(mainnd)
        {
            int matIndex=1;
            foreach(QGLSceneNode* node,mainnd->allChildren())
            {
                if(node)
                {
                    QString objName = node->objectName();
                    mHashSceneNode.insertMulti(objName,node);
                    mHashMatIndex.insert(objName,matIndex++);
                }
            }
        }
    }
}


