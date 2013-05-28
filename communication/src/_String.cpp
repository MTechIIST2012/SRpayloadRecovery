#include "_String.h"
#include "stdlib.h"
#include "stdio.h"

_String::_String()
{
          //ctor
}

_String::~_String()
{
          //dtor
}

int _String::_strlen(const char* bytes)
{
          int len=0;
          while(bytes[len] != '\0')
          {
                    len++;
          }
          return len;
}

int _String::_strToInt(const char* bytes)
{
          return atoi(bytes);
}



float _String::_strToFloat(const char* bytes)
{
         float val = 0;
          int decimal=0,fract=0;
          char str[10];
          const int byteLen = _strlen(bytes);
           bool bLoopEsc = false;
           bool bDecimalVals = false;
          for(int i=0; i<byteLen; i++)
          {
                    switch(bytes[i])
                    {
                              case ' ':
                                        break;
                              case '-':
                                        break;
                              case '.' :                        // negative
                                        bDecimalVals = true;
                                        bLoopEsc = true;
                                        break;
                              default:
                                        bLoopEsc = true;
                    }

                    if(bLoopEsc )
                              break;
          }

          if(bDecimalVals)
                    sscanf(bytes,".%s",str);
          else
                    sscanf(bytes,"%d.%s",&decimal,str);

          //sscanf(bytes,"%d.%s",&decimal,str);
          fract = atoi(str);
          val = decimal;

          if(fract > 0)
          {
                    int deciVal  = 10;
                    while(fract/deciVal > 0)
                    {
                              deciVal *= 10;
                    }
                    // for zero correction.
                    const int len = _strlen(str);
                    int i=0;
                    for( ; i<len; i++)
                    {
                              if(str[i] != '0')
                                        break;
                    }
                    while(i>0)
                    {
                              deciVal *= 10;
                              i--;
                    }

                    if(decimal>=0)
                              val += (float)fract/deciVal;
                    else
                              val -= (float)fract/deciVal;
          }

           // sign correction.
          if(decimal ==0)
          {
                    bool bLoopEsc = false;
                    for(int i=0; i<byteLen; i++)
                    {
                              switch(bytes[i])
                              {
                                        case ' ':
                                                  break;
                                        case '-' :                        // negative
                                                  val *=  -1;
                                                  bLoopEsc = true;
                                                  break;
                                        default:
                                                  bLoopEsc = true;
                              }

                              if(bLoopEsc )
                                        break;
                    }
          }
          return val;
}


double _String::_strToDouble(const char* bytes)
{
          double val = 0;
          int decimal=0,fract=0;
          char str[10];
          const int byteLen = _strlen(bytes);
           bool bLoopEsc = false;
           bool bDecimalVals = false;
          for(int i=0; i<byteLen; i++)
          {
                    switch(bytes[i])
                    {
                              case ' ':
                                        break;
                              case '-':
                                        break;
                              case '.' :                        // negative
                                        bDecimalVals = true;
                                        bLoopEsc = true;
                                        break;
                              default:
                                        bLoopEsc = true;
                    }

                    if(bLoopEsc )
                              break;
          }

          if(bDecimalVals)
                    sscanf(bytes,".%s",str);
          else
                    sscanf(bytes,"%d.%s",&decimal,str);

          //sscanf(bytes,"%d.%s",&decimal,str);
          fract = atoi(str);
          val = decimal;

          if(fract > 0)
          {
                    int deciVal  = 10;
                    while(fract/deciVal > 0)
                    {
                              deciVal *= 10;
                    }
                    // for zero correction.
                    const int len = _strlen(str);
                    int i=0;
                    for( ; i<len; i++)
                    {
                              if(str[i] != '0')
                                        break;
                    }
                    while(i>0)
                    {
                              deciVal *= 10;
                              i--;
                    }

                    if(decimal>=0)
                              val += (double)fract/deciVal;
                    else
                              val -= (double)fract/deciVal;
          }

           // sign correction.
          if(decimal ==0)
          {
                    bool bLoopEsc = false;
                    for(int i=0; i<byteLen; i++)
                    {
                              switch(bytes[i])
                              {
                                        case ' ':
                                                  break;
                                        case '-' :                        // negative
                                                  val *=  -1;
                                                  bLoopEsc = true;
                                                  break;
                                        default:
                                                  bLoopEsc = true;
                              }

                              if(bLoopEsc )
                                        break;
                    }
          }
          return val;
}

