#include "systemconfigurewindow.h"
#include "ui_systemconfigurewindow.h"

systemconfigurewindow::systemconfigurewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::systemconfigurewindow)
{
    ui->setupUi(this);
}

systemconfigurewindow::~systemconfigurewindow()
{
    delete ui;
}
