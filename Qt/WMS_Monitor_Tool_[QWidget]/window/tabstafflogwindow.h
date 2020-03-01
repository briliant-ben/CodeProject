#ifndef TABSTAFFLOGWINDOW_H
#define TABSTAFFLOGWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "dao/stafflogdao.h"

namespace Ui {
class tabstafflogwindow;
}

class tabstafflogwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabstafflogwindow(QWidget *parent = 0);

    ~tabstafflogwindow();

private slots:
    void judgeprivilegeslot();

    void on_tabstalog_combox_currentIndexChanged(int);

    void on_tabstalog_choicetext_textChanged(const QString &);

    void on_tabstalog_querybutton_clicked();

    QString getfilterstring(const QString &);

    void on_tabstalog_clearbutton_clicked(bool checked);

    void on_tabstalog_exportbutton_clicked();

    void on_tabstalog_printbutton_clicked();

    void on_tabstalog_lastbutton_clicked();

    void on_tabstalog_currenttext_returnPressed();

    void on_tabstalog_nextbutton_clicked();

    //bool printFile(QString);

private:
    Ui::tabstafflogwindow *ui;
    stafflogdao *newstafflogdao;
    qint32 totalnumber;
    qint32 totalpage;
    qint32 currentpage;
    QString filterstring;
    qint32 flag;
    QMessageBox msgBox;
};

#endif // TABSTAFFLOGWINDOW_H
