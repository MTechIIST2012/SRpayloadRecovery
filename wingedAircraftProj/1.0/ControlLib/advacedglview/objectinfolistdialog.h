#ifndef OBJECTINFOLISTDIALOG_H
#define OBJECTINFOLISTDIALOG_H

#include "objectviewinfo.h"
#include "ControlLib_global.h"
#include <QDialog>

namespace Ui {
    class ObjectInfoListDialog;
}

class CONTROLLIBSHARED_EXPORT ObjectInfoListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectInfoListDialog(ObjectInfoHash objects,QWidget *parent = 0);
    ~ObjectInfoListDialog();

    void setObjectInfoHash(ObjectInfoHash objects);
    ObjectInfoHash getObjectInfoHash();
    void recalculate();
    bool hasChanged();
private:
    void refreshUi();
    void refreshList();
    void clearTable();

    Ui::ObjectInfoListDialog *ui;
    ObjectInfoHash mObjectInfoHash;
    bool bChanged;

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
};

#endif // OBJECTINFOLISTDIALOG_H
