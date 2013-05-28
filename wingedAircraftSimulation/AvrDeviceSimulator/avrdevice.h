#ifndef AVRDEVICE_H
#define AVRDEVICE_H

#include <QObject>
#include <QHash>
#include <QStringList>
#include "AvrDeviceSimulator_global.h"
#include "SimulatorDefinisions.h"

class QProcess;

class AVRDEVICESIMULATORSHARED_EXPORT AvrDevice : public QObject
{
    Q_OBJECT
public:
    explicit AvrDevice(QString device,
                       QString srcPath,
                       QString appPath,
                       QString configfile,
                       QObject *parent = 0);
    virtual ~AvrDevice();

    bool start();
    void stop();

    void setDeviceType(QString device);
    QString getDeviceType();
    void setSrcPath(QString srcPath);
    QString getSrcPath();
    void setAppPath(QString appPath);
    QString getAppPath();
    void setConfigFile(QString configfile);
    QString getConfigFile();

    void setDisplayFields(QStringList& fields);
    QStringList getDisplayFields();
    BYTE getRegValue(QString reg);
    void setRegValue(QString reg,BYTE value);
    QHash<QString,BYTE> getRegValueMap();
signals:
    void registerSet(QString reg,BYTE data);
    void stepAdvanced();
    void valueChanged();
private slots:
    void onAvrSimulator_readyRead();
    void onAvrGDB_readyRead();
private:
    void loadRegisterMap(QString filename);
    bool startAvrSimulator();
    bool startAvrGDB();
    void stopAvrSimulator();
    void stopAvrGDB();
    void stepLine();
    void checkIfStarting(QString& data);
    void readRegValues(QString& data);
    bool isRegValue(QString& data);
    void copyRegValue(QString& data);

    QString mDeviceType;
    QString mStrConfigFile;
    QString mSrcPath;
    QString mAppPath;
    bool bGDBstarted;
    bool bReadingFields;
    bool bTerminalActive;
    bool bRegChanged;
    int regReadCount;
    QProcess* mSimulProcess;
    QProcess* mGDBProcess;
    int mLineN;
    QHash<QString,BYTE> mRegValueMap;
    QHash<QString,QString> mRegisterMap;
    QHash<QString,QString> mRegisterNameMap;
    QStringList mDisplayFields;
};

#endif // AVRDEVICE_H
