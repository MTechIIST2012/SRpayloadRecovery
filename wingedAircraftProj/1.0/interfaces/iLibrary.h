#ifndef ILIBRARY_H
#define ILIBRARY_H

#include <QStringList>
#include <QList>

class iLibrary
{
public:
    virtual ~iLibrary() {}
    virtual void setName(QString name)=0;
    virtual QString getName()=0;
    virtual void setValue(QString name,QVariant value)=0;
    virtual QVariant getValue(QString name)=0;
    virtual QString toString(QString name,QVariant value)=0;
    virtual QVariant fromString(QString name,QString value)=0;
    virtual QStringList getKeys()=0;
};

class iLibraryClient
{
public:
    virtual ~iLibraryClient() {}
    virtual iLibrary* createLibrary()=0;
    virtual bool fillLibrary(iLibrary* lib)=0;
    virtual bool setLibrary(iLibrary* lib)=0;
};

class iLibraryContainer
{
public:
    virtual ~iLibraryContainer() {}
    virtual bool addLibrary(iLibrary* lib)=0;
    virtual bool removeLibrary(QString name)=0;
    virtual iLibrary* getLibrary(QString name)=0;
    virtual QList<iLibrary*> getLibraryList()=0;
    virtual bool contains(QString name)=0;
    virtual int count()=0;
    virtual void clear()=0;
    virtual QStringList getLibraryNames()=0;
    virtual void setLibraryClient(iLibraryClient* client)=0;
    virtual iLibraryClient* getLibraryClient()=0;
    virtual bool write(QString filename)=0;
    virtual bool load(QString filename)=0;
};

#endif // ILIBRARY_H
