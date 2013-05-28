#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->lblAppName->setText(qApp->applicationName());
    ui->lblVersion->setText(qApp->applicationVersion());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
