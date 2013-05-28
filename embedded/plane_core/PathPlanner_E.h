#ifndef PATHPLANNER_E_H
#define PATHPLANNER_E_H

#include "IPathPlanner_E.h"

class PathPlanner_E : public IPathPlanner_E
{
public:
          PathPlanner_E();
          virtual ~PathPlanner_E();
          virtual void setPath( const  _LinkedList<_GPSPosition>&  poslist);
          virtual const  _LinkedList<_GPSPosition>&  getPath();
          virtual _GPSPosition calcReqPos(double puTime);
private:
          _LinkedList<_GPSPosition> mPathPosList;
};

#endif // PATHPLANNER_E_H
