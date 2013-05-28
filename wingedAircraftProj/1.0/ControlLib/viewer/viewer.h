#ifndef VIEWER_H
#define VIEWER_H

#include "ControlLib_global.h"
#include "logger.h"
#include <QMainWindow>
#include <QHash>
#include <QStringList>

namespace Ui {
    class Viewer;
}

class QMdiSubWindow;

class CONTROLLIBSHARED_EXPORT Viewer : public QMainWindow
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
    virtual ~Viewer();
    Logger* getLogger();
    bool log(QString str,Logger::LogType logtype=Logger::INFO,int tracelevel=-1);
    void message(QString msg,Logger::LogType logtype=Logger::INFO);
    void addMdiSubWindow(QString windowname,QMdiSubWindow* window);
    void removeMdiSubWindow(QString windowname);
    QMdiSubWindow* getMdiSubWindow(QString windowname);
    void setViewTypes(QStringList viewtypes);
    QStringList getViewTypes();
signals:
    void aboutDialogReqest();
protected:
    virtual QMdiSubWindow* createView(QString viewtype,QString windowname)=0;
private slots:
    void on_actionNew_view_triggered();
    void updateWindowsList();
    void updateViewList();
private:
    Ui::Viewer *ui;
    Logger* mLogger;
    QHash<QString,QMdiSubWindow*> mHashMdiWindow;
    QHash<QString,QAction*> mHashShowWins;
    int mViewCount;
    QStringList mViewTypes;
};

#endif // VIEWER_H
