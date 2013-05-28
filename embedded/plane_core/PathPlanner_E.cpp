#include "PathPlanner_E.h"

PathPlanner_E::PathPlanner_E()
{
}

PathPlanner_E::~PathPlanner_E()
{
}

void PathPlanner_E::setPath( const  _LinkedList<_GPSPosition>&  poslist)
{
          mPathPosList = poslist;
}

const  _LinkedList<_GPSPosition>&  PathPlanner_E::getPath()
{
          return mPathPosList;
}

_GPSPosition PathPlanner_E::calcReqPos(double puTime)
{
          return _GPSPosition();
}
