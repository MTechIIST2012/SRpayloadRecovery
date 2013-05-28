#ifndef GOOGLEEARTHCONNECTION_H
#define GOOGLEEARTHCONNECTION_H

#include <QObject>
#include <QHash>

class IPlane;
class QProcess;

class GoogleEarthConnection : public QObject
{
    Q_OBJECT
public:
    explicit GoogleEarthConnection(QString root,QString settingsFile,IPlane* plane,QObject *parent = 0);
    virtual ~GoogleEarthConnection();
    void setRootPath(QString path);
    QString getRootPath();
    void setSettingsFile(QString file);
    QString getSettingsFile();
    void setPlane(IPlane* plane);
    IPlane* getPlane();
    bool startGE();
    void stopGE();
public slots:
    void updateGE();
    void updateSettings();
private:
    void updateFileString(QString& str);

    IPlane* mPlane;
    QString mSettingsFile;
    QString mRootPath;
    QProcess* mGEprocess;
    QHash<QString,QString> mSettings;
};

#endif // GOOGLEEARTHCONNECTION_H
