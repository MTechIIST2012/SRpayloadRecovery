/********************************************************************************
** Form generated from reading UI file 'missionviewer.ui'
**
** Created: Thu Feb 21 19:21:43 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONVIEWER_H
#define UI_MISSIONVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionViewer
{
public:
    QAction *actionNew_view;
    QAction *actionViews;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MissionViewer)
    {
        if (MissionViewer->objectName().isEmpty())
            MissionViewer->setObjectName(QString::fromUtf8("MissionViewer"));
        MissionViewer->resize(704, 487);
        actionNew_view = new QAction(MissionViewer);
        actionNew_view->setObjectName(QString::fromUtf8("actionNew_view"));
        actionViews = new QAction(MissionViewer);
        actionViews->setObjectName(QString::fromUtf8("actionViews"));
        centralWidget = new QWidget(MissionViewer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MissionViewer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MissionViewer);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 704, 23));
        MissionViewer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MissionViewer);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MissionViewer->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MissionViewer);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MissionViewer->setStatusBar(statusBar);

        retranslateUi(MissionViewer);

        QMetaObject::connectSlotsByName(MissionViewer);
    } // setupUi

    void retranslateUi(QMainWindow *MissionViewer)
    {
        MissionViewer->setWindowTitle(QApplication::translate("MissionViewer", "MissionViewer", 0, QApplication::UnicodeUTF8));
        actionNew_view->setText(QApplication::translate("MissionViewer", "New view", 0, QApplication::UnicodeUTF8));
        actionViews->setText(QApplication::translate("MissionViewer", "Views", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MissionViewer: public Ui_MissionViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONVIEWER_H
