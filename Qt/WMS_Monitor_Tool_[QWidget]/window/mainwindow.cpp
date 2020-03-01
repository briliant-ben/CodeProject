#pragma execution_character_set("utf-8")
#include <QDebug>
#include <QTextCodec>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDesktopServices"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow),
    timer(new QTimer(this)),
    animation(new QPropertyAnimation(this)),
    newstafflogdao(new stafflogdao),
    newtabper(new tabpersonnelwindow),
    newtabstalog(new tabstafflogwindow),
    newtabstock(new tabstoragestockwindow),
    newtabstream(new tabstoragestreamwindow),
    newtabstolog(new tabstoragelogwindow),
    newtabmonagv(new tabmonitoragvwindow),
    newstatisticone(new tabstatisticone),
    newtabdispatch(new tabdispatchwindow),
    newreportform(new tabreportformwindow)/*,
            newconfigure(new systemconfigurewindow)*/
{
    ui->setupUi(this);//ui->tabwidget->removeTab(X);

    QFont font;
    font.setUnderline(true);
    ui->tabadmin_linkbutton1->setFont(font);
    ui->tabadmin_linkbutton2->setFont(font);
    ui->tabadmin_linkbutton3->setFont(font);
    ui->tabadmin_linkbutton4->setFont(font);
    ui->main_timeaction->setText(QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate));

    animation->setPropertyName("windowOpacity");
    animation->setDuration(222);
    animation->setStartValue(0);
    animation->setEndValue(1);

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    msgBox.setWindowTitle("警告");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,"确定");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");

    newconfigure.setWindowFlags(Qt::WindowStaysOnTopHint);

    view = new QWebEngineView(ui->tabadmin_frame);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutdo()));
    connect(ui->tabwidget, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));
    //connect(ui->tabwidget, QTabWidget::tabCloseRequested(int), this, mainwindow::removeSubTab(int));
    connect(this, SIGNAL(judgeprivilege()), newtabper, SLOT(judgeprivilegeslot()));
    connect(this, SIGNAL(judgeprivilege()), newtabstalog, SLOT(judgeprivilegeslot()));
    connect(this, SIGNAL(judgeprivilege()), newtabstock, SLOT(judgeprivilegeslot()));
    connect(this, SIGNAL(judgeprivilegewhich(qint32)), newtabstream, SLOT(judgeprivilegeslot(qint32)));
    connect(this, SIGNAL(judgeprivilege()), newtabstolog, SLOT(judgeprivilegeslot()));
    connect(this, SIGNAL(judgeprivilegewhich(qint32)), newtabmonagv, SLOT(judgeprivilegeslot(qint32)));
    connect(this, SIGNAL(judgeprivilege()), newstatisticone, SLOT(judgeprivilegeslot()));
    connect(this, SIGNAL(judgeprivilege()), newreportform, SLOT(judgeprivilegeslot()));
    connect(this, SIGNAL(judgeprivilege()), newtabdispatch, SLOT(judgeprivilegeslot()));
}

mainwindow::~mainwindow()
{
    delete ui;
    delete timer;
    delete animation;
    delete newstafflogdao;
    delete newtabper;
    delete newtabstalog;
    delete newtabstock;
    delete newtabstream;
    delete newtabstolog;
    delete newtabmonagv;
    delete newstatisticone;
    delete newtabdispatch;
}

void mainwindow::timeoutdo()
{
    ui->main_timeaction->setText(QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate));
}

void mainwindow::receiveData(qint32 id,QString name,qint32 role)//no need!!!!!!
{
    timer->start(30000);

    ui->main_inforaction->setText("欢迎！"+name);
    //    switch (role) {
    //    case value:

    //        break;
    //    default:
    //        break;
    //    }
}

void mainwindow::removeSubTab(qint32 index)
{
    ui->tabwidget->removeTab(index);
}

void mainwindow::on_main_storageaction_triggered()
{
    setitemexpand("仓 储");
}

void mainwindow::on_main_dispatchaction_triggered()
{
    setitemexpand("调 度");
}

void mainwindow::on_main_monitoraction_triggered()
{
    setitemexpand("监 控");
}

void mainwindow::on_main_personnelaction_triggered()
{
    setitemexpand("人 员");
}

void mainwindow::on_main_journalaction_triggered()
{
    setitemexpand("日 志");
}

void mainwindow::on_main_statisticaction_triggered()
{
    setitemexpand("统 计");
}

void mainwindow::on_main_reportaction_triggered()
{
    setitemexpand("报 表");
}

