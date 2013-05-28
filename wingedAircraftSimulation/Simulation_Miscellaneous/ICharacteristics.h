#ifndef ICHARACTERISTICS_H
#define ICHARACTERISTICS_H

class IChara
{
public:
    virtual ~IChara() {}
    virtual float  minInput()=0;
    virtual float  maxInput()=0;
    virtual float  minOutput()=0;
    virtual float  maxOutput()=0;
    virtual float calc_output(float input)=0;
    virtual float calc_input(float output,int count=1)=0;
};

#endif // ICHARACTERISTICS_H
