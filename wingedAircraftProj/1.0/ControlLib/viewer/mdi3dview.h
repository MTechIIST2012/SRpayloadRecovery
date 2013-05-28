#ifndef MDI3DVIEW_H
#define MDI3DVIEW_H

#include "advancedglview.h"
#include "ControlLib_global.h"
#include <QMdiSubWindow>

namespace Ui {
    class Mdi3dView;
}

class QGLAbstractScene;

class CONTROLLIBSHARED_EXPORT Mdi3dView : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit Mdi3dView(QWidget *parent = 0);
    virtual ~Mdi3dView();
    void setScene(QGLAbstractScene* scene);
    QGLAbstractScene* getScene();
    void setObjectViewInfo(ObjectInfoHash objInfo);
    AdvancedGLView* getGLView();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::Mdi3dView *ui;
};

#endif // MDI3DVIEW_H
