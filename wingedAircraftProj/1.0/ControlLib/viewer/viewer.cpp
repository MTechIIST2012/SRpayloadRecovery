#include "viewer.h"
#include "ui_viewer.h"
#include "viewselectordialog.h"
#include <QMenu>
#include <QHash>
#include <QDockWidget>
#include <QMdiSubWindow>

#define DEFAULT_LOG_FILENAME "logs/viewerlog.log"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    mViewCount = 0;

    mLogger = new Logger(DEFAULT_LOG_FILENAME);
    ui->dockBrowser->hide();

    connect(ui->actionAbout_qt,
            SIGNAL(triggered()),
            qApp,
            SLOT(aboutQt()));

    connect(ui->actionAbout,
            SIGNAL(triggered()),
            this,
            SIGNAL(aboutDialogReqest()));
}

Viewer::~Viewer()
{
    delete ui;
    delete mLogger;
}

Logger* Viewer::getLogger()
{
    return mLogger;
}

bool Viewer::log(QString str,Logger::LogType logtype,int tracelevel)
{
    message(str,logtype);
    return mLogger->Log(str,logtype,tracelevel);
}

void Viewer::message(QString msg,Logger::LogType logtype)
{
    switch(logtype)
    {
    case Logger::ERROR:
        {
            QTextCursor cursor = ui->edtErros->textCursor();
            cursor.insertText("\n" + msg);
            ui->edtErros->setTextCursor(cursor);
        }
        break;
    case Logger::WARNING:
        {
            QTextCursor cursor = ui->edtWarnings->textCursor();
            cursor.insertText("\n" + msg);
            ui->edtWarnings->setTextCursor(cursor);
        }
        break;
    case Logger::INFO:
        {
            QTextCursor cursor = ui->edtMessages->textCursor();
            cursor.insertText("\n" + msg);
            ui->edtMessages->setTextCursor(cursor);
        }
        break;
    case Logger::DEBUG:
        {
            QTextCursor cursor = ui->edtDebug->textCursor();
            cursor.insertText("\n" + msg);
            ui->edtDebug->setTextCursor(cursor);
        }
        break;
    }
}

void Viewer::addMdiSubWindow(QString windowname,QMdiSubWindow* window)
{
    if(!window)
        return;

    removeMdiSubWindow(windowname);
    mHashMdiWindow.insert(windowname,window);
    ui->mdiArea->addSubWindow(window);
    QAction* showAction = ui->menuViews->addAction(windowname);
    showAction->setCheckable(true);
    showAction->setChecked(true);
    connect(showAction,
            SIGNAL(toggled(bool)),
            window,
            SLOT(setVisible(bool)));
    mHashShowWins.insert(windowname,showAction);
}

void Viewer::removeMdiSubWindow(QString windowname)
{
    QMdiSubWindow* curWindow = mHashMdiWindow.value(windowname,0);
    if(curWindow)
    {
        QAction* showAction = mHashShowWins.value(windowname);
        mHashShowWins.remove(windowname);
        if(showAction)
            delete showAction;
        ui->mdiArea->removeSubWindow(curWindow);
        mHashMdiWindow.remove(windowname);
        delete curWindow;
    }
}

QMdiSubWindow* Viewer::getMdiSubWindow(QString windowname)
{
    return mHashMdiWindow.value(windowname,0);
}

void Viewer::setViewTypes(QStringList viewtypes)
{
    mViewTypes = viewtypes;
}

QStringList Viewer::getViewTypes()
{
    return mViewTypes;
}

void Viewer::on_actionNew_view_triggered()
{
    ViewSelectorDialog dlg;
    dlg.setViewTypes(mViewTypes);
    dlg.setViewName(tr("View%0").arg(mViewCount++));
    if(dlg.exec())
    {
        QString viewtype = dlg.getSelectedViewtype();
        if(!viewtype.isEmpty())
        {
            QString windowName = dlg.getViewName();
            QMdiSubWindow* window = createView(viewtype,windowName);
            if(window)
            {
                addMdiSubWindow(windowName,window);
                window->show();
            }
        }
    }
}

void Viewer::updateWindowsList()
{
    QMenu* windowmenu = ui->menuWindowsList;
    windowmenu->clear();
    foreach(QObject* obj,children())
    {
        QDockWidget* dockWidg = dynamic_cast<QDockWidget*>(obj);
        if(dockWidg)
        {
            QAction* showAction = windowmenu->addAction(dockWidg->windowTitle());
            showAction->setCheckable(true);
            showAction->setChecked(dockWidg->isVisible());
            connect(showAction,
                    SIGNAL(toggled(bool)),
                    dockWidg,
                    SLOT(setVisible(bool)));
        }
    }
}

void Viewer::updateViewList()
{
    foreach(QString viewname,mHashMdiWindow.keys())
    {
        QMdiSubWindow* window = mHashMdiWindow.value(viewname);
        QAction* showAction = mHashShowWins.value(viewname);
        if(window && showAction)
        {
            showAction->setChecked(window->isVisible());
        }
    }
}
