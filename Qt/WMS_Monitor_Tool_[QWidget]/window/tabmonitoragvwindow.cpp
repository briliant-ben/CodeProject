#pragma execution_character_set("utf-8")
#include "tabmonitoragvwindow.h"
#include "ui_tabmonitoragvwindow.h"
#include <QMessageBox>
#include <QtMath>
#include <QValueAxis>

tabmonitoragvwindow::tabmonitoragvwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabmonitoragvwindow)
{
    ui->setupUi(this);

    //ui->tabmonagv_graphicview1->setWindowTitle("AGV#001 实时监控");//好像没什么用
    //ui->tabmonagv_graphicview1->setRenderHint(QPainter::Antialiasing);//反锯齿，但会增加CPU
    ui->tabmonagv_graphicview1->show();

    scene.setBackgroundBrush(QBrush(QColor(240, 240, 240)));

    Charthere.setDropShadowEnabled(true);
    Charthere.legend()->hide();  // 隐藏图例
    Charthere.createDefaultAxes();  // 基于已添加到图表的 series 来创建轴
    Charthere.setTitle("AGV 实时监控");
    Charthere.setTitleBrush(QBrush(Qt::Dense5Pattern));
    Charthere.setTitleFont(QFont("Helvetica"));
    Charthere.setGeometry(0, 0, 480, 250);
    Charthere.setAnimationDuration(500);
    //Charthere.setBackgroundVisible(false);
    //Charthere.setAnimationOptions(QChart::SeriesAnimations);//QChart::AllAnimations//QChart::GridAxisAnimations
    //Charthere.setTheme(QChart::ChartThemeDark);

    for(qint8 i=0; i<21;i++){//初始数据
        lineseies1.append(i-20,1);
        lineseies2.append(i-20,1);
        zero.append(i-20,0);
    }
    lineseies1.setName("速度");
    lineseies2.setName("加速度");
    areaseries2.setColor(QColor(0, 0, 255, 255));
    areaseries1.setLowerSeries(&zero);
    areaseries1.setUpperSeries(&lineseies1);
    areaseries2.setColor(QColor(255, 0, 0,180));
    areaseries2.setBorderColor(QColor(255, 0, 0,120));
    areaseries2.setLowerSeries(&zero);
    areaseries2.setUpperSeries(&lineseies2);

    Charthere.addSeries(&areaseries1);  // 将 series1 添加至图表中
    Charthere.addSeries(&areaseries2);  // 将 series2 添加至图表中
    Charthere.createDefaultAxes();  // 基于已添加到图表的 series 来创建轴
    Charthere.axisX()->setRange(-20,0);
    Charthere.axisY()->setRange(0,15);

    ui->tabmonagv_graphicview1->setScene(&scene);
    ui->tabmonagv_graphicview2->setScene(&scene);
    scene.addItem(&Charthere);

    timer.start(500);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeoutpaintchart()));
}

tabmonitoragvwindow::~tabmonitoragvwindow()
{
    delete ui;
}

void tabmonitoragvwindow::judgeprivilegeslot(qint32 page)
{
    ui->tabmonagv_stackwidget->setCurrentIndex(page);
}

void tabmonitoragvwindow::timeoutpaintchart()
{
    //receive real-time data and refresh data in lineseies
    //    qreal newdata = getspeeddata();
    qreal newspeeddata = qrand() % 5 + 1.5;
    qint8 i=0;
    for(i=0; i<20;i++){
        lineseies1.replace(i,lineseies1.at(i).x(),lineseies1.at(i+1).y());
    }
    lineseies1.replace(i,lineseies1.at(i).x(),newspeeddata);

    //    qreal newdata = getacceleratedata();

    qreal newacceleratedata = qrand() % 5 + 0.8;
    qint8 j=0;
    for(j=0; j<20;j++){
        lineseies2.replace(j,lineseies2.at(j).x(),lineseies2.at(j+1).y());
    }
    lineseies2.replace(j,lineseies2.at(j).x(),newacceleratedata);

    //    qint8 i=0;
    //    for(i=0;i<10;i++){
    //        data_y[i] = data_y[i+1];
    //    }
    //    data_y[i] = newdata;
}

void tabmonitoragvwindow::on_tabmonagv_linkbutton1_clicked()
{
    QMessageBox::about(this, "AGV#001", QString("【型号参数】").append("\n")
                       .append("具体型号：NUAA-BG-AGV-A").append("\n")
                       .append("额定载重量：1200 KG").append("\n")
                       .append("车身自重：1100 KG").append("\n")
                       .append("车体尺寸：2500x950x2100 mm").append("\n")
//                       .append("导引方式：激光导引").append("\n")
                       .append("停位精度：±10 mm").append("\n")
                       .append("转弯半径：600-1200 mm").append("\n")
//                       .append("最小启动距离：mm").append("\n")
                       .append("运行速度：0.4-1.2 m/s").append("\n")
                       .append("运动形式：单舵轮 前进 后退 转弯").append("\n")
                       .append("更多型号信息︾").append("\n")
//                       .append("工作周期：6 h").append("\n")
//                       .append("充电方式：").append("\n")
//                       .append("运载方式：").append("\n")
//                       .append("移载方式：").append("\n")
//                       .append("其他信息：本AGV由XXX制造提供"))
                       .append("【统计信息】").append("\n")
                       .append("故障次数：0 次").append("\n")
                       .append("运行总时长：14.2 h").append("\n")
                       .append("总任务数：21 个").append("\n")
                       .append("更多统计信息︾"));
    QMessageBox::warning(this, "系统警告", "与AGV#001无法通讯，请检查！", QMessageBox::Yes, QMessageBox::Help);
}

void tabmonitoragvwindow::on_tabmonagv_linkbutton2_clicked()
{
    QMessageBox::about(this, QString("AGV#002"), QString("AGV#002的型号参数：").append("\n")
                       .append("具体型号：AGV#002-NJIT").append("\n")
                       .append("额定载重量：KG").append("\n")
                       .append("车身自重：KG").append("\n")
                       .append("车体尺寸：xxx").append("\n")
                       .append("导引方式：视觉导引").append("\n")
                       .append("停位精度：mm").append("\n")
                       .append("最小转弯半径：mm").append("\n")
                       .append("最小启动距离：mm").append("\n")
                       .append("运行速度：m/s").append("\n")
                       .append("运动形式：单舵轮").append("\n")
                       .append("工作周期：h").append("\n")
                       .append("充电方式：").append("\n")
                       .append("运载方式：").append("\n")
                       .append("移载方式：").append("\n")
                       .append("其他信息：本AGV由XXX制造提供"));
}
