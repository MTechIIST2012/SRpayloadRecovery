#include "avrdeviceview.h"
#include "ui_avrdeviceview.h"
#include "avrdevice.h"
#include "SimulatorDefinisions.h"
#include <QFileDialog>
#include <QStandardItemModel>

AvrDeviceView::AvrDeviceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvrDeviceView)
{
    ui->setupUi(this);
    mAvrDevice = 0;
    mRegStdModel = new QStandardItemModel(0,2,this);
    ui->tblRegisters->setModel(mRegStdModel);

    connect(ui->btnStart,
            SIGNAL(clicked()),
            this,
            SLOT(start()));
    connect(ui->btnStop,
            SIGNAL(clicked()),
            this,
            SLOT(stop()));
}

AvrDeviceView::~AvrDeviceView()
{
    delete ui;
}

void AvrDeviceView::setAvrDevice(AvrDevice* device)
{
    mAvrDevice = device;
    connect(mAvrDevice,
            SIGNAL(valueChanged()),
            this,
            SLOT(on_avrdevice_valueChanged()));
    updateView();
}

AvrDevice* AvrDeviceView::getAvrDevice()
{
    return mAvrDevice;
}

void AvrDeviceView::setApp(QString app)
{
    ui->edtApp->setText(app);
}

QString AvrDeviceView::getApp()
{
    return ui->edtApp->text();
}

void AvrDeviceView::setWorkingDir(QString workingDir)
{
    ui->edtWorkingDir->setText(workingDir);
}

QString AvrDeviceView::getWorkingDir()
{
    return ui->edtWorkingDir->text();
}

void AvrDeviceView::setConfigFile(QString configfile)
{
    ui->edtConfigFile->setText(configfile);
}

QString AvrDeviceView::getConfigFile()
{
    return ui->edtConfigFile->text();
}

void AvrDeviceView::setFields(QStringList& fields)
{
    ui->edtFields->setText(fields.join(","));
}

QStringList AvrDeviceView::getFields()
{
    return ui->edtFields->text().split(",");
}

void AvrDeviceView::start()
{
    if(!mAvrDevice)
        return;
    updateDevice();
    createRegModel();
    mAvrDevice->start();
}

void AvrDeviceView::stop()
{
    if(!mAvrDevice)
        return;
    mAvrDevice->stop();
}


void AvrDeviceView::on_btnBrowseApp_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("App file"),
                                                     "/home",
                                                     tr("Executable (*.elf)"));
    if(!fileName.isEmpty())
    {
        setApp(fileName);
    }
}

void AvrDeviceView::on_btnBrowseWorkingDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open working directory"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        setWorkingDir(dir);
    }
}

void AvrDeviceView::on_btnBrowseConfigFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Config file"),
                                                     "/home",
                                                     tr("Config file (*.ini)"));
    if(!fileName.isEmpty())
    {
        setConfigFile(fileName);
    }
}

void AvrDeviceView::on_avrdevice_valueChanged()
{
    updateRegValues();
}

void AvrDeviceView::updateView()
{
    if(!mAvrDevice)
        return;

    setApp(mAvrDevice->getAppPath());
    setWorkingDir(mAvrDevice->getSrcPath());
    setConfigFile(mAvrDevice->getConfigFile());
    QStringList fields = mAvrDevice->getDisplayFields();
    setFields(fields);
}

void AvrDeviceView::updateDevice()
{
    if(!mAvrDevice)
        return;

    mAvrDevice->setAppPath(getApp());
    mAvrDevice->setSrcPath(getWorkingDir());
    mAvrDevice->setConfigFile(getConfigFile());
    QStringList fields = getFields();
    mAvrDevice->setDisplayFields(fields);
}

void AvrDeviceView::createRegModel()
{
    mRegStdModel->clear();
    mRegStdItemMap.clear();
    QStringList regNames = getFields();
    int row = 0;
    foreach(QString regname,regNames)
    {
//        mRegStdModel->appendRow();
         QStandardItem *RegItem = new QStandardItem(regname);
         QStandardItem *ValueItem = new QStandardItem(QString::number(0,16));
         mRegStdModel->setItem(row,0,RegItem);
         mRegStdModel->setItem(row,1,ValueItem);
         mRegStdItemMap.insert(regname,ValueItem);
         row++;
    }
}

void AvrDeviceView::updateRegValues()
{
    if(!mAvrDevice)
        return;

    QStringList regNames = getFields();
    foreach(QString regname,regNames)
    {
        BYTE data = mAvrDevice->getRegValue(regname);
        QStandardItem *ValueItem = mRegStdItemMap.value(regname,0);
        if(ValueItem)
        {
            ValueItem->setText(QString::number((int)data,16));
        }
    }
}
