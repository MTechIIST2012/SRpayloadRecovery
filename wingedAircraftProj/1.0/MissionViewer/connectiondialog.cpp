#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QString host,
                                   int port,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    setHost(host);
    setPort(port);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::setHost(QString host)
{
    ui->edtHost->setText(host);
}

QString ConnectionDialog::getHost()
{
    return ui->edtHost->text();
}

void ConnectionDialog::setPort(int port)
{
    ui->edtPort->setText(QString::number(port));
}

int ConnectionDialog::getPort()
{
    return ui->edtPort->text().toInt();
}
