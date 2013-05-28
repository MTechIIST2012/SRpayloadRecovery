#ifndef AVRDEVICEVIEW_H
#define AVRDEVICEVIEW_H

#include <QWidget>
#include <QStringList>
#include <QHash>
#include "AvrDeviceSimulator_global.h"

namespace Ui {
    class AvrDeviceView;
}

class AvrDevice;
class QStandardItem;
class QStandardItemModel;

class AVRDEVICESIMULATORSHARED_EXPORT AvrDeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit AvrDeviceView(QWidget *parent = 0);
    ~AvrDeviceView();
    void setAvrDevice(AvrDevice* device);
    AvrDevice* getAvrDevice();
    void setApp(QString app);
    QString getApp();
    void setWorkingDir(QString workingDir);
    QString getWorkingDir();
    void setConfigFile(QString configfile);
    QString getConfigFile();
    void setFields(QStringList& fields);
    QStringList getFields();
public slots:
    void start();
    void stop();
private slots:
    void on_btnBrowseConfigFile_clicked();
    void on_btnBrowseWorkingDir_clicked();
    void on_btnBrowseApp_clicked();
    void on_avrdevice_valueChanged();
private:
    void updateView();
    void updateDevice();
    void createRegModel();
    void updateRegValues();

    Ui::AvrDeviceView *ui;
    AvrDevice* mAvrDevice;
    QHash<QString,QStandardItem*> mRegStdItemMap;
    QStandardItemModel* mRegStdModel;
};

#endif // AVRDEVICEVIEW_H
