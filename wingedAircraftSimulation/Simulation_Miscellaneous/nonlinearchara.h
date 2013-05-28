#ifndef NONLINEARCHARA_H
#define NONLINEARCHARA_H

#include "ICharacteristics.h"
#include "Simulation_Miscellaneous_global.h"

class SIMULATION_MISCELLANEOUSSHARED_EXPORT NonlinearChara : public IChara
{
public:
    struct Point
    {
        float X;
        float Y;
    };

    NonlinearChara();
    virtual ~NonlinearChara();
    virtual float  minInput();
    virtual float  maxInput();
    virtual float  minOutput();
    virtual float  maxOutput();
    virtual float calc_output(float input);
    virtual float calc_input(float output,int count=1);

    void setPointList(Point* pointList,int N);
private:
    void updateSlopeList();
    void clearMem();

    Point* mPointList;
    float* mSlopeList;
    float* mRevSlopeList;
    int mPointListN;
};

#endif // NONLINEARCHARA_H
