#include "_CircularBuffer.h"
#include "stdlib.h"

_CircularBuffer::_CircularBuffer(unsigned int size)
{
         mStart = 0;
         mEnd = 0;
         mSize = size;
         mCount = 0;
         mDataPtr = (char*)malloc(sizeof(char) * mSize);
}

_CircularBuffer::~_CircularBuffer()
{
          free(mDataPtr);
 }

bool _CircularBuffer::isEmpty()
{
          return (mCount==0);
}

int _CircularBuffer::count()
{
          return mCount;
}

void _CircularBuffer::writeByte(char byte)
{
          mDataPtr[mEnd] = byte;
          correctOverlap();
         int rotated = 0;
         mEnd++;
         mCount++;
         adjustPos(mEnd,rotated);
}

char _CircularBuffer::readByte()
{
          char byte = 0;
          if(mCount>0)
          {
                    byte = mDataPtr[mStart];
                    mStart++;
                    mCount--;
                    int rotated = 0;
                    adjustPos(mStart,rotated);
                    correctOverlap();
          }
          return byte;
}

bool _CircularBuffer::contains(char byte)
{
          bool bContains = false;
          int preStart = mStart;
          int preCount = mCount;
          while(mCount > 0)
          {
                    if(readByte()==byte)
                    {
                              bContains = true;
                              break;
                    }
          }
          mStart = preStart;
          mCount = preCount;
          return bContains;
}

IBuffer_E&  _CircularBuffer::operator<< (char byte)
{
          writeByte(byte);
          return *this;
}

IBuffer_E&  _CircularBuffer::operator>> (char& byte)
{
          byte = readByte();
          return *this;
}

void _CircularBuffer::adjustPos(int& index,int& rotationSign)
{
          if(index >= mSize)
          {
                    rotationSign = 1;
                    index = 0;
          }
          else if(index < 0)
          {
                    rotationSign = -1;
                    index = mSize-1;
          }
          else
          {
                    rotationSign = 0;
          }

          if(mCount > mSize)
                    mCount = mSize;
          else if(mCount < 0)
                    mCount = 0;

}

void _CircularBuffer::correctOverlap()
{
          if(mStart==mEnd && mCount>0)
          {
                    mStart++;
                    int rotated = 0;
                    adjustPos(mStart,rotated);
          }
}
