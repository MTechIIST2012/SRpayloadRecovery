#include "nonlinearchara.h"

NonlinearChara::NonlinearChara()
{
    mPointList = 0;
    mPointListN = 0;
    mSlopeList = 0;
    mRevSlopeList = 0;
}

NonlinearChara::~NonlinearChara()
{
    clearMem();
}

float  NonlinearChara::minInput()
{
    if(mPointList)
        return mPointList[0].X;
    return -1;
}

float  NonlinearChara::maxInput()
{
    if(mPointList)
        return mPointList[mPointListN-1].X;
    return -1;
}

float  NonlinearChara::minOutput()
{
    if(mPointList)
        return mPointList[0].Y;
    return -1;
}

float  NonlinearChara::maxOutput()
{
    if(mPointList)
        return mPointList[mPointListN-1].Y;
    return -1;
}

float NonlinearChara::calc_output(float input)
{
    if(!mPointList || mPointListN<1)
        return 0;

    float output = 0;
    if(input <= mPointList[0].X)
        output = mPointList[0].Y;
    else if(input >= mPointList[mPointListN-1].X)
        output = mPointList[mPointListN-1].Y;
    else
    {
        bool bSignBefore = (input>mPointList[0].X);
        bool bSignAfter = false;

        for(int i=1; i<mPointListN; i++)
        {
            bSignAfter = (input>mPointList[i].X);
            if(bSignBefore != bSignAfter)
            {
                output = mPointList[i-1].Y + (input-mPointList[i-1].X)*mSlopeList[i-1];
                break;
            }
            bSignBefore = bSignAfter;
        }
    }
    return output;
}

float NonlinearChara::calc_input(float output,int count)
{
    if(!mPointList || mPointListN<1)
        return 0;

    float input = 0;
    bool bDoIteration = false;
    if(mPointList[0].Y <= mPointList[mPointListN-1].Y)
    {
        if(output <= mPointList[0].Y)
        {
                input = mPointList[0].X;
        }
        else if(output >= mPointList[mPointListN-1].Y)
        {
                input = mPointList[mPointListN-1].X;
        }
        else
            bDoIteration = true;
    }
    else
    {
        if(output >= mPointList[0].Y)
        {
                input = mPointList[0].X;
        }
        else if(output <= mPointList[mPointListN-1].Y)
        {
                input = mPointList[mPointListN-1].X;
        }
        else
            bDoIteration = true;
    }

    if(bDoIteration)
    {
        bool bSignBefore = (output>mPointList[0].Y);
        bool bSignAfter = false;
        for(int i=1; i<mPointListN; i++)
        {
            bSignAfter = (output>mPointList[i].Y);
            if(bSignBefore != bSignAfter)
            {
                input = mPointList[i-1].X + (output-mPointList[i-1].Y)*mRevSlopeList[i-1];
                count--;
                if(count <= 0)
                    break;
            }
            bSignBefore = bSignAfter;
        }
    }
    return input;
}

void NonlinearChara::setPointList(Point* pointList,int N)
{
    clearMem();
    mPointList = pointList;
    mPointListN = N;
    mSlopeList = new float[mPointListN-1];
    mRevSlopeList = new float[mPointListN-1];
    updateSlopeList();
}

void NonlinearChara::updateSlopeList()
{
    for(int i=0; i<mPointListN-1; i++)
    {
        mSlopeList[i] = (mPointList[i+1].Y-mPointList[i].Y)/(mPointList[i+1].X-mPointList[i].X);
        mRevSlopeList[i] = 1/mSlopeList[i];
    }
}

void NonlinearChara::clearMem()
{
    if(mSlopeList)
        delete[] mSlopeList;
    if(mPointList)
        delete[] mPointList;
    if(mRevSlopeList)
        delete[] mRevSlopeList;

    mSlopeList = 0;
    mPointList = 0;
    mRevSlopeList = 0;
}
