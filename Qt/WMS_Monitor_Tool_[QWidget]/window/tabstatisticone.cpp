#include "tabstatisticone.h"
#include "ui_tabstatisticone.h"

tabstatisticone::tabstatisticone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabstatisticone)
{
    ui->setupUi(this);
}

tabstatisticone::~tabstatisticone()
{
    delete ui;
}

void tabstatisticone::judgeprivilegeslot()
{

}
