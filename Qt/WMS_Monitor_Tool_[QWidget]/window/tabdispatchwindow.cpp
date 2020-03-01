#include "tabdispatchwindow.h"
#include "ui_tabdispatchwindow.h"

tabdispatchwindow::tabdispatchwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabdispatchwindow)
{
    ui->setupUi(this);
}

tabdispatchwindow::~tabdispatchwindow()
{
    delete ui;
}

void tabdispatchwindow::judgeprivilegeslot(){
//    if(staff::staticrole == 1){
//        ui->tabper_deletebutton->setEnabled(true);
//        ui->tabper_submitbutton->setEnabled(true);
//        ui->tabper_cancelbutton->setEnabled(true);
//        ui->tabper_stafftable->setEditTriggers(QAbstractItemView::DoubleClicked
//                                               | QAbstractItemView::EditKeyPressed
//                                               | QAbstractItemView::AnyKeyPressed);
//    }
}

