#ifndef PERSONNELWINDOW_H
#define PERSONNELWINDOW_H

#include <QMainWindow>

namespace Ui {
class personnelwindow;
}

class personnelwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit personnelwindow(QWidget *parent = 0);
    ~personnelwindow();

private:
    Ui::personnelwindow *ui;
};

#endif // PERSONNELWINDOW_H
