#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
    class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QString host="127.0.0.1",
                              int port=1234,
                              QWidget *parent = 0);
    ~ConnectionDialog();
    void setHost(QString host);
    QString getHost();
    void setPort(int port);
    int getPort();
private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
