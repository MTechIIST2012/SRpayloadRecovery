#ifndef VIEWSELECTORDIALOG_H
#define VIEWSELECTORDIALOG_H

#include <QDialog>
#include <QStringList>
#include "ControlLib_global.h"


namespace Ui {
    class ViewSelectorDialog;
}

class CONTROLLIBSHARED_EXPORT ViewSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewSelectorDialog(QWidget *parent = 0);
    ~ViewSelectorDialog();
    void setViewTypes(const QStringList& types);
    QStringList getViewTypes();
    QString getSelectedViewtype();
    void setViewName(QString viewname);
    QString getViewName();
private:
    Ui::ViewSelectorDialog *ui;
};

#endif // VIEWSELECTORDIALOG_H
