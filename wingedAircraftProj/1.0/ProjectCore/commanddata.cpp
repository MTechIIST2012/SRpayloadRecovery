#include "commanddata.h"

AbstractCommandData::AbstractCommandData(int datatype)
{
    mDataType = datatype;
}

AbstractCommandData::~AbstractCommandData()
{

}

void AbstractCommandData::setType(int datatype)
{
    mDataType = datatype;
}

int AbstractCommandData::getType()
{
    return mDataType;
}


////////////////////////ByteCommandData///////////////////////////////////////////////

ByteCommandData::ByteCommandData(int datatype,BYTE data)
    : AbstractCommandData(datatype)
{
    mByteData = data;
}

ByteCommandData::~ByteCommandData()
{

}

void ByteCommandData::setData(BYTE data)
{
    mByteData = data;
}

BYTE ByteCommandData::getData()
{
    return mByteData;
}

void ByteCommandData::serialize(QDataStream& stream)
{
    stream.readRawData((char*)&mByteData,1);
}

bool ByteCommandData::deserialize(QDataStream& stream)
{
    bool succes=false;
    if(!stream.atEnd())
    {
        stream.writeRawData((char*)&mByteData,1);
        succes = true;
    }
    return succes;
}

int ByteCommandData::compare(ICommandData* other)
{
    int ans = -2;
    if(other->getType() == getType())
    {
        ByteCommandData* otherByteCmdData = dynamic_cast<ByteCommandData*>(other);
        if(otherByteCmdData)
        {
            BYTE otherData = otherByteCmdData->getData();
            if(mByteData == otherData)
            {
                ans = 0;
            }
            else if(otherData < mByteData)
            {
                ans = -1;
            }
            else if(otherData > mByteData)
            {
                ans = 1;
            }
        }
    }
    return ans;
}

ICommandData* ByteCommandData::cloneData()
{
    ICommandData* clone = new ByteCommandData(getType(),mByteData);
    return clone;
}

///////////////////////////ByteArrayCommandData//////////////////////////////////////////////////////

ByteArrayCommandData::ByteArrayCommandData(int datatype,QByteArray data)
    : AbstractCommandData(datatype)
{
    mBtArrData = data;
}

ByteArrayCommandData::~ByteArrayCommandData()
{

}

void ByteArrayCommandData::setData(const QByteArray& data)
{
    mBtArrData = data;
}

QByteArray ByteArrayCommandData::getData()
{
    return mBtArrData;
}

void ByteArrayCommandData::serialize(QDataStream& stream)    // Todo: check how bytearray is serialized
{
    stream << mBtArrData;
}

bool ByteArrayCommandData::deserialize(QDataStream& stream)
{
    bool succes=false;
    if(!stream.atEnd())
    {
        stream >> mBtArrData;
        succes = true;
    }
    return succes;
}

int ByteArrayCommandData::compare(ICommandData* other)
{
    int ans = -2;
    if(other->getType() == getType())
    {
        ByteArrayCommandData* otherBtArrCmdData = dynamic_cast<ByteArrayCommandData*>(other);
        if(otherBtArrCmdData)
        {
            QByteArray otherData = otherBtArrCmdData->getData();
            if(mBtArrData == otherData)
            {
                ans = 0;
            }
            else if(otherData < mBtArrData)
            {
                ans = -1;
            }
            else if(otherData > mBtArrData)
            {
                ans = 1;
            }
        }
    }
    return ans;
}

ICommandData* ByteArrayCommandData::cloneData()
{
    ICommandData* clone = new ByteArrayCommandData(getType(),mBtArrData);
    return clone;
}
