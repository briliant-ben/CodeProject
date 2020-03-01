#pragma execution_character_set("utf-8")
#include <QScrollBar>
#include "tabpersonnelwindow.h"
#include "ui_tabpersonnelwindow.h"

tabpersonnelwindow::tabpersonnelwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabpersonnelwindow),
    newstaffdao(new staffdao())
{
    ui->setupUi(this);
    totalnumber = 0;
    totalpage = 1;
    currentpage = 1;
    flag = 0;

    QRegExp regExp("^[0-9]*$");//[1-9][A-Za-z]{[0-9],[a-z]}
    ui->tabper_currenttext->setValidator(new QRegExpValidator(regExp,this));

    //see if some can be deleted
    ui->tabper_stafftable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tabper_stafftable->setSortingEnabled(true);
    ui->tabper_stafftable->setItemDelegate(new QSqlRelationalDelegate(ui->tabper_stafftable));
    ui->tabper_currenttext->setText(QString::number(currentpage));
    ui->tabper_totaltext->setText(QString::number(totalpage));

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,"确定");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");
}

tabpersonnelwindow::~tabpersonnelwindow()
{
    delete ui;
}

void tabpersonnelwindow::judgeprivilegeslot(){
    if(staff::staticrole == 1){
        ui->tabper_deletebutton->setEnabled(true);
        ui->tabper_submitbutton->setEnabled(true);
        ui->tabper_cancelbutton->setEnabled(true);
        ui->tabper_stafftable->setEditTriggers(QAbstractItemView::DoubleClicked
                                               | QAbstractItemView::EditKeyPressed
                                               | QAbstractItemView::AnyKeyPressed);
    }
}

void tabpersonnelwindow::on_tabper_choicecombo_currentIndexChanged(int index)
{
    ui->tabper_choicetext->setText("");
    if(index == 4 || index == 5){
        ui->tabper_choicetext->setPlaceholderText("input example:2000-01-01 00:00");
    }
    else{
        ui->tabper_choicetext->setPlaceholderText("");
    }
}

void tabpersonnelwindow::on_tabper_inquirebutton_clicked()
{
    flag = 1;
    if(newstaffdao->showstaff()){
        QString choice = ui->tabper_choicetext->text();
        filterstring = getfilterstring(choice);
        newstaffdao->getrtmodel()->setFilter(filterstring);//qDebug()<<newstaffdao->getrtmodel()->filter();

        //get the relevant number of the sql result
        totalnumber = newstaffdao->getrtmodel()->rowCount();
        ui->tabper_totalnumtext->setText(QString::number(totalnumber));
        totalpage = (totalnumber%16 == 0)?(totalnumber / 16):(totalnumber / 16 + 1);
        if(totalpage == 0){
            totalpage = 1;
        }
        ui->tabper_totaltext->setText(QString::number(totalpage));
        currentpage = 1;
        ui->tabper_currenttext->setText(QString::number(currentpage));

        ui->tabper_stafftable->setModel(newstaffdao->getrtmodel());
        ui->tabper_stafftable->sortByColumn(0,Qt::AscendingOrder);
        if(newstaffdao->getstaff().staticrole != 1){
            ui->tabper_stafftable->hideColumn(0);
            ui->tabper_stafftable->hideColumn(2);
            ui->tabper_stafftable->hideColumn(7);
            ui->tabper_stafftable->hideColumn(8);
        }
    }
    else{
        return;
    }
    ui->tabper_stafftable->resizeColumnsToContents();
    ui->tabper_stafftable->horizontalHeader()->setStretchLastSection(true);
    ui->tabper_lastbutton->setEnabled(true);
    ui->tabper_nextbutton->setEnabled(true);
}

