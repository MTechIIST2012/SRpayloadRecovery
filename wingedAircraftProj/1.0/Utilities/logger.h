#ifndef LOGGER_H
#define LOGGER_H

#include "Utilities_global.h"
#include <QMutex>
#include <QString>

class UTILITIESSHARED_EXPORT Logger
{
public:
    enum LogType
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };


    Logger(QString FileName);
    void SetFile(QString filename);
    QString GetFileName();
    void SetTraceLevel(unsigned int level);
    unsigned int GetTraceLevel();
    bool Log(QString str,LogType logtype=INFO,int tracelevel=-1);  // <0 is tracelevel of type

    static void SetCurLogger(Logger* logger);
    static Logger* GetCurLogger();
    static bool curLog(QString str,LogType logtype=INFO,int tracelevel=-1);
protected:
    virtual bool checkTraceLevel(LogType logtype,unsigned int setTraceLevel,int traceLevel=-1);
    virtual QString createLogString(QString str,LogType logtype=INFO);
private:
    QString LogTypeStr(LogType type);

    QString mFileName;
    unsigned int mTraceLevel;
    static QMutex mLock;

    static Logger* mCurLogger;
};

#endif // LOGGER_H