void mainwindow::on_main_exitaction_triggered()
{
    msgBox.setText(QString("<font>警告！将退出系统！<br/>您确定要退出？</font>"));
    //    animation->setTargetObject(&msgBox);
    //    animation->start();
    if(msgBox.exec() == QMessageBox::Ok){
        if(!newstafflogdao->insertstafflog(staff::staticid)){
            qDebug()<<"stafflog failed!";
        }
        qApp->exit();
    }
}

void mainwindow::on_main_inforaction_triggered()
{
    //show information of current user
    //    msgBox.setWindowTitle("信息");
    //    msgBox.setIcon(QMessageBox::Information);
    //    msgBox.setText("<font>您的信息：<br/></font>");
}

void mainwindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //    QList<QString> itemname;
    //    itemname<<"仓 储"<<"库 存"<<"入 库"<<"出 库"<<"盘 点";
    //    QList<QString>::iterator itemindex = qFind(itemname,item->text(column));
    QString itemname = item->text(column);
    ui->tabwidget->setCurrentIndex(0);
    if(itemname == "库 存"){
        if(newtabstock->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newtabstock,"库 存");
            ui->tabwidget->setCurrentWidget(newtabstock);
        }
    }else if(itemname == "入 库"){
        emit judgeprivilegewhich(0);
        if(newtabstream->isHidden()){
            ui->tabwidget->addTab(newtabstream,"出入库");
            ui->tabwidget->setCurrentWidget(newtabstream);
        }
    }else if(itemname == "出 库"){
        emit judgeprivilegewhich(1);
        if(newtabstream->isHidden()){
            ui->tabwidget->addTab(newtabstream,"出入库");
            ui->tabwidget->setCurrentWidget(newtabstream);
        }
    }else if(itemname == "盘 点"){
        emit judgeprivilegewhich(2);
        if(newtabstream->isHidden()){
            ui->tabwidget->addTab(newtabstream,"出入库");
            ui->tabwidget->setCurrentWidget(newtabstream);
        }
    }else if(itemname == "人员信息" || itemname == "权限管理"){//"权限管理"应该单独做成一页！！！
        if(newtabper->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newtabper, "人员信息");
            ui->tabwidget->setCurrentWidget(newtabper);
        }//
    }else if(itemname == "人员日志" || itemname == "调度日志" || itemname == "监控日志" ){
        if(newtabstalog->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newtabstalog, "人员日志");
            ui->tabwidget->setCurrentWidget(newtabstalog);
        }
    }else if(itemname == "仓储日志"){
        if(newtabstolog->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newtabstolog, "仓储日志");
            ui->tabwidget->setCurrentWidget(newtabstolog);
        }
    }else if(itemname == "AGV监控" || itemname == "机器人监控" || itemname == "机床监控" || itemname == "其他设备监控"){
        if(newtabmonagv->isHidden()){
            static qint32 page = 0;
            emit judgeprivilegewhich(page++);
            page = page % 2;
            ui->tabwidget->addTab(newtabmonagv, "AGV监控");
            ui->tabwidget->setCurrentWidget(newtabmonagv);
        }
    }else if(itemname == "仓储统计"){
        if(newstatisticone->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newstatisticone, "仓储统计");
            ui->tabwidget->setCurrentWidget(newstatisticone);
        }
    }else if(itemname == "监控统计" || itemname == "调度统计"){
        if(newstatisticone->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newstatisticone, "监控统计");
            ui->tabwidget->setCurrentWidget(newstatisticone);
        }
    }else if(itemname == "仓储报表"){
        if(newstatisticone->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newreportform, "仓储报表");
            ui->tabwidget->setCurrentWidget(newreportform);
        }
    }else if(itemname == "人员报表"){
        if(newstatisticone->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newreportform, "人员报表");
            ui->tabwidget->setCurrentWidget(newreportform);
        }
    }else if(itemname == "任务调度" || itemname == "车辆调度"){
        if(newtabdispatch->isHidden()){
            emit judgeprivilege();
            ui->tabwidget->addTab(newtabdispatch, "调度管理");
            ui->tabwidget->setCurrentWidget(newtabdispatch);
        }
    }
    else if(1){}//newstatisticone
}

void mainwindow::closeEvent(QCloseEvent *event)
{
    msgBox.setText(QString("<font>警告！将退出系统！<br/>您确定要退出？</font>"));
    //    animation->setTargetObject(&msgBox);
    //    animation->start();
    //    event->setAccepted(msgBox.exec() == QMessageBox::Ok);
    if(msgBox.exec() == QMessageBox::Ok){
        if(!newstafflogdao->insertstafflog(staff::staticid)){
            qDebug()<<"stafflog failed!";
        }
        event->accept();
    }
    else{
        event->ignore();
    }
}

