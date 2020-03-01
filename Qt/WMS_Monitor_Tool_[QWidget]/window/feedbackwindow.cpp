#include "feedbackwindow.h"
#include "ui_feedbackwindow.h"

feedbackwindow::feedbackwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::feedbackwindow)
{
    ui->setupUi(this);
}

feedbackwindow::~feedbackwindow()
{
    delete ui;
}
