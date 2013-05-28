#ifndef IPATHPLANNER_E_H_INCLUDED
#define IPATHPLANNER_E_H_INCLUDED

#include "_LinkedList.h"
#include "embedded_typedefs.h"

class IPathPlanner_E
{
public:
          virtual ~IPathPlanner_E() {}
          virtual void setPath( const  _LinkedList<_GPSPosition>&  poslist)=0;
          virtual const  _LinkedList<_GPSPosition>&  getPath()=0;
          virtual _GPSPosition calcReqPos(double puTime)=0;
};

#endif // IPATHPLANNER_E_H_INCLUDED
