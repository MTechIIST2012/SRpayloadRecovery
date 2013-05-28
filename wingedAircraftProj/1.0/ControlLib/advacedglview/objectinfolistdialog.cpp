#include "objectinfolistdialog.h"
#include "ui_objectinfolistdialog.h"
#include <QComboBox>
#include <QVariant>
#include <QColorDialog>

#define TABLEINDEX_OBJECT 0
#define TABLEINDEX_VIEWTYPE 1
#define TABLEINDEX_COLOR 2

ObjectInfoListDialog::ObjectInfoListDialog(ObjectInfoHash objects,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectInfoListDialog)
{
    ui->setupUi(this);
    bChanged = false;
    mObjectInfoHash = objects;
    refreshUi();
}

ObjectInfoListDialog::~ObjectInfoListDialog()
{
    delete ui;
}

void ObjectInfoListDialog::setObjectInfoHash(ObjectInfoHash objects)
{
    mObjectInfoHash = objects;
}

ObjectInfoHash ObjectInfoListDialog::getObjectInfoHash()
{
    return mObjectInfoHash;
}

void ObjectInfoListDialog::recalculate()
{
    bChanged = false;
    QTableWidget* tableWdg = ui->tableWidget;
    const int rowCount = tableWdg->rowCount();
    for(int i=0; i<rowCount; i++)
    {
        QTableWidgetItem* nameItem = tableWdg->item(i,TABLEINDEX_OBJECT);
        QComboBox* viewTypeCombo = dynamic_cast<QComboBox*>(tableWdg->cellWidget(i,TABLEINDEX_VIEWTYPE));
        QTableWidgetItem* colorItem = tableWdg->item(i,TABLEINDEX_COLOR);
        if(nameItem && viewTypeCombo && colorItem)
        {
            QString objname = nameItem->data(0).toString();
            if(mObjectInfoHash.contains(objname))
            {
                ObjectViewInfo viewinfo = mObjectInfoHash.value(objname);
                ObjectViewInfo::ViewType newViewType = ObjectViewInfo::toViewType(viewTypeCombo->currentText());
                QColor color = colorItem->backgroundColor();
                if(viewinfo.getViewType() != newViewType  ||
                   viewinfo.getColor() != color)
                {
                    viewinfo.setViewType(newViewType);
                    viewinfo.setColor(color);

                    bChanged = true;
                    mObjectInfoHash.insert(objname,viewinfo);
                }
            }
        }
    }
}

bool ObjectInfoListDialog::hasChanged()
{
    return bChanged;
}

void ObjectInfoListDialog::refreshUi()
{
    clearTable();
    QTableWidget* tableWdg = ui->tableWidget;
    int row=0;
    foreach(QString objname,mObjectInfoHash.keys())
    {
        ObjectViewInfo viewinfo = mObjectInfoHash.value(objname);
        tableWdg->insertRow(row);
        QTableWidgetItem *nameItem = new QTableWidgetItem(objname);

        QComboBox* displayCombo = new QComboBox(this);
        displayCombo->addItem(STR_VIEWTYPE_LINES);
        displayCombo->addItem(STR_VIEWTYPE_SURFACE);
        displayCombo->addItem(STR_VIEWTYPE_HIDDEN);
        int index = displayCombo->findText(ObjectViewInfo::toString(viewinfo.getViewType()));
        if(index != -1)
        {
            displayCombo->setCurrentIndex(index);
        }

        QTableWidgetItem *colorItem = new QTableWidgetItem();
        colorItem->setBackgroundColor(viewinfo.getColor());

        tableWdg->setItem(row,TABLEINDEX_OBJECT, nameItem);
        tableWdg->setCellWidget(row,TABLEINDEX_VIEWTYPE,displayCombo);
        tableWdg->setItem(row,TABLEINDEX_COLOR, colorItem);

        row++;
    }
}

void ObjectInfoListDialog::refreshList()
{
    bChanged = false;
}

void ObjectInfoListDialog::clearTable()
{
    QTableWidget* tableWdg = ui->tableWidget;
    const int rowCount = tableWdg->rowCount();
    for(int i=rowCount-1; i>=0; i--)
    {
        QTableWidgetItem* nameItem = tableWdg->item(i,TABLEINDEX_OBJECT);
        QObject* viewTypeCombo = tableWdg->cellWidget(i,TABLEINDEX_VIEWTYPE);
        QTableWidgetItem* colorItem = tableWdg->item(i,TABLEINDEX_COLOR);

        if(nameItem)
            delete nameItem;
        if(viewTypeCombo)
            delete viewTypeCombo;
        if(colorItem)
            delete colorItem;
        tableWdg->removeRow(i);
    }
}

void ObjectInfoListDialog::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if(column == TABLEINDEX_COLOR)
    {
        QTableWidget* tableWdg = ui->tableWidget;
        QTableWidgetItem* colorItem = tableWdg->item(row,column);
        if(colorItem)
        {
            QColor color = QColorDialog::getColor(colorItem->backgroundColor(),this);
            colorItem->setBackgroundColor(color);
        }
    }
}
