#ifndef TABMONITORAGVWINDOW_H
#define TABMONITORAGVWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QAreaSeries>
#include <QTimer>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class tabmonitoragvwindow;
}

class tabmonitoragvwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tabmonitoragvwindow(QWidget *parent = 0);

    ~tabmonitoragvwindow();

private slots:
    void judgeprivilegeslot(qint32);

    void timeoutpaintchart();

    void on_tabmonagv_linkbutton1_clicked();

    void on_tabmonagv_linkbutton2_clicked();

private:
    Ui::tabmonitoragvwindow *ui;
    QGraphicsScene scene;
    QChart Charthere;
    QValueAxis axis1;
    QValueAxis axis2;
    QValueAxis axis3;
    QLineSeries lineseies1;
    QLineSeries lineseies2;
    QLineSeries zero;
    QAreaSeries areaseries1;
    QAreaSeries areaseries2;
    qreal data_x[11];
    qreal data_y[11];
    QTimer timer;
};

#endif // TABMONITORAGVWINDOW_H
