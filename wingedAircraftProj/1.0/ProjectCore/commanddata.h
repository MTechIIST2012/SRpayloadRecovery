#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include "ICommandData.h"
#include "typedefs.h"
#include "ProjectCore_global.h"
#include <QByteArray>

class PROJECTCORESHARED_EXPORT AbstractCommandData : public ICommandData
{
public:
    AbstractCommandData(int datatype=TYPE_UNKNOWN);
    virtual ~AbstractCommandData();
    virtual void setType(int datatype);
    virtual int getType();
private:
    int mDataType;
};

class PROJECTCORESHARED_EXPORT ByteCommandData : public AbstractCommandData
{
public:
    ByteCommandData(int datatype=TYPE_BYTE,BYTE data=0x0);
    virtual ~ByteCommandData();
    void setData(BYTE data);
    BYTE getData();

    // ICommandData interface
    virtual void serialize(QDataStream& stream);
    virtual bool deserialize(QDataStream& stream);
    virtual int compare(ICommandData* other);
    virtual ICommandData* cloneData();
private:
    BYTE mByteData;
};

class PROJECTCORESHARED_EXPORT ByteArrayCommandData : public AbstractCommandData
{
public:
    ByteArrayCommandData(int datatype=TYPE_BYTEARRAY,QByteArray data=QByteArray());
    virtual ~ByteArrayCommandData();
    void setData(const QByteArray& data);
    QByteArray getData();

    // ICommandData interface
    virtual void serialize(QDataStream& stream);
    virtual bool deserialize(QDataStream& stream);
    virtual int compare(ICommandData* other);
    virtual ICommandData* cloneData();
private:
    QByteArray mBtArrData;
};

#endif // COMMANDDATA_H
