#ifndef ADVANCEDGLVIEW_H
#define ADVANCEDGLVIEW_H

#include "ControlLib_global.h"
#include "objectviewinfo.h"
#include <qglview.h>
#include <QMultiHash>
#include <QDialog>

class QGLAbstractScene;
class QGLSceneNode;
class QRubberBand;

namespace Ui {
    class AdvancedGLView;
}

class CONTROLLIBSHARED_EXPORT AdvancedGLView : public QGLView
{
    Q_OBJECT
public:
    explicit AdvancedGLView(QWidget *parent = 0);
    ~AdvancedGLView();

    void setScene(QGLAbstractScene* scene);
    void setZoomInFactor(double factor);
    void setZoomOutFactr(double factor);
    void setMoveTrnIncement(int incr);
    void setProjDistance(double dist);
    void setObjectViewInfo(ObjectInfoHash objInfo);
    QGLAbstractScene* getScene();
    double getZoomInFactor();
    double getZoomOutFactr();
    int getMoveTrnIncement();
    double getProjDistance();
    ObjectInfoHash getObjectViewInfo();
    void updateObject(QString objname,ObjectViewInfo objViewInfo);
    void setObjectColor(QString objname,QColor color);
    void setObjectLabelMap(QHash<QString,QString> map);
    QHash<QString,QString> getObjectLabelMap();
protected:
    void initializeGL(QGLPainter *painter);
    void paintGL(QGLPainter *painter);
private slots:
    void on_btnViewCompDlg_clicked();
    void on_btnProjBack_clicked();
    void on_btnProjFront_clicked();
    void on_btnProjLeft_clicked();
    void on_btnProjBottom_clicked();
    void on_btnProjRight_clicked();
    void on_btnProjTop_clicked();
    void on_btnMoveRight_clickUpdate();
    void on_btnMoveDown_clickUpdate();
    void on_btnMoveLeft_clickUpdate();
    void on_btnMoveUp_clickUpdate();
    void on_btnZoomOut_clickUpdate();
    void on_btnZoomIn_clickUpdate();
    void on_btnRotRight_clickUpdate();
    void on_btnRotDown_clickUpdate();
    void on_btnRotLeft_clickUpdate();
    void on_btnRotUp_clickUpdate();
private:
    void updateObject_internal(QGLSceneNode* node,ObjectViewInfo objViewInfo);
    void populateSceneNodeHash(QGLAbstractScene* scene);

    Ui::AdvancedGLView *ui;
    double mZoomInFactor;
    double mZoomOutFactor;
    int mMoveTrnIncr;
    double mProjDist;

    QGLAbstractScene *m_scene;
    QGLLightModel *m_lightModel;
    QGLLightParameters *m_lightParameters;
    ObjectInfoHash mObjViewInfoHash;
    QMultiHash<QString,QGLSceneNode*> mHashSceneNode;
    QHash<QString,int> mHashMatIndex;
    QHash<QString,QString> mObjectLabelMap;

    int mMatIndex;
};

#endif // ADVANCEDGLVIEW_H
