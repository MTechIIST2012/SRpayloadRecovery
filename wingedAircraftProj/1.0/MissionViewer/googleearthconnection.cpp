#include "googleearthconnection.h"
#include "MissionViewerCommon.h"
#include "IPlane.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QProcess>

GoogleEarthConnection::GoogleEarthConnection(QString root,QString settingsFile,IPlane* plane,QObject *parent) :
    QObject(parent)
{
    mPlane = plane;
    mSettingsFile = settingsFile;
    mRootPath = root;
    mGEprocess = 0;
}

GoogleEarthConnection::~GoogleEarthConnection()
{
    stopGE();
}

void GoogleEarthConnection::setRootPath(QString path)
{
    mRootPath = path;
}

QString GoogleEarthConnection::getRootPath()
{
    return mRootPath;
}

void GoogleEarthConnection::setSettingsFile(QString file)
{
    mSettingsFile = file;
}

QString GoogleEarthConnection::getSettingsFile()
{
    return mSettingsFile;
}

void GoogleEarthConnection::setPlane(IPlane* plane)
{
    mPlane = plane;
}

IPlane* GoogleEarthConnection::getPlane()
{
    return mPlane;
}

bool GoogleEarthConnection::startGE()
{
    updateSettings();
    if(!mGEprocess)
        mGEprocess = new QProcess(this);
    mGEprocess->start(mSettings.value(FIELD_GEAPP));
    return mGEprocess->waitForStarted();
}

void GoogleEarthConnection::stopGE()
{
    if(mGEprocess)
    {
        mGEprocess->kill();
        delete mGEprocess;
        mGEprocess = 0;
    }
}

void GoogleEarthConnection::updateGE()
{
    //updateSettings();
    QString outpath = mRootPath + "/" + mSettings.value(FIELD_GEOUTDIR);
    QString templateFile = mRootPath + "/" + mSettings.value(FIELD_TEMPLATE);
    QString tempfile = mRootPath + "/"+ mSettings.value(FIELD_GEOUTDIR) + "/" + mSettings.value(FIELD_RUNTIMEFILE);

    QDir dir(outpath);
    if(!dir.exists())
        dir.mkpath(outpath);

    if(dir.exists())
    {
        QFile TemplateFile(templateFile);
        QFile OutFile(tempfile);
        if (TemplateFile.open(QIODevice::ReadOnly | QIODevice::Text) &&
            OutFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString str = TemplateFile.readAll();
            TemplateFile.close();
            updateFileString(str);
            OutFile.write(str.toAscii());
            OutFile.close();
        }
    }
}

void GoogleEarthConnection::updateSettings()
{
    mSettings.clear();
    if(!QFile::exists(mSettingsFile))
        return;

    QSettings settings(mSettingsFile,QSettings::IniFormat);

    settings.beginGroup(GROUP_GE);
    mSettings.insert(FIELD_GEAPP,settings.value(FIELD_GEAPP).toString().trimmed());
    settings.endGroup();

    settings.beginGroup(GROUP_FILES);
    mSettings.insert(FIELD_TEMPLATE,settings.value(FIELD_TEMPLATE).toString().trimmed());
    mSettings.insert(FIELD_MODEL,settings.value(FIELD_MODEL).toString().trimmed());
    mSettings.insert(FIELD_RUNTIMEFILE,settings.value(FIELD_RUNTIMEFILE).toString().trimmed());
    settings.endGroup();

    settings.beginGroup(GROUP_OUTDIR);
    mSettings.insert(FIELD_GEOUTDIR,settings.value(FIELD_GEOUTDIR).toString().trimmed());
    settings.endGroup();

    settings.beginGroup(GROUP_ORIENTAION);
    mSettings.insert(FIELD_ROTX,settings.value(FIELD_ROTX).toString().trimmed());
    mSettings.insert(FIELD_ROTY,settings.value(FIELD_ROTY).toString().trimmed());
    mSettings.insert(FIELD_ROTZ,settings.value(FIELD_ROTZ).toString().trimmed());
    mSettings.insert(FIELD_ROT_ORDER,settings.value(FIELD_ROT_ORDER).toString().trimmed());
    settings.endGroup();

    settings.beginGroup(GROUP_SCALE);
    mSettings.insert(FIELD_SCALEX,settings.value(FIELD_SCALEX).toString().trimmed());
    mSettings.insert(FIELD_SCALEY,settings.value(FIELD_SCALEY).toString().trimmed());
    mSettings.insert(FIELD_SCALEZ,settings.value(FIELD_SCALEZ).toString().trimmed());
    settings.endGroup();
}

void GoogleEarthConnection::updateFileString(QString& str)
{
    if(mPlane)
    {
        float pitch = mPlane->getOrientation().pitch + mSettings.value(FIELD_ROTY).toFloat();
        float roll = mPlane->getOrientation().roll + mSettings.value(FIELD_ROTX).toFloat();
        float yaw = mPlane->getOrientation().yaw + mSettings.value(FIELD_ROTZ).toFloat();

        float scale_x = mSettings.value(FIELD_SCALEX).toFloat();
        float scale_y = mSettings.value(FIELD_SCALEY).toFloat();
        float scale_z = mSettings.value(FIELD_SCALEZ).toFloat();

        str = str.replace("%longitude%",QString::number(mPlane->getLongitude()))
              .replace("%latitude%",QString::number(mPlane->getLatitude()))
              .replace("%altitude%",QString::number(mPlane->getAltitude()))
              .replace("%tilt%",QString::number(pitch))
              .replace("%roll%",QString::number(roll))
              .replace("%heading%",QString::number(yaw))
              .replace("%scale_x%",QString::number(scale_x))
              .replace("%scale_y%",QString::number(scale_y))
              .replace("%scale_z%",QString::number(scale_z))
              .replace("%dae_model%",mSettings.value(FIELD_MODEL));     // relative to the script file
    }
}
