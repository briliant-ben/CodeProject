#pragma execution_character_set("utf-8")
#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>

registerwindow::registerwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerwindow),
    newstaffdao(new staffdao())
{
    ui->setupUi(this);
    QRegExp regExp1("^[A-Z][A-Z].*$");
    ui->register_numtext->setValidator(new QRegExpValidator(regExp1,this));

//    ui->register_pwdtext->setEchoMode(QLineEdit::Password);
//    ui->register_pwdagaintext->setEchoMode(QLineEdit::Password);
//    ui->register_phonetext->setMaxLength(15);

    QRegExp regExp2("^[0-9]*[-]*[0-9]*$");
    ui->register_phonetext->setValidator(new QRegExpValidator(regExp2,this));

}

registerwindow::~registerwindow()
{
    delete ui;
}

void registerwindow::on_register_confirmbutton_clicked()
{
    if (ui->register_pwdtext->text() == ui->register_pwdagaintext->text())
    {
        if((ui->register_numtext->text() != "")
                &&(ui->register_pwdtext->text() != "")
                &&(ui->register_pwdagaintext->text() != "")
                &&(ui->register_nametext->text() != "")
                &&(ui->register_phonetext->text() != "")
                &&(ui->register_authenticationtext->text() != ""))
        {
            if(newstaffdao->staffregister(ui->register_numtext->text(), ui->register_pwdtext->text(),
                                          ui->register_nametext->text(), ui->register_unitcombobox->currentText(),
                                          ui->register_poscombobox->currentText(),ui->register_phonetext->text(),
                                          ui->register_authenticationtext->text()))
            {
                QMessageBox::information(this, "Information", QString("<font>信息注册成功！<br/>请等待管理员确认！</font>"),
                                         QMessageBox::Ok);
            }
            else
            {
                QMessageBox::warning(this, "Warning!",QString("<font>信息注册失败！<br/>请确认您的信息！</font>"), QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning!",QString("<font>输入信息不完全！<br/>请确认！</font>"), QMessageBox::Ok);
            ui->register_numtext->setFocus();
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!",QString("<font>密码输入不一致！<br/>请确认！</font>"), QMessageBox::Ok);
        ui->register_pwdtext->setText("");
        ui->register_pwdtext->setFocus();
        ui->register_pwdagaintext->setText("");
    }
}

void registerwindow::on_register_cancelbutton_clicked()
{
    ui->register_numtext->setText("");
    ui->register_pwdtext->setText("");
    ui->register_pwdagaintext->setText("");
    ui->register_nametext->setText("");
    ui->register_unitcombobox->setCurrentIndex(0);
    ui->register_poscombobox->setCurrentIndex(0);
    ui->register_phonetext->setText("");
    ui->register_authenticationtext->setText("");
    ui->register_numtext->setFocus();
}
