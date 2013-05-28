#include "linearchara.h"

LinearChara::LinearChara()
{
    mMinInput = 0;
    mMaxInput = 100;
    mMinOutput = 0;
    mMaxOutput = 100;
    updateSlope();
}

LinearChara::~LinearChara()
{

}

float  LinearChara::minInput()
{
    return mMinInput;
}

float  LinearChara::maxInput()
{
    return mMaxInput;
}

float  LinearChara::minOutput()
{
    return mMinOutput;
}

float  LinearChara::maxOutput()
{
    return mMaxOutput;
}

float LinearChara::calc_output(float input)
{
    float output=0;

    if(input <= mMinInput)
        output = mMinOutput;
    else if(input >= mMaxInput)
        output = mMaxOutput;
    else
    {
        output = mMinOutput + (input-mMinInput)*mSlope;
    }

    return output;
}

float LinearChara::calc_input(float output,int /*count*/)
{
    float input=1;

    bool isRisingChara = (mMaxOutput >= mMinOutput);
    if(isRisingChara)
    {
        if(output <= mMinOutput)
            input = mMinInput;
        else if(output >= mMaxOutput)
            input = mMaxInput;
        else
        {
            input = mMinInput + (output-mMinOutput)*mRevSlope;
        }
    }
    else
    {
        if(output >= mMinOutput)
            input = mMinInput;
        else if(output <= mMaxOutput)
            input = mMaxInput;
        else
        {
            input = mMinInput + (output-mMinOutput)*mRevSlope;
        }
    }

    return input;
}

void LinearChara::setInputRange(float inputMin,float inputMax)
{
    mMinInput = inputMin;
    mMaxInput = inputMax;
}

void LinearChara::setOutputRange(float outputMin,float outputMax)
{
    mMinOutput = outputMin;
    mMaxOutput = outputMax;
}

void LinearChara::setMinInput(float input)
{
    mMinInput = input;
}

void LinearChara::setMaxInput(float input)
{
    mMaxInput = input;
}

void LinearChara::setMinOutput(float output)
{
    mMinOutput = output;
}

void LinearChara::setMaxOutput(float output)
{
    mMaxOutput = output;
}

float LinearChara::getSlope()
{
    return mSlope;
}

void LinearChara::updateSlope()
{
    mSlope = (mMaxOutput-mMinOutput)/(mMaxInput-mMinInput);
    mRevSlope = 1/mSlope;
}
