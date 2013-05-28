#ifndef ISCENEOPERATOR_H
#define ISCENEOPERATOR_H

#include <QString>

class ICommand;
class QGLAbstractScene;
class QGLSceneNode;

class ISceneOperator
{
public:
    virtual ~ISceneOperator() {}
    virtual int getType()=0;
    virtual bool doAction(ICommand* command,QGLAbstractScene* scene)=0;
};


#endif  // ISCENEOPERATOR_H
