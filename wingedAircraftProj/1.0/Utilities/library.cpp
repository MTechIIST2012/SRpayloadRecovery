#include "library.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define LIBRARY_DOCNAME "LibraryContainer"
#define LIBRARYLIST_ELM_TAG "libraryList"
#define LIBRARY_ELM_TAG "library"
#define LIBRARY_ATTRB_NAME "name"
#define LIBRARY_ELM_VALUES "values"

Library::Library()
{

}

Library::~Library()
{

}

void Library::setName(QString name)
{
    mName = name;
}

QString Library::getName()
{
    return mName;
}

void Library::setValue(QString name,QVariant value)
{
    if(!name.isEmpty())
        mValueHash.insert(name,value.toString());
}

QVariant Library::getValue(QString name)
{
    return mValueHash.value(name);
}

QString Library::toString(QString /*name*/,QVariant value)
{
    return value.toString();
}

QVariant Library::fromString(QString /*name*/,QString value)
{
    return value;
}

QStringList Library::getKeys()
{
    return mValueHash.keys();
}

//////////////////////////LibraryContainer//////////////////////////////////////////////////
LibraryContainer::LibraryContainer()
{
    mLibClient = 0;
}

LibraryContainer::~LibraryContainer()
{
    clear();
}

bool LibraryContainer::addLibrary(iLibrary* lib)
{
    if(!lib)
        return false;
    QString libName = lib->getName();
    if(libName.isEmpty())
        return false;
    iLibrary* curLib = mLibraryHash.value(libName,0);
    if(curLib)
        delete curLib;

    mLibraryHash.insert(libName,lib);
    return true;
}

bool LibraryContainer::removeLibrary(QString libName)
{
    bool succes = false;
    iLibrary* curLib = mLibraryHash.value(libName,0);
    if(curLib)
    {
        delete curLib;
        mLibraryHash.remove(libName);
        succes = true;
    }
    return succes;
}

iLibrary* LibraryContainer::getLibrary(QString libName)
{
    iLibrary* curLib = mLibraryHash.value(libName,0);
    return curLib;
}

QList<iLibrary*> LibraryContainer::getLibraryList()
{
    return mLibraryHash.values();
}

bool LibraryContainer::contains(QString name)
{
    return mLibraryHash.contains(name);
}

int LibraryContainer::count()
{
    return mLibraryHash.count();
}

void LibraryContainer::clear()
{
    qDeleteAll(mLibraryHash.values());
    mLibraryHash.clear();
}

void LibraryContainer::setLibraryClient(iLibraryClient* client)
{
    mLibClient = client;
}

iLibraryClient* LibraryContainer::getLibraryClient()
{
    return mLibClient;
}

QStringList LibraryContainer::getLibraryNames()
{
    return mLibraryHash.keys();
}

bool LibraryContainer::write(QString filename)
{
    QDomDocument doc(LIBRARY_DOCNAME);
    QDomElement listElm = doc.createElement(LIBRARYLIST_ELM_TAG);
    foreach(iLibrary* lib,getLibraryList())
    {
        saveLibrary(lib,listElm,doc);
    }
    doc.appendChild(listElm);

    bool succes=false;
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << doc.toString();
        file.close();
        succes = true;
    }
    return succes;
}

bool LibraryContainer::load(QString filename)
{
    clear();

    QDomDocument doc(LIBRARY_DOCNAME);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QString errMsg;
    if (!doc.setContent(&file,&errMsg))
    {
        qDebug() << "XML doc error :" << errMsg;
        file.close();
        return false;
    }
    file.close();

    bool succes=true;
    QDomElement docElem = doc.documentElement();       // LIBRARYLIST_ELM_TAG
    QDomNodeList libraryNodes = docElem.elementsByTagName(LIBRARY_ELM_TAG);
    const int count = libraryNodes.count();

   // qDebug() << docElem.tagName();

    for(int i=0; i<count; i++)
    {
        QDomNode LibNode = libraryNodes.at(i);
        iLibrary* lib = loadLibrary(LibNode);
        if(lib)
            addLibrary(lib);
        else
            succes = false;
    }
    return succes;
}

iLibrary* LibraryContainer::loadLibrary(QDomNode& node)
{
    iLibrary* lib=0;
    if(!mLibClient)
        return lib;

    bool succes=true;
    QDomElement elm = node.toElement();
    if(elm.tagName() == LIBRARY_ELM_TAG)
    {
        lib = mLibClient->createLibrary();
        if(lib)
        {
            lib->setName(elm.attribute(LIBRARY_ATTRB_NAME));
            QDomNodeList ValueElmList = elm.elementsByTagName(LIBRARY_ELM_VALUES);
            const int ValueElmCount = ValueElmList.count();
            for(int elmIndex=0; elmIndex<ValueElmCount; elmIndex++)
            {
                QDomNode valueElm = ValueElmList.at(elmIndex);
                QDomNamedNodeMap values = valueElm.attributes();
                const int count = values.count();
                for(int i=0; i<count; i++)
                {
                    QDomNode val = values.item(i);
                    QDomAttr valAttr = val.toAttr();
                    if(!valAttr.isNull())
                    {
                        QString name = valAttr.name();
                        QVariant VarVal = lib->fromString(name,valAttr.value());
                        lib->setValue(name,VarVal);
                    }
                }
            }
        }
        else
            succes = false;
    }
    return lib;
}

bool LibraryContainer::saveLibrary(iLibrary* lib,QDomNode& node,QDomDocument& doc)
{
    if(!mLibClient || !lib)
        return false;

    QDomElement libElm = doc.createElement(LIBRARY_ELM_TAG);
    libElm.setAttribute(LIBRARY_ATTRB_NAME,lib->getName());
    QStringList keys = lib->getKeys();

    QDomElement libValElm = doc.createElement(LIBRARY_ELM_VALUES);
    foreach(QString key,keys)
    {
        libValElm.setAttribute(key,
                            lib->toString(key,lib->getValue(key)));
    }
    libElm.appendChild(libValElm);
    node.appendChild(libElm);
}
