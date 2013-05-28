#ifndef _STRING_H
#define _STRING_H

#include "_StringList.h"
#include "embedded_typedefs.h"

class _String
{
          public:
                    virtual ~_String();
                    // string manipulations
                    static int _strlen(const char* bytes);
                    static int _strToInt(const char* bytes);
                    static float _strToFloat(const char* bytes);
                    static double _strToDouble(const char* bytes);

                    static _BYTE* packInString(_BYTE* data,_BYTE* obj,int objSize);
                    static _BYTE* unpackString(_BYTE* data,_BYTE* obj,int objSize);

                    static _StringList  _strSplit(const char* bytes,const char* splitString);      // Note: memory of first string is not released
                    static _StringList  _strSplit(const char* bytes,char splitChar);      // Note: memory of first string is not released
          private:
                     _String();                                                                           // static class
                    static int charToInt(char chVal);
};

#endif // _STRING_H
