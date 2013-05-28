#ifndef PLANECONTROLSWIDGET_H
#define PLANECONTROLSWIDGET_H

#include <QWidget>

namespace Ui {
    class PlaneControlsWidget;
}

class IPlane;

class PlaneControlsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlaneControlsWidget(IPlane* plane,QWidget *parent = 0);
    ~PlaneControlsWidget();
private slots:
    void onValueChange();
private:
    void updateUi();
    void updateFlight();

    Ui::PlaneControlsWidget *ui;
    IPlane* mPlane;
};

#endif // PLANECONTROLSWIDGET_H
