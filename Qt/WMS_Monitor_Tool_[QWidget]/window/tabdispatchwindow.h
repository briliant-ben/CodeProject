#ifndef TABDISPATCHWINDOW_H
#define TABDISPATCHWINDOW_H

#include <QWidget>

namespace Ui {
class tabdispatchwindow;
}

class tabdispatchwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabdispatchwindow(QWidget *parent = 0);
    ~tabdispatchwindow();

private slots:
    void judgeprivilegeslot();

private:
    Ui::tabdispatchwindow *ui;
};

#endif // TABDISPATCHWINDOW_H
