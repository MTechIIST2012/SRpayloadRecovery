#include "_StringList.h"
#include "string.h"

_StringList::_StringList(int preAlloc)
{
          mPreAlloc =  preAlloc;
          mStrings = 0;
          mBalPtrs = 0;
          mStringCount = 0;
}

_StringList::~_StringList()
{
          clear();
}

 void _StringList::addString(const char* string)
 {
          if(mStrings==0)
          {
                    mStrings = new char*[mPreAlloc];
                    mBalPtrs = mPreAlloc;
          }
          else if(mBalPtrs==0)
          {
                    char** newPtrlist = new char*[mStringCount+mPreAlloc];
                    mBalPtrs = mPreAlloc;

                    for(int i=0; i<mStringCount; i++)
                              newPtrlist[i] = mStrings[i];

                    //deleting previous ptr list
                    delete[] mStrings;
                    mStrings = newPtrlist;
          }

          char* strCopy = new char[strlen(string)];
          strcpy(strCopy,string);
          mStrings[mStringCount] = strCopy;
          mStringCount++;
          mBalPtrs--;
 }

void _StringList::removeAt(int index)
{
          char* strPtr = mStrings[index];
          delete[] strPtr;
          for(int i=index+1; i<mStringCount; i++)
          {
                    mStrings[i-1] =  mStrings[i];
          }
          mStringCount--;
          mBalPtrs++;
}

const char* _StringList::stringAt(int index) const
{
          return mStrings[index];
}

int _StringList::count() const
{
          return mStringCount;
}

void _StringList::clear()
{
          if(mStrings)
          {
                     for(int i=0; i<mStringCount; i++)
                    {
                              delete[]  mStrings[i];
                    }
                    delete[] mStrings;
                    mStrings = 0 ;
          }
          mStringCount = 0;
          mBalPtrs = 0;
}

char* _StringList::join(const char* joinString)
{
          char* str = 0;
          // finding string length
          int len=0;
          const int joinStringLen = strlen(joinString);
          for(int i=0; i<mStringCount; i++)
          {
                    len += strlen(mStrings[i])  +  joinStringLen;
          }
          len -= joinStringLen;
          len++;

          if(len >0)
          {
                    str = new char[len];
                    int str_index = 0;
                    for(int i=0; i<mStringCount; i++)
                    {
                              char* partStr = mStrings[i];
                              int j=0;
                              for(j=0; j<strlen(partStr) ;  j++)
                              {
                                        str[str_index++] = partStr[j];
                              }

                              if(i != mStringCount-1)
                              {
                                       for(j=0; j<joinStringLen; j++)
                                        {
                                                  str[str_index++] = joinString[j];
                                        }
                              }
                    }
                    str[len] = '\0';
          }
          return str;
}

char* _StringList::join(const char joinChar)
{
          char* str = 0;
          // finding string length
          int len=0;
          for(int i=0; i<mStringCount; i++)
          {
                    len += strlen(mStrings[i])  +  1;
          }

          if(len >0)
          {
                    str = new char[len];
                    int str_index = 0;
                    for(int i=0; i<mStringCount; i++)
                    {
                              char* partStr = mStrings[i];
                              int j=0;
                              for(j=0; j<strlen(partStr) ;  j++)
                              {
                                        str[str_index++] = partStr[j];
                              }

                              if(i != mStringCount-1)
                              {
                                      str[str_index++] = joinChar;
                              }
                    }
                    str[len] = '\0';
          }
          return str;
}

_StringList&  _StringList::operator= (const _StringList& other)
{
          clear();
          int c = other.count();
          if(c>0)
          {
                    for(int i=0; i<c; i++)
                    {
                              addString(other.stringAt(i));
                    }
          }
          return *this;
}

