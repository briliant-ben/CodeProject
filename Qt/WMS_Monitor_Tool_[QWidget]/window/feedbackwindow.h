#ifndef FEEDBACKWINDOW_H
#define FEEDBACKWINDOW_H

#include <QWidget>

namespace Ui {
class feedbackwindow;
}

class feedbackwindow : public QWidget
{
    Q_OBJECT

public:
    explicit feedbackwindow(QWidget *parent = 0);
    ~feedbackwindow();

private:
    Ui::feedbackwindow *ui;
};

#endif // FEEDBACKWINDOW_H
