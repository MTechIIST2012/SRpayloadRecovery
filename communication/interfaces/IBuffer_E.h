#ifndef IBUFFER_E_H_INCLUDED
#define IBUFFER_E_H_INCLUDED

class IBuffer_E
{
public:
          virtual ~IBuffer_E() {}
          virtual bool isEmpty()=0;
          virtual int count()=0;
          virtual void writeByte(char byte)=0;
          virtual char readByte()=0;
          virtual bool contains(char byte)=0;

          virtual IBuffer_E&  operator<< (char byte)=0;
          virtual IBuffer_E&  operator>> (char& byte)=0;
};

#endif // IBUFFER_E_H_INCLUDED
