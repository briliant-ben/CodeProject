#ifndef TABSTORAGESTREAMWINDOW_H
#define TABSTORAGESTREAMWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <dao/storagestreamdao.h>
#include <window/streamrecordwindow.h>

namespace Ui {
class tabstoragestreamwindow;
}

class tabstoragestreamwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabstoragestreamwindow(QWidget *parent = 0);

    ~tabstoragestreamwindow();

signals:
    void judgewhichkind(int);

private slots:
    void judgeprivilegeslot(int);

    void on_tabstream_choicecombox_currentIndexChanged(int );

    void on_tabstream_choicetext_textChanged(const QString &);

    void on_tabstream_querybutton_clicked();

    QString getfilterstring(const QString &);

    void on_tabstream_inbutton_clicked();

    void on_tabstream_outbutton_clicked();

    void on_tabstream_inventorybutton_clicked();

    void on_tabstream_submitbutton_clicked();

    void on_tabstream_deletebutton_clicked();

    void on_tabstream_cancelbutton_clicked();

    void on_tabstream_table_clicked(const QModelIndex &);

    void on_tabstream_lastbutton_clicked();

    void on_tabstream_currenttext_returnPressed();

    void on_tabstream_nextbutton_clicked();

private:
    Ui::tabstoragestreamwindow *ui;
    storagestreamdao *newstreamdao;
    qint32 totalnumber;
    qint32 totalpage;
    qint32 currentpage;
    QString filterstring;
    qint32 flag;
    QMessageBox msgBox;
    streamrecordwindow newstrwin;
};

#endif // TABSTORAGESTREAMWINDOW_H
