#ifndef TABREPORTFORMWINDOW_H
#define TABREPORTFORMWINDOW_H

#include <QWidget>

namespace Ui {
class tabreportformwindow;
}

class tabreportformwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabreportformwindow(QWidget *parent = 0);
    ~tabreportformwindow();

private slots:
    void judgeprivilegeslot();

private:
    Ui::tabreportformwindow *ui;
};

#endif // TABREPORTFORMWINDOW_H
