#ifndef TABPERSONNELWINDOW_H
#define TABPERSONNELWINDOW_H

#include <QWidget>
//#include <QMouseEvent>
//#include <QWheelEvent>
#include <QMessageBox>
#include "dao/staffdao.h"
namespace Ui {
class tabpersonnelwindow;
}

class tabpersonnelwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabpersonnelwindow(QWidget *parent = 0);
    ~tabpersonnelwindow();

    QString getfilterstring(QString);

protected:
    //    void wheelEvent(QWheelEvent *);

    //    bool eventFilter(QObject *, QEvent *);

private slots:
    void judgeprivilegeslot();

    void on_tabper_inquirebutton_clicked();

    void on_tabper_choicecombo_currentIndexChanged(int index);

    void on_tabper_lastbutton_clicked();

    void on_tabper_nextbutton_clicked();

    void on_tabper_currenttext_returnPressed();

    void on_tabper_choicetext_textChanged(const QString &);

    void on_tabper_submitbutton_clicked();

    void on_tabper_cancelbutton_clicked();

    void on_tabper_deletebutton_clicked();

    void on_tabper_stafftable_clicked(const QModelIndex &);

private:
    Ui::tabpersonnelwindow *ui;
    staffdao *newstaffdao;
    qint32 totalnumber;
    qint32 totalpage;
    qint32 currentpage;
    QString filterstring;
    qint32 flag;
    QMessageBox msgBox;
};

#endif // TABPERSONNELWINDOW_H
