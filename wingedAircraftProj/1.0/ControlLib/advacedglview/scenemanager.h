#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <QHash>
#include "abstractmanager.h"
#include "ControlLib_global.h"

class QGLAbstractScene;
class ICommand;
class ICommandData;
class ISceneOperator;

class CONTROLLIBSHARED_EXPORT SceneManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = 0);
    ~SceneManager();
    void addScene(QString sceneName,QGLAbstractScene* scene);
    QGLAbstractScene* getScene(QString sceneName);
    void removeScene(QString sceneName);
    QList<QGLAbstractScene*> getScenes();
    void registerOperator(int operId,ISceneOperator* oper);
    void unregisterOperator(int operId);
    ISceneOperator* getOperator(int operId);
    bool hasOperator(int operId);
protected:
    bool doAction(ICommand* command);
private:
    QHash<QString,QGLAbstractScene*> mHshScenes;
    QHash<int,ISceneOperator*> mHshOperators;
};

#endif // SCENEMANAGER_H
