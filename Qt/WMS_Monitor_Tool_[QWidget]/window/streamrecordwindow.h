#ifndef STREAMRECORDWINDOW_H
#define STREAMRECORDWINDOW_H

#include <QWidget>
#include <dao/storagestreamdao.h>

namespace Ui {
class streamrecordwindow;
}

class streamrecordwindow : public QWidget
{
    Q_OBJECT

public:
    explicit streamrecordwindow(QWidget *parent = 0);
    ~streamrecordwindow();

private slots:
    void judgement(int);

    void on_stream_locationcombox_activated(int);

    void on_stream_modelcombox_activated(int);

    void on_stream_quantitycombox_activated(int);

    void on_stream_statecombox_activated(int);

    void on_stream_chargemancombox_activated(int);

    void on_stream_confirmbutton_clicked();

    void on_stream_cancelbuttom_clicked();

    void clearcontent();

    void on_stream_kindcombox_currentIndexChanged(int);

private:
    Ui::streamrecordwindow *ui;
    storagestreamdao *newstreamdao;
};

#endif // STREAMRECORDWINDOW_H
