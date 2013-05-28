#ifndef _STRINGLIST_H
#define _STRINGLIST_H



class _StringList
{
          public:
                    _StringList(int preAlloc=5);
                    virtual ~_StringList();
                    void addString(const char* string);
                    void removeAt(int index);
                    const char* stringAt(int index) const;
                    int count() const;
                    void clear();
                    char* join(const char* joinString);
                    char* join(const char joinChar);
                    _StringList& operator= (const _StringList& other);
          private:
                    char** mStrings;
                    int mStringCount;
                    int mPreAlloc;
                    int mBalPtrs;
};

#endif // _STRINGLIST_H