QString tabpersonnelwindow::getfilterstring(QString choice){
    if(choice != ""){
        switch (ui->tabper_choicecombo->currentIndex()) {
        case 0:
            return QString("number like '%%1%'").arg(choice);
            break;
        case 1:
            return QString("name like '%%1%'").arg(choice);
            break;
        case 2:
            return QString("unit like '%%1%'").arg(choice);
            break;
        case 3:
            return QString("position like '%%1%'").arg(choice);
            break;
        case 4:
            return QString("createtime like '%%1%'").arg(choice);
            break;
        case 5:
            return QString("updatetime like '%%1%'").arg(choice);
            break;
        case 6:
            return QString("role like '%%1%'").arg(choice);//choice.toInt()
            break;
        default:
            return "";
            break;
        }
    }
    else{
        return "";
    }
}

void tabpersonnelwindow::on_tabper_lastbutton_clicked()
{
    if(currentpage <= totalpage && currentpage > 1){
        ui->tabper_currenttext->setText(QString::number(--currentpage));
        //        int currentvalue = ui->tabper_stafftable->verticalScrollBar()->value();
        ui->tabper_stafftable->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
    }
}

void tabpersonnelwindow::on_tabper_nextbutton_clicked()
{
    if(currentpage < totalpage && currentpage >= 1){
        ui->tabper_currenttext->setText(QString::number(++currentpage));
        ui->tabper_stafftable->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
    }
}

void tabpersonnelwindow::on_tabper_currenttext_returnPressed()
{
    if(ui->tabper_currenttext->text().toInt() > totalpage){
        ui->tabper_currenttext->setText(QString(totalpage));
        currentpage = totalpage;
    }
    if(ui->tabper_currenttext->text().toInt() < 1){
        ui->tabper_currenttext->setText("1");
        currentpage = 1;
    }
    currentpage = ui->tabper_currenttext->text().toInt();
    ui->tabper_stafftable->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
}

void tabpersonnelwindow::on_tabper_choicetext_textChanged(const QString &)
{
    ui->tabper_lastbutton->setEnabled(false);
    ui->tabper_nextbutton->setEnabled(false);
}

void tabpersonnelwindow::on_tabper_submitbutton_clicked()
{
    if(flag == 2){
        flag = 3;
        newstaffdao->getrtmodel()->database().transaction();//begin database transaction
        if(newstaffdao->getrtmodel()->submitAll()){
            newstaffdao->getrtmodel()->database().commit();
            msgBox.setText("提交修改成功！");
            msgBox.exec();
        }
        else{
            newstaffdao->getrtmodel()->database().rollback();
            msgBox.setText(QString("<font>数据库错误：<br/>%1</font>")
                                  .arg(newstaffdao->getrtmodel()->lastError().text()));
            msgBox.exec();
        }
    }
}

void tabpersonnelwindow::on_tabper_cancelbutton_clicked()
{
    if(flag == 2){
        flag = 4;
        newstaffdao->getrtmodel()->revertAll();
    }
}

void tabpersonnelwindow::on_tabper_deletebutton_clicked()
{
    if(flag != 0){
        flag = 5;
        QModelIndexList indexlist = ui->tabper_stafftable->selectionModel()->selectedIndexes();
        if(indexlist.size() != 0){
            QSet<qint32> indexset;
            QModelIndex index;
            qint32 row;
            foreach (index, indexlist) {
                indexset<<index.row();
            }
            foreach (row, indexset) {
                newstaffdao->getrtmodel()->removeRow(row);//dont need (currentpage-1)*16 + row;
            }
            msgBox.setText(QString("确认要删除这%1行？").arg(indexset.size()));
            if(msgBox.exec() == QMessageBox::Ok){
                newstaffdao->getrtmodel()->submitAll();
            }
            else{
                newstaffdao->getrtmodel()->revertAll();
            }
        }
        else{
            msgBox.setText(QString("您没有选中任何一行！"));
            msgBox.exec();
        }
    }
}

void tabpersonnelwindow::on_tabper_stafftable_clicked(const QModelIndex &)
{
    if(flag != 0){
        flag = 2;
    }
}
