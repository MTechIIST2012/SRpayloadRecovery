#include "scenemanager.h"
#include "ICommand.h"
#include "ICommandData.h"
#include "ISceneOperator.h"
#include "logger.h"
#include <QDebug>

SceneManager::SceneManager(QObject *parent) :
    AbstractManager(parent)
{
}

SceneManager::~SceneManager()
{
   // qDeleteAll(mHshScenes.values());
    qDeleteAll(mHshOperators.values());
}

void SceneManager::addScene(QString sceneName,QGLAbstractScene* scene)
{
    if(!scene)
        return;
    QGLAbstractScene* prevScene = mHshScenes.value(sceneName,0);
    if(prevScene)
        delete prevScene;
    mHshScenes.insert(sceneName,scene);
}

QGLAbstractScene* SceneManager::getScene(QString sceneName)
{
    QGLAbstractScene* scene = mHshScenes.value(sceneName,0);
    return scene;
}

void SceneManager::removeScene(QString sceneName)
{
    QGLAbstractScene* prevScene = mHshScenes.value(sceneName,0);
    if(prevScene)
        delete prevScene;
    mHshScenes.remove(sceneName);
}

QList<QGLAbstractScene*> SceneManager::getScenes()
{
    return mHshScenes.values();
}

void SceneManager::registerOperator(int operId,ISceneOperator* oper)
{
    if(!oper)
        return;
    ISceneOperator* prevOper = mHshOperators.value(operId,0);
    if(prevOper)
        delete prevOper;
    mHshOperators.insert(operId,oper);
}

void SceneManager::unregisterOperator(int operId)
{
    ISceneOperator* prevOper = mHshOperators.value(operId,0);
    if(prevOper)
        delete prevOper;
    mHshOperators.remove(operId);
}

ISceneOperator* SceneManager::getOperator(int operId)
{
    ISceneOperator* oper = mHshOperators.value(operId,0);
    return oper;
}

bool SceneManager::hasOperator(int operId)
{
    return bool(mHshOperators.value(operId,0));
}

bool SceneManager::doAction(ICommand* command)        // severity based queue needs to be implimented
{
    if(!command)
        return false;

    bool bSucces = false;
    int commandType = command->getType();
    ISceneOperator* oper = getOperator(commandType);
    if(oper)
    {
        foreach(QGLAbstractScene* scene,mHshScenes.values())
        {
            if(!oper->doAction(command,scene))
            {
                bSucces = false;
            }
        }
    }
    else
    {
        QString err = QString("SceneManager,operator for '%0' not found").arg(commandType);
        Logger::curLog(err,Logger::ERROR);
    }
    return bSucces;
}
