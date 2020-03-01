#include "tabreportformwindow.h"
#include "ui_tabreportformwindow.h"

tabreportformwindow::tabreportformwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabreportformwindow)
{
    ui->setupUi(this);
}

tabreportformwindow::~tabreportformwindow()
{
    delete ui;
}

void tabreportformwindow::judgeprivilegeslot()
{

}
