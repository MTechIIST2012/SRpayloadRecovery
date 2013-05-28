#include "mdi3dview.h"
#include "ui_mdi3dview.h"

Mdi3dView::Mdi3dView(QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::Mdi3dView)
{
    ui->setupUi(this);
    setWidget(ui->widget);
}

Mdi3dView::~Mdi3dView()
{
    delete ui;
}

void Mdi3dView::setScene(QGLAbstractScene* scene)
{
    getGLView()->setScene(scene);
}

QGLAbstractScene* Mdi3dView::getScene()
{
    return getGLView()->getScene();
}

void Mdi3dView::setObjectViewInfo(ObjectInfoHash objInfo)
{
    getGLView()->setObjectViewInfo(objInfo);
}

AdvancedGLView* Mdi3dView::getGLView()
{
    return ui->glview;
}

void Mdi3dView::closeEvent(QCloseEvent *event)
{
    hide();
}
