#include "personnelwindow.h"
#include "ui_personnelwindow.h"

personnelwindow::personnelwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::personnelwindow)
{
    ui->setupUi(this);
}

personnelwindow::~personnelwindow()
{
    delete ui;
}
