#ifndef MDIPLANEMETERPANNEL_H
#define MDIPLANEMETERPANNEL_H

#include <QMdiSubWindow>

namespace Ui {
    class MdiPlaneMeterPannel;
}

class QTimer;
class IPlane;

class MdiPlaneMeterPannel : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit MdiPlaneMeterPannel(IPlane* plane,QWidget *parent = 0);
    ~MdiPlaneMeterPannel();
    void setRefreshDelay(int ms);
    int getRefreshDelay();
public slots:
    void updateUi();
protected slots:
    void closeEvent(QCloseEvent *event);
private:
    QPalette colorTheme( const QColor &base ) const;

    Ui::MdiPlaneMeterPannel *ui;
    IPlane* mPlane;
    QTimer* mRefreshTimer;
    int mRefreshDelay;
};

#endif // MDIPLANEMETERPANNEL_H
