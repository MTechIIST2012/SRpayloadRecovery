#include "viewselectordialog.h"
#include "ui_viewselectordialog.h"

ViewSelectorDialog::ViewSelectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewSelectorDialog)
{
    ui->setupUi(this);
}

ViewSelectorDialog::~ViewSelectorDialog()
{
    delete ui;
}

void ViewSelectorDialog::setViewTypes(const QStringList& types)
{
    ui->lstViewTypes->clear();
    ui->lstViewTypes->addItems(types);
}

QStringList ViewSelectorDialog::getViewTypes()
{
    QStringList viewtypes;
    const int c = ui->lstViewTypes->count();
    for(int i=0; i<c; i++)
    {
        viewtypes.append( ui->lstViewTypes->item(i)->text() );
    }
    return viewtypes;
}

QString ViewSelectorDialog::getSelectedViewtype()
{
    QString type = ui->lstViewTypes->currentItem()->text();
    return type;
}

void ViewSelectorDialog::setViewName(QString viewname)
{
    ui->edtViewName->setText(viewname);
}

QString ViewSelectorDialog::getViewName()
{
    return ui->edtViewName->text();
}
