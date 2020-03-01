#ifndef TABSTORAGESTOCKWINDOW_H
#define TABSTORAGESTOCKWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <dao/couplingdao.h>
#include <dao/locationdao.h>

namespace Ui {
class tabstoragestockwindow;
}

class tabstoragestockwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabstoragestockwindow(QWidget *parent = 0);

    ~tabstoragestockwindow();

private slots:
    void judgeprivilegeslot();

    void on_tabstock_tablecombox_currentIndexChanged(int);

    void on_tabstock_choicecombox_currentIndexChanged(int);

    void on_tabstock_querybutton_clicked();

    QString getfilterstring(const QString &);

    void on_tabstock_submitbutton_clicked();

    void on_tabstock_deletebutton_clicked();

    void on_tabstock_cancelbutton_clicked();

    void on_tabstock_lastbutton_clicked();

    void on_tabstock_currenttext_returnPressed();

    void on_tabstock_nextbutton_clicked();

    void on_tabstock_table_clicked(const QModelIndex &);

private:
    Ui::tabstoragestockwindow *ui;
    couplingdao *newcouplingdao;
    locationdao *newlocationdao;
    qint32 totalnumber;
    qint32 totalpage;
    qint32 currentpage;
    QString filterstring;
    qint32 flag;
    QMessageBox msgBox;
};

#endif // TABSTORAGESTOCKWINDOW_H
