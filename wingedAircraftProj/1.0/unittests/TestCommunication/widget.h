#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class ICommunication_E;
class IControllerPipe;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();   
private slots:
    void on_btnClientUpdate_clicked();
    void on_btnServerUpdate_clicked();
    void on_btnClientRecvPacket_clicked();
    void on_btnClientAcceptConn_clicked();
    void on_btnServerSendPacket_clicked();
    void on_btnServerCheckConnection_clicked();
private:
    Ui::Widget *ui;
public:
    static ICommunication_E* mServerComm;
    static ICommunication_E* mClientComm;
    static IControllerPipe* mServerPipe;
    static IControllerPipe* mClientPipe;
};

#endif // WIDGET_H
