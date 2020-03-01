#ifndef TABSTATISTICONE_H
#define TABSTATISTICONE_H

#include <QWidget>

namespace Ui {
class tabstatisticone;
}

class tabstatisticone : public QWidget
{
    Q_OBJECT

public:
    explicit tabstatisticone(QWidget *parent = 0);
    ~tabstatisticone();

private slots:
    void judgeprivilegeslot();

private:
    Ui::tabstatisticone *ui;
};

#endif // TABSTATISTICONE_H