void mainwindow::setitemexpand(QString name)
{
    itemlist = ui->treeWidget->findItems(name,Qt::MatchExactly);
    //    if(!itemlist.isEmpty()){
    //        itemlist[0]->setExpanded(!itemlist[0]->isExpanded());
    //    }
    itemlist[0]->setExpanded(!itemlist[0]->isExpanded());
}


void mainwindow::on_main_quitaction_triggered()
{
    msgBox.setText(QString("<font>警告！将退出系统！<br/>您确定要退出？</font>"));
    //    animation->setTargetObject(&msgBox);
    //    animation->start();
    if(msgBox.exec() == QMessageBox::Ok){
        if(!newstafflogdao->insertstafflog(staff::staticid)){
            qDebug()<<"stafflog failed!";
        }
        qApp->exit();
    }
}

void mainwindow::on_main_baiduaction_triggered()
{
    if(!QDesktopServices::openUrl(QUrl("http://www.baidu.com"))){
        msgBox.setText(QString("错误！请确认您的浏览器和网络！"));
        msgBox.exec();
    }
}

void mainwindow::on_main_referenceaction_triggered()
{
    if(!QDesktopServices::openUrl(QUrl("file:///F:/1.txt", QUrl::TolerantMode))){
        msgBox.setText(QString("错误！请再次尝试！"));
        msgBox.exec();
    }
}

void mainwindow::on_main_setupaction_triggered()
{
    newconfigure.setWindowTitle("系统设置");
    newconfigure.show();
}

void mainwindow::on_main_toolbar1action_triggered(bool checked)
{
    (checked)?ui->toolbar1->show():ui->toolbar1->hide();
    qDebug()<<checked;
}

void mainwindow::on_main_toobar2action_triggered(bool checked)
{
    (checked)?ui->toolbar2->show():ui->toolbar2->hide();
}

void mainwindow::on_mian_toolbar3action_triggered(bool checked)
{
    (checked)?ui->toolbar3->show():ui->toolbar3->hide();
}

void mainwindow::on_main_optionaction_triggered(bool checked)
{
    (checked)?ui->dockwidget1->show():ui->dockwidget1->hide();
}

void mainwindow::on_main_messageaction_triggered(bool checked)
{
    (checked)?ui->dockwidget2->show():ui->dockwidget2->hide();
}

void mainwindow::on_main_adminaction_triggered()
{
    ui->tabwidget->addTab(ui->tabhomepage,"主 页");
    ui->tabwidget->setCurrentWidget(ui->tabhomepage);
}

void mainwindow::on_main_systemaction_triggered()
{
    QMessageBox::about(this,"系统信息","<font>硬件信息：</font>"
                                   "<br/><br/>CPU:"
                                   "<br/><br/>GPU:BEN"
                                   "<br/><br/>Operating System: Windows 7 Profession"
                                   "<br/><br/>HARDDISK:</font>");
}

void mainwindow::on_main_aboutaction_triggered()
{
    QMessageBox::about(this,"关于WMS","<font>INTELLIGNET WMS SYSTEM 2.0！"
                                    "<br/><br/>Development IDE---Qt5.8.0(MSVC 2015, 32 bit)"
                                    "<br/><br/>Built On-------------July 01 2017 10:10"
                                    "<br/><br/>Author--------------BEN"
                                    "<br/><br/>Copyright-----------XU.COMPANY 2016-2017 All rights reserved"
                                    "<br/><br/>The program is provided AS IS with NO WARRANTY OF ANY KIND,"
                                    "<br/>     INCLUDING THE WARRANTY OF DESIGN,MERCHANTABILITY AND "
                                    "<br/>     FITNESS FOR A PARTICULAR PURPOSE."
                                    "</font>");
}

void mainwindow::on_tabadmin_refreshbutton_clicked()
{
    view->load(QUrl("http://i.tianqi.com/index.php?c=code&id=21&num=2"));//id=33,41,5,7,8,11,16,17,21
    view->show();
}

void mainwindow::on_tabadmin_linkbutton1_clicked()
{
    if(!QDesktopServices::openUrl(QUrl("http://www.baidu.com"))){
        msgBox.setText(QString("错误！请确认您的浏览器和网络！"));
        msgBox.exec();
    }
}

void mainwindow::on_main_fullscreenaction_triggered(bool checked)
{
    if(checked){
        this->showFullScreen();
    }else{
        this->showNormal();
    }
}

void mainwindow::on_mian_feedbackaction_triggered()
{
    fbwindow.setWindowTitle("信息反馈");
    fbwindow.show();
}
