#ifndef TABSTORAGELOGWINDOW_H
#define TABSTORAGELOGWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <dao/storagestreamdao.h>

namespace Ui {
class tabstoragelogwindow;
}

class tabstoragelogwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabstoragelogwindow(QWidget *parent = 0);

    ~tabstoragelogwindow();

private slots:
    void judgeprivilegeslot();

    void on_tabstolog_choicecombox_currentIndexChanged(int);

    void on_tabstolog_choicetext_textChanged(const QString &);

    void on_tabstolog_querybutton_clicked();

    QString getfilterstring(const QString &);

    void on_tabstolog_clearbutton_clicked(bool);

    void on_tabstolog_exportbutton_clicked();

    void on_tabstolog_printbutton_clicked();

    void on_tabstolog_lastbutton_clicked();

    void on_tabstolog_currenttext_returnPressed();

    void on_tabstolog_nextbutton_clicked();

    void on_tabstolog_table_clicked(const QModelIndex &);

private:
    Ui::tabstoragelogwindow *ui;
    storagestreamdao *newstreamdao;
    qint32 totalnumber;
    qint32 totalpage;
    qint32 currentpage;
    QString filterstring;
    qint32 flag;
    QMessageBox msgBox;
};

#endif // TABSTORAGELOGWINDOW_H
