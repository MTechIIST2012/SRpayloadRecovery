#ifndef ICOMMANDDATA_H
#define ICOMMANDDATA_H

#include <QString>
#include <QDataStream>

class ICommandData
{
public:
    virtual ~ICommandData() {}
    virtual int getType()=0;
    virtual void serialize(QDataStream& stream)=0;
    virtual bool deserialize(QDataStream& stream)=0;
    virtual int compare(ICommandData* other)=0;
    virtual ICommandData* cloneData()=0;
};


#endif  // ICOMMANDDATA_H