_BYTE* _String::packInString(_BYTE* data,_BYTE* obj,int objSize)
{
    int k = 0;
    for(int i=0; i<objSize; i++)
    {
        data[k++] = (obj[i] & 0xF0);
        data[k++] = ((obj[i] & 0x0F) << 4);
    }
    return  (data + 2*objSize);
}

_BYTE* _String::unpackString(_BYTE* data,_BYTE* obj,int objSize)
{
    int k = 0;
    for(int i=0; i<objSize; i++)
    {
        obj[i] = data[k++];
        obj[i] |= ((data[k++]) >> 4);
    }
    return  (data + 2*objSize);
}

_StringList  _String::_strSplit(const char* bytes,const char* splitString)     // Note: memory of first string is not released
{
           _StringList stringlist;
          const int len = _strlen(bytes);
          const int splitStringLen = _strlen(splitString);
          if(splitStringLen == 0)
          {
                  stringlist.addString(bytes);
          }
          else
          {
                    const int ittrMax = len-splitStringLen;
                    int prevEnd = 0;
                    int i=0;
                    bool bRepeating = false;
                    for( ; i<=ittrMax; i++)
                    {
                              bool bMatched=true;
                              for(int j=0; j<splitStringLen; j++)
                              {
                                        if(bytes[i+j] != splitString[j])
                                        {
                                                  bMatched = false;
                                                  break;
                                        }
                              }
                              if(bMatched)
                              {
                                        if(bRepeating)
                                        {
                                                  stringlist.addString("");
                                                  prevEnd += splitStringLen;
                                        }
                                        else if(i>prevEnd)
                                        {
                                                  int copyStrLen =  i - prevEnd;
                                                  char* copyString = new char[copyStrLen+1];
                                                  int k=0;
                                                  for( ;k<copyStrLen; k++)
                                                  {
                                                            copyString[k] = bytes[prevEnd++];
                                                  }
                                                  copyString[k] = '\0';
                                                  stringlist.addString(copyString);
                                                  delete[] copyString;
                                        }
                                        prevEnd += (splitStringLen-1);
                                        i = prevEnd;
                                        bRepeating = true;
                              }
                              else
                                        bRepeating = false;
                    }
                    // adding the rest
                    i = prevEnd+1;
                   char* restStr = new char[len-i+1];
                   int m=0;
                   for( ; i<len; i++,m++)
                   {
                             restStr[m] = bytes[i];
                   }
                   restStr[m] = '\0';
                   stringlist.addString(restStr);
                   delete[] restStr;
          }
          return stringlist;
}

_StringList  _String::_strSplit(const char* bytes,char splitChar)     // Note: memory of first string is not released
{
           _StringList stringlist;
          const int len = _strlen(bytes);
          int prevEnd = 0;
          int i=0;
          bool bRepeating = false;
          for( ; i<len; i++)
          {
                    if(bytes[i] == splitChar)
                    {
                              if(bRepeating)
                              {
                                        stringlist.addString("");
                                        prevEnd += 1;
                              }
                              else if(i > prevEnd)
                              {
                                         int copyStrLen =  i - prevEnd;
                                        char* copyString = new char[copyStrLen+1];
                                        int k=0;
                                        for( ;k<copyStrLen; k++)
                                        {
                                                  copyString[k] = bytes[prevEnd++];
                                        }
                                        copyString[k] = '\0';
                                        stringlist.addString(copyString);
                                        delete[] copyString;
                              }
                              //prevEnd += (1-1);
                              i = prevEnd;
                              bRepeating = true;
                    }
                    else
                              bRepeating = false;
          }
          // adding the rest
          i = prevEnd+1;
         char* restStr = new char[len-i+1];
         int m=0;
         for( ; i<len; i++,m++)
         {
                   restStr[m] = bytes[i];
         }
         restStr[m] = '\0';
         stringlist.addString(restStr);
         delete[] restStr;
          return stringlist;
}


int _String::charToInt(char chVal)
{
          int value = 0;
          switch(chVal)
          {
          case '0':
                    value = 0;
                    break;
           case '1':
                    value = 1;
                    break;
           case '2':
                    value = 2;
                    break;
           case '3':
                    value = 3;
                    break;
           case '4':
                    value = 4;
                    break;
           case '5':
                    value = 5;
                    break;
           case '6':
                    value = 6;
                    break;
           case '7':
                    value = 7;
                    break;
           case '8':
                    value = 8;
                    break;
           case '9':
                    value = 9;
                    break;
          default:
                    value = 0;
          }
          return value;
}


