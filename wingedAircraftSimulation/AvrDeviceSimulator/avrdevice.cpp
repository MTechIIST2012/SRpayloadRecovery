#include "avrdevice.h"
#include <QSettings>
#include <QStringList>
#include <QProcess>
#include <QDebug>

AvrDevice::AvrDevice(QString device,
                     QString srcPath,
                     QString appPath,
                     QString configfile,
                     QObject *parent) :
    QObject(parent)
{
    mDeviceType = device;
    mSrcPath = srcPath;
    mAppPath = appPath;
    mStrConfigFile = configfile;
    mSimulProcess = new QProcess(this);
    mGDBProcess = new QProcess(this);
}

AvrDevice::~AvrDevice()
{
    stop();
}

bool AvrDevice::start()
{
    loadRegisterMap(mStrConfigFile);
    startAvrSimulator();
    startAvrGDB();
}

void AvrDevice::stop()
{
    stopAvrSimulator();
    stopAvrGDB();
}

void AvrDevice::setDeviceType(QString device)
{
    mDeviceType = device;
}

QString AvrDevice::getDeviceType()
{
    return mDeviceType;
}

void AvrDevice::setSrcPath(QString srcPath)
{
    mSrcPath = srcPath;
}

QString AvrDevice::getSrcPath()
{
    return mSrcPath;
}

void AvrDevice::setAppPath(QString appPath)
{
    mAppPath = appPath;
}

QString AvrDevice::getAppPath()
{
    return mAppPath;
}

void AvrDevice::setConfigFile(QString configfile)
{
    mStrConfigFile = configfile;
}

QString AvrDevice::getConfigFile()
{
    return mStrConfigFile;
}

void AvrDevice::setDisplayFields(QStringList& fields)
{
    mDisplayFields = fields;
}

QStringList AvrDevice::getDisplayFields()
{
    return mDisplayFields;
}

BYTE AvrDevice::getRegValue(QString reg)
{
    return mRegValueMap.value(reg);
}

void AvrDevice::setRegValue(QString reg,BYTE value)
{
    // not implimented
}

QHash<QString,BYTE> AvrDevice::getRegValueMap()
{
    return mRegValueMap;
}

void AvrDevice::onAvrSimulator_readyRead()
{
    qDebug() << mSimulProcess->readAll();
}

void AvrDevice::onAvrGDB_readyRead()
{
    QString data(mGDBProcess->readAll());

    data = data.trimmed();
    if(data.endsWith("(gdb)"))
        bTerminalActive = true;
    else
        bTerminalActive = false;


    if(!bGDBstarted)
        checkIfStarting(data);
    else if(!bReadingFields)
        readRegValues(data);
    else if(isRegValue(data))
        copyRegValue(data);
    else
        stepLine();

    //qDebug() << data;
}

void AvrDevice::loadRegisterMap(QString filename)
{
    mRegisterMap.clear();
    mRegisterNameMap.clear();
    QSettings settings(filename,QSettings::IniFormat,this);
    settings.beginGroup("portmapping");
    QStringList regNames = settings.childKeys();
    foreach(QString regname,regNames)
    {
        QString regName = regname.trimmed();
        QString reqMem = settings.value(regname).toString().trimmed();
        mRegisterMap.insert(regName,reqMem);
        mRegisterNameMap.insert(reqMem,regName);
    }
    //qDebug() << "Register map" << mRegisterMap;
}

bool AvrDevice::startAvrSimulator()
{
    bool bSucces=false;
    QStringList argu;
    argu << "-d" << mDeviceType << "-g" << "\n";
    mSimulProcess->start("simulavr",argu);

    connect(mSimulProcess,
            SIGNAL(readyRead()),
            this,
            SLOT(onAvrSimulator_readyRead()));


    return bSucces;
}

bool AvrDevice::startAvrGDB()
{
    bool bSucces=false;
    bGDBstarted = false;
    bReadingFields = false;
    bTerminalActive = false;
    QStringList argu;
    mGDBProcess->setWorkingDirectory(mSrcPath);
    mGDBProcess->start("avr-gdb",argu);
    mGDBProcess->write(QString("file "+mAppPath + "\n").toAscii() );
    mGDBProcess->write( "target remote localhost:1212\n" );
    mGDBProcess->write( "load\n" );
    mGDBProcess->write( "list\n" );
    mGDBProcess->write( "break main\n" );
    connect(mGDBProcess,
            SIGNAL(readyRead()),
            this,
            SLOT(onAvrGDB_readyRead()));

    bSucces = true;
    return bSucces;
}

void AvrDevice::stopAvrSimulator()
{
    disconnect(mSimulProcess,
            SIGNAL(readyRead()),
            this,
            SLOT(onAvrGDB_readyRead()));
    mGDBProcess->kill();
}

void AvrDevice::stopAvrGDB()
{
    disconnect(mGDBProcess,
            SIGNAL(readyRead()),
            this,
            SLOT(onAvrGDB_readyRead()));
    mGDBProcess->kill();
}

void AvrDevice::stepLine()
{
    bReadingFields = false;
    if(bRegChanged)
        emit valueChanged();
    emit stepAdvanced();
    mGDBProcess->write("s\n");
}

void AvrDevice::checkIfStarting(QString& data)
{
    if(data.count(QRegExp("Breakpoint . at ....: file main.c, line .\."))>0)
    {
        mGDBProcess->write( "c\n" );
    }
    else if(bTerminalActive && data.count(QRegExp("Breakpoint"))>0)   // "Breakpoint ., main () at main.c"
    {
        bGDBstarted = true;
        mGDBProcess->write("s\n");
    }
}

void AvrDevice::readRegValues(QString& data)
{
    if(bTerminalActive)
    {
        bReadingFields = true;
        bRegChanged = false;
        regReadCount = 0;
        foreach(QString field,mDisplayFields)
        {
            QString mem = mRegisterMap.value(field);
            if(!mem.isEmpty())
            {
                QString readCmd = "x/bx "+mem+"\n";
                mGDBProcess->write(readCmd.toAscii());
            }
        }
        //bReadingFields = false;
    }
}

bool AvrDevice::isRegValue(QString& data)
{
    data = data.remove("(gdb)").trimmed();
    bool bIsReg = (data.contains(QRegExp(".*0x8000..:.*0x...*")));
    return bIsReg;
}

void AvrDevice::copyRegValue(QString& data)
{
    data = data.remove("(gdb)").remove("8000");
    QStringList dataLines = data.split("\n");
    foreach(QString line,dataLines)
    {
        QStringList parts = line.split(":");
        if(parts.count() == 2)
        {
            QString regmem = parts.at(0);  regmem = regmem.trimmed();
            QString regVal = parts.at(1); regVal = regVal.remove("0x").trimmed();

            QString regname = mRegisterNameMap.value(regmem);
            BYTE prevVal = mRegValueMap.value(regname);
            BYTE newVal = regVal.toInt(0,16);
            if(prevVal != newVal)
            {
                mRegValueMap.insert(regname,newVal);
                bRegChanged = true;
            }
            regReadCount++;
        }
    }

    if(regReadCount >= mDisplayFields.count())
        stepLine();
}
