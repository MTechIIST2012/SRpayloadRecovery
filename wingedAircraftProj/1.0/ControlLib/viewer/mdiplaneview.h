#ifndef MDIPLANEVIEW_H
#define MDIPLANEVIEW_H

#include <QHash>
#include <QVector3D>
#include "mdi3dview.h"
#include "ControlLib_global.h"

class IPlane;
class QGraphicsRotation3D;
class QTimer;

class CONTROLLIBSHARED_EXPORT MdiPlaneView : public Mdi3dView
{
    Q_OBJECT
public:
    explicit MdiPlaneView(QString configFile,QWidget *parent = 0);
    virtual ~MdiPlaneView();
    void setPlane(IPlane* plane);
    IPlane* getPlane();
    void setRefreshDelay(int ms);
    int getRefreshDelay();
protected slots:
    virtual void refreshPlaneView();
protected:
    void setScene(QGLAbstractScene* scene);
    virtual void readSettings(QString configFile);
private:
    void initGraphicRotations();
    QVector3D parseVector(QString str);
    void initScene();

    QTimer* mRefreshTimer;
    QString mConfigFile;
    IPlane* mPlane;
    QHash<int,QGraphicsRotation3D*> mGraphicRotMap;
    QHash<int,QString> mObjectModelMap;
    QHash<int,QString> mObjectConfigMap;
    QString mModelFileName;
    int mRefreshDelay;
};

#endif // MDIPLANEVIEW_H
