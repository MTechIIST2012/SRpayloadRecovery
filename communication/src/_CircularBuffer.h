#ifndef _CIRCULARBUFFER_H
#define _CIRCULARBUFFER_H

#include "IBuffer_E.h"

class _CircularBuffer : public IBuffer_E
{
public:
          _CircularBuffer(unsigned int size);
          virtual ~_CircularBuffer();
          virtual bool isEmpty();
          virtual int count();
          virtual void writeByte(char byte);
          virtual char readByte();
          virtual bool contains(char byte);

          virtual IBuffer_E&  operator<< (char byte);
          virtual IBuffer_E&  operator>> (char& byte);
private:
          inline void adjustPos(int& index,int& rotationSign);
          inline void correctOverlap();

          int mStart;
          int mEnd;
          unsigned int mSize;
          int mCount;
          char* mDataPtr;
};

#endif // _CIRCULARBUFFER_H
