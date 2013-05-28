#ifndef _LIST_H_INCLUDED
#define _LIST_H_INCLUDED

template  <typename T>             // Todo: needs to impliment == operator
class _LinkedList
{
private:
          struct ListNode;
public:
          class Iterator
          {
          public:
                    Iterator(_LinkedList<T>::ListNode* node);
                    Iterator& next();
                    Iterator& previous();
                    const T& value();
                    bool isAtBegining();
                    bool isAtEnd();

                    Iterator& operator++ (int);
                    Iterator& operator-- (int);
          private:
                    _LinkedList<T>::ListNode* mNode;
          };


          _LinkedList();
          virtual ~_LinkedList();
          virtual  _LinkedList<T>& append(const T& obj);
          virtual  _LinkedList<T>& insert(int index,const T& obj);
          virtual void removeAt(int index);
          virtual int count() const;
          virtual  const T&  at(int index);
          virtual void clear();
          virtual Iterator start() const;
          virtual Iterator end() const;

          // operatiors.
          virtual  _LinkedList&  operator << (const T&  obj);
          _LinkedList& operator= (const _LinkedList& other);
private:
          struct ListNode
          {
                    ListNode* mPrevNode;
                    T* mPtr;
                    ListNode* mNextNode;

                    ListNode()
                    {
                              mPrevNode = 0;
                              mPtr = 0;
                              mNextNode = 0;
                    }

                    ~ListNode()
                    {
                              if(mPtr != 0)
                                        delete mPtr;
                    }
          };


          virtual ListNode* nodeAt(int index);

          int mCount;
          ListNode* mNodeListStart;
          ListNode* mNodeListEnd;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
template  <typename T>
 _LinkedList<T>::_LinkedList()
 {
           mCount = 0;
           mNodeListStart = 0;
           mNodeListEnd = 0;
 }

template  <typename T>
 _LinkedList<T>::~_LinkedList()
 {
         clear();
 }

 template  <typename T>
_LinkedList<T>& _LinkedList<T>::append(const T& obj)
{
          return insert(mCount,obj);
}

template  <typename T>
_LinkedList<T>&  _LinkedList<T>::insert(int index,const T& obj)
{
          if(mCount > 0)
          {
                     index = (index >=mCount ) ? mCount: index ;
                    index = (index <=0)? 0 : index;

                    ListNode* listNode = new ListNode();
                    listNode->mPtr = new T();
                    *(listNode->mPtr) = obj;

                    int adjIndex = index - 1;
                    if(adjIndex >= 0)
                    {
                              ListNode* prevNode = nodeAt(adjIndex);
                              listNode->mPrevNode = prevNode;
                              prevNode->mNextNode = listNode;
                    }
                    else
                    {
                              if(mNodeListStart)
                                        mNodeListStart->mPrevNode = listNode;
                              mNodeListStart =  listNode;
                    }

                    if(index < mCount)
                    {
                              ListNode* nextNode = nodeAt(index);
                              listNode->mNextNode = nextNode;
                              nextNode->mPrevNode = listNode;
                    }
                    else
                    {
                              if(mNodeListEnd)
                                        mNodeListEnd->mNextNode = listNode;
                              mNodeListEnd =  listNode;
                    }

          }
          else
          {
                    mNodeListStart = new ListNode();
                    mNodeListStart->mPtr = new T();
                    *(mNodeListStart->mPtr) = obj;

                    mNodeListEnd = mNodeListStart;                //  start and end are the same
          }

          mCount++;
          return *this;
}

template  <typename T>
void  _LinkedList<T>::removeAt(int index)
{
          if(index >=0 && index < mCount)
          {
                    ListNode* node = nodeAt(index);
                    if(node)
                    {
                              ListNode* prevNode =  node->mPrevNode;
                              ListNode* nextNode =  node->mNextNode;
                              if(prevNode)
                                        prevNode->mNextNode = nextNode;
                              if(nextNode)
                                        nextNode->mPrevNode = prevNode;

                              delete node;
                              mCount--;
                    }
          }
}

template  <typename T>
int  _LinkedList<T>::count() const
{
          return mCount;
}

template  <typename T>
const T&   _LinkedList<T>::at(int index)
{
         return *(nodeAt(index)->mPtr);
}

// private
template  <typename T>
typename _LinkedList<T>::ListNode* _LinkedList<T>::nodeAt(int index)
{
          _LinkedList<T>::ListNode* node = 0;
          if(index == 0)
                    node = mNodeListStart;
          else if(index == mCount-1)
                    node  = mNodeListEnd;
          else if(index >=0 && index < mCount-1)
          {
                    node = mNodeListStart;
                    for(int i=1; i<=index; i++)
                    {
                              node = node->mNextNode;
                    }
          }
          return node;
}

template  <typename T>
void _LinkedList<T>::clear()
{
          while(mCount>0)
                    removeAt(0);
}

template  <typename T>
typename _LinkedList<T>::Iterator _LinkedList<T>::start() const
{
          return Iterator(mNodeListStart);
}

template  <typename T>
typename _LinkedList<T>::Iterator _LinkedList<T>::end() const
{
           return Iterator(mNodeListEnd);
}

template  <typename T>
_LinkedList<T>&  _LinkedList<T>::operator << (const T&  obj)
{
          return append(obj);
}

template  <typename T>
_LinkedList<T>& _LinkedList<T>::operator= (const _LinkedList<T>& other)
{
    clear();
    int c = other.count();
    for(int i=0; i<c; i++)
    {
        append(((_LinkedList<T>)other).at(i));
    }
    return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

template  <typename T>
 _LinkedList<T>::Iterator::Iterator(ListNode* node)
 {
           mNode = node;
 }

 template  <typename T>
typename _LinkedList<T>::Iterator&  _LinkedList<T>::Iterator::next()
{
          if(mNode != 0)
                    mNode = mNode->mNextNode;
          return *this;
}

template  <typename T>
typename _LinkedList<T>::Iterator&  _LinkedList<T>::Iterator::previous()
{
          if(mNode != 0)
                    mNode = mNode->mPrevNode;
          return *this;
}

template  <typename T>
const T&  _LinkedList<T>::Iterator::value()
{
          return *(mNode->mPtr);
}

template  <typename T>
bool _LinkedList<T>::Iterator::isAtBegining()
{
          return (previous() == 0);
}

template  <typename T>
bool _LinkedList<T>::Iterator::isAtEnd()
{
          return (next() == 0);
}

template  <typename T>
typename _LinkedList<T>::Iterator& _LinkedList<T>::Iterator::operator++ (int)
 {
           return next();
 }

template  <typename T>
typename _LinkedList<T>::Iterator& _LinkedList<T>::Iterator::operator-- (int)
{
          return previous();
}


#endif // _LIST_H_INCLUDED
