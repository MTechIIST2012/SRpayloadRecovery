#ifndef LIBRARY_H
#define LIBRARY_H

#include "iLibrary.h"
#include "Utilities_global.h"
#include <QHash>
#include <QVariant>

class QDomNode;
class QDomDocument;

class UTILITIESSHARED_EXPORT Library : public iLibrary
{
public:
    explicit Library();
    virtual ~Library();
    virtual void setName(QString name);
    virtual QString getName();
    virtual void setValue(QString name,QVariant value);
    virtual QVariant getValue(QString name);
    virtual QString toString(QString name,QVariant value);
    virtual QVariant fromString(QString name,QString value);
    virtual QStringList getKeys();
private:
    QString mName;
    QHash<QString,QString> mValueHash;
};

class UTILITIESSHARED_EXPORT LibraryContainer : public iLibraryContainer
{
public:
    explicit LibraryContainer();
    virtual ~LibraryContainer();
    virtual bool addLibrary(iLibrary* lib);
    virtual bool removeLibrary(QString libName);
    virtual iLibrary* getLibrary(QString libName);
    virtual QList<iLibrary*> getLibraryList();
    virtual bool contains(QString name);
    virtual int count();
    virtual void clear();
    virtual void setLibraryClient(iLibraryClient* client);
    virtual iLibraryClient* getLibraryClient();
    virtual QStringList getLibraryNames();
    virtual bool write(QString filename);
    virtual bool load(QString filename);
protected:
    virtual iLibrary* loadLibrary(QDomNode& node);
    virtual bool saveLibrary(iLibrary* lib,QDomNode& node,QDomDocument& doc);
private:
    QHash<QString,iLibrary*> mLibraryHash;
    iLibraryClient* mLibClient;
};

#endif // LIBRARY_H
