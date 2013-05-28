#ifndef ORDEREDHASH_H
#define ORDEREDHASH_H

#include <QHash>
#include <QList>

template <class KEY,class VAL>
    class OrderedHash
{
public:
    void insert(const KEY& k,const VAL& v,int index);
    void append(const KEY& k,const VAL& v);
    void remove(const KEY& k);
    QList<KEY> keys();
    QList<VAL> values();
    QList<KEY> orderedKeys();
    QList<VAL> orderedValues();
    int indexOf(const KEY& k);
    int count();
    VAL value(const KEY& k,const VAL& defaultVal=VAL());
    void clear();
private:
    QHash<KEY,VAL> mHash;
    QList<KEY> mList;
};

template <class KEY,class VAL>
        void OrderedHash<KEY,VAL>::insert(const KEY& k,const VAL& v,int index)
{
    mHash.insert(k,v);
    mList.insert(index,k);
}

template <class KEY,class VAL>
void OrderedHash<KEY,VAL>::append(const KEY& k,const VAL& v)
{
    if(mHash.contains(k))
        remove(k);
    mHash.insert(k,v);
    mList.append(k);
}

template <class KEY,class VAL>
void OrderedHash<KEY,VAL>::remove(const KEY& k)
{
    if(mHash.contains(k))
    {
        mHash.remove(k);
        mList.removeAll(k);
    }
}

template <class KEY,class VAL>
QList<KEY> OrderedHash<KEY,VAL>::keys()
{
    return mHash.keys();
}

template <class KEY,class VAL>
QList<VAL> OrderedHash<KEY,VAL>::values()
{
    return mHash.values();
}

template <class KEY,class VAL>
QList<KEY> OrderedHash<KEY,VAL>::orderedKeys()
{
    return mList;
}

template <class KEY,class VAL>
QList<VAL> OrderedHash<KEY,VAL>::orderedValues()
{
    QList<VAL> valuelist;
    foreach(KEY k,mList)
    {
        valuelist.append(mHash.value(k));
    }
    return valuelist;
}

template <class KEY,class VAL>
int OrderedHash<KEY,VAL>::indexOf(const KEY& k)
{
    return mList.count();
}

template <class KEY,class VAL>
int OrderedHash<KEY,VAL>::count()
{
    return mList.count();
}

template <class KEY,class VAL>
VAL OrderedHash<KEY,VAL>::value(const KEY& k,const VAL& defaultVal)
{
    return mHash.value(k,defaultVal);
}

template <class KEY,class VAL>
void OrderedHash<KEY,VAL>::clear()
{
    mHash.clear();
    mList.clear();
}

#endif // ORDEREDHASH_H
