#ifndef SYSTEMCONFIGUREWINDOW_H
#define SYSTEMCONFIGUREWINDOW_H

#include <QWidget>

namespace Ui {
class systemconfigurewindow;
}

class systemconfigurewindow : public QWidget
{
    Q_OBJECT

public:
    explicit systemconfigurewindow(QWidget *parent = 0);
    ~systemconfigurewindow();

private:
    Ui::systemconfigurewindow *ui;
};

#endif // SYSTEMCONFIGUREWINDOW_H
