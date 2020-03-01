#pragma execution_character_set("utf-8")
#include "loginwindow.h"
#include "ui_loginwindow.h"
//#include "entity/staff.h"

loginwindow::loginwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginwindow),
    animation(new QPropertyAnimation()),
    newstaffdao(new staffdao())
{
    ui->setupUi(this);

    QRegExp regExp("^[A-Z][A-Z].*$");//[1-9][A-Za-z]{[0-9],[a-z]}
    ui->login_numbertext->setValidator(new QRegExpValidator(regExp,this));

//    ui->login_numbertext->setMaxLength(10);
//    ui->login_passwordtext->setEchoMode(QLineEdit::Password);

    regwindow.setFixedSize(300,360);
    regwindow.setWindowTitle("Register Account");
    regwindow.setWindowFlags(Qt::WindowCloseButtonHint);

    animation->setPropertyName("windowOpacity");
    animation->setDuration(222);
    animation->setStartValue(0);
    animation->setEndValue(1);

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    //    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(QString("<font>抱歉！<br/>现在没有任何帮助</font>"));
    msgBox.setButtonText(QMessageBox::Ok,"确定");

    connect(this, SIGNAL(senddata(qint32,QString,qint32)), &mainWindow, SLOT(receiveData(qint32,QString,qint32)));
}

loginwindow::~loginwindow()
{
    delete ui;
    delete animation;
    delete newstaffdao;
}

void loginwindow::on_login_numbertext_textChanged(const QString &)
{
    if(ui->login_numbertext->hasAcceptableInput() && (ui->login_passwordtext->text() != "")){
        ui->login_loginbutton->setEnabled(true);
    }
    else{
        ui->login_loginbutton->setEnabled(false);
    }
}

void loginwindow::on_login_numbertext_returnPressed()
{
    ui->login_passwordtext->setFocus();
}

void loginwindow::on_login_passwordtext_textChanged(const QString &)
{
    if(ui->login_numbertext->hasAcceptableInput() && (ui->login_passwordtext->text() != "")){
        ui->login_loginbutton->setEnabled(true);
    }
    else{
        ui->login_loginbutton->setEnabled(false);
    }
}

void loginwindow::on_login_registerbutton_clicked()
{
    animation->setTargetObject(&regwindow);
    animation->start();
    regwindow.exec();
    this->show();
}

void loginwindow::on_login_helpbutton_clicked()
{
    msgBox.setWindowTitle("Help");
    animation->setTargetObject(&msgBox);
    animation->start();
    msgBox.exec();
}

void loginwindow::on_login_loginbutton_clicked()
{
    if(newstaffdao->login(ui->login_numbertext->text(),ui->login_passwordtext->text())){
        msgBox.setWindowTitle("Login Information");
        msgBox.setText(QString("<font>登录成功！欢迎使用！<br/>------</font>")
                       + newstaffdao->getstaff().getname()
                       + "------");
        animation->setTargetObject(&msgBox);
        animation->start();
        msgBox.exec();

        animation->stop();

        emit senddata(newstaffdao->getstaff().getid(),
                      newstaffdao->getstaff().getname(),newstaffdao->getstaff().getrole());
        this->close();
        mainWindow.setWindowTitle("导航控制信息系统");
        mainWindow.showMaximized();
        animation->setTargetObject(&mainWindow);
        animation->start();
    }
    else{
        msgBox.setWindowTitle("Login Information");
        msgBox.setText(QString("<font>登录失败！请确认您的登录<br/>信息后再次登录！</font>"));
        animation->setTargetObject(&msgBox);
        animation->start();
        msgBox.exec();

        ui->login_numbertext->setText("");
        ui->login_passwordtext->setText("");
        ui->login_numbertext->setFocus();
    }
}

void loginwindow::on_login_exitbutton_clicked()
{
    qApp->exit();
}
