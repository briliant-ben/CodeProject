#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include "dao/staffdao.h"

namespace Ui {
class registerwindow;
}

class registerwindow : public QDialog
{
    Q_OBJECT

public:
    explicit registerwindow(QWidget *parent = 0);
    ~registerwindow();

private slots:
    void on_register_confirmbutton_clicked();

    void on_register_cancelbutton_clicked();

private:
    Ui::registerwindow *ui;
    staffdao *newstaffdao;
};

#endif // REGISTERWINDOW_H
