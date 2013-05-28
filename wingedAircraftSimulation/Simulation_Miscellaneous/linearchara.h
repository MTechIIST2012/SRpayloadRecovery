#ifndef LINEARCHARA_H
#define LINEARCHARA_H

#include "ICharacteristics.h"
#include "Simulation_Miscellaneous_global.h"

class SIMULATION_MISCELLANEOUSSHARED_EXPORT LinearChara : public IChara
{
public:
    LinearChara();
    virtual ~LinearChara();
    virtual float  minInput();
    virtual float  maxInput();
    virtual float  minOutput();
    virtual float  maxOutput();
    virtual float calc_output(float input);
    virtual float calc_input(float output,int count=1);

    void setInputRange(float inputMin,float inputMax);
    void setOutputRange(float outputMin,float outputMax);
    void setMinInput(float input);
    void setMaxInput(float input);
    void setMinOutput(float output);
    void setMaxOutput(float output);
    float getSlope();
    void updateSlope();
private:
    float mMinInput;
    float mMaxInput;
    float mMinOutput;
    float mMaxOutput;
    float mSlope;
    float mRevSlope;
};

#endif // LINEARCHARA_H
