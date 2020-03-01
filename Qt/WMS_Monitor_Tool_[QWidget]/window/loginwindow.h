#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QpropertyAnimation>
#include <QMessageBox>
#include <QMouseEvent>
#include "registerwindow.h"
#include "mainwindow.h"
#include "dao/staffdao.h"

namespace Ui {
class loginwindow;
}

class loginwindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = 0);
    ~loginwindow();

signals:
    void senddata(qint32,QString,qint32);

private slots:
    void on_login_numbertext_returnPressed();

    void on_login_numbertext_textChanged(const QString &);

    void on_login_passwordtext_textChanged(const QString &);

    void on_login_registerbutton_clicked();

    void on_login_helpbutton_clicked();

    void on_login_loginbutton_clicked();

    void on_login_exitbutton_clicked();

private:
    Ui::loginwindow *ui;
    registerwindow regwindow;
    mainwindow mainWindow;
    QPropertyAnimation *animation;
    QMessageBox msgBox;
    staffdao *newstaffdao;
    //    QPoint last;
};

#endif // LOGINWINDOW_H
