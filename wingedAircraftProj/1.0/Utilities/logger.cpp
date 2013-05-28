#include "logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

QMutex Logger::mLock;
Logger* Logger::mCurLogger=0;

Logger::Logger(QString FileName)
{
    SetFile(FileName);
    mTraceLevel = (int)INFO;
}
void Logger::SetFile(QString filename)
{
    mFileName = filename;
}
QString Logger::GetFileName()
{
    return mFileName;
}
void Logger::SetTraceLevel(unsigned int level)
{
    mTraceLevel = level;
}
unsigned int Logger::GetTraceLevel()
{
    return mTraceLevel;
}
bool Logger::Log(QString str,LogType logtype,int tracelevel)
{
    bool succes=false;
//    if(tracelevel<0)
//        tracelevel = (unsigned int)logtype;
//    if(tracelevel<=mTraceLevel)
    if(checkTraceLevel(logtype,mTraceLevel,tracelevel))
    {
        QFile file(mFileName);
        if(file.open(QIODevice::WriteOnly |
                     QIODevice::Append |
                     QIODevice::Text))
        {
            QTextStream stream(&file);
            if(stream.pos())
                stream << "\n";
            for(int i=0; i<tracelevel; i++)
                stream << "\t";
            stream << createLogString(str,logtype);
            file.close();
        }
    }
    return succes;
}
void Logger::SetCurLogger(Logger* logger)
{
    if(logger)
    {
        mLock.lock();
        mCurLogger = logger;
        mLock.unlock();
    }
}
Logger* Logger::GetCurLogger()
{
    return mCurLogger;
}
bool Logger::curLog(QString str,LogType logtype,int tracelevel)
{
    bool succes=false;
    if(mCurLogger)
    {
        mLock.lock();
        succes = mCurLogger->Log(str,logtype,tracelevel);
        mLock.unlock();
    }
    return succes;
}
bool Logger::checkTraceLevel(LogType logtype,unsigned int setTraceLevel,int traceLevel)
{
    if(traceLevel<0)
        traceLevel = (unsigned int)logtype;
    return (traceLevel<=setTraceLevel);
}
QString Logger::createLogString(QString str,LogType logtype)
{
    return QString("%0 (%1) : %2")
            .arg(LogTypeStr(logtype))
            .arg(QDateTime::currentDateTime().toString())
            .arg(str);
}
QString Logger::LogTypeStr(LogType type)
{
    QString logtypestr;
    switch(type)
    {
    case ERROR:
        logtypestr = "ERROR";
        break;
    case WARNING:
        logtypestr = "WARNING";
        break;
    case INFO:
        logtypestr = "INFO";
        break;
    case DEBUG:
        logtypestr = "DEBUG";
        break;
    default:
        logtypestr = "LOG";
    }
    return logtypestr;
}
