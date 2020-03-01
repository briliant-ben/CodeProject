#pragma execution_character_set("utf-8")
#include <QScrollBar>
#include "tabstoragestockwindow.h"
#include "ui_tabstoragestockwindow.h"
#include "entity/staff.h"

tabstoragestockwindow::tabstoragestockwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabstoragestockwindow),
    newcouplingdao(new couplingdao),
    newlocationdao(new locationdao)
{
    ui->setupUi(this);
    totalnumber = 0;
    totalpage = 1;
    currentpage = 1;
    flag = 0;

    ui->tabstock_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tabstock_table->setSortingEnabled(true);
    ui->tabstock_table->setItemDelegate(new QSqlRelationalDelegate(ui->tabstock_table));

    QRegExp regExp("^[0-9]*$");//[1-9][A-Za-z]{[0-9],[a-z]}
    ui->tabstock_currenttext->setValidator(new QRegExpValidator(regExp,this));
    ui->tabstock_currenttext->setText(QString::number(currentpage));
    ui->tabstock_totalnumtext->setText(QString::number(currentpage));

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,"确定");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");
}

tabstoragestockwindow::~tabstoragestockwindow()
{
    delete ui;
}

void tabstoragestockwindow::judgeprivilegeslot()
{
    if(staff::staticrole == 1){
        ui->tabstock_submitbutton->setEnabled(true);
        ui->tabstock_deletebutton->setEnabled(true);
        ui->tabstock_cancelbutton->setEnabled(true);
        ui->tabstock_table->setEditTriggers(QAbstractItemView::DoubleClicked
                                             | QAbstractItemView::EditKeyPressed
                                             | QAbstractItemView::AnyKeyPressed);
    }
}



void tabstoragestockwindow::on_tabstock_tablecombox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->tabstock_choicecombox->clear();
        QStringList texts;
        texts<<"位置编号"<<"管料"<<"数量"<<"状态"<<"其他";
        ui->tabstock_choicecombox->addItems(texts);
    }else{
        ui->tabstock_choicecombox->clear();
        QStringList texts;
        texts<<"型号"<<"外径"<<"接箍外径"<<"长度"<<"重量"<<"每筐数量"<<"总重";
        ui->tabstock_choicecombox->addItems(texts);
    }
}

void tabstoragestockwindow::on_tabstock_choicecombox_currentIndexChanged(int)
{
    ui->tabstock_lastbutton->setEnabled(false);
    ui->tabstock_nextbutton->setEnabled(false);
}

void tabstoragestockwindow::on_tabstock_querybutton_clicked()
{
    flag = 1;
    if(ui->tabstock_tablecombox->currentIndex() == 0){
        if(newlocationdao->showstoragelocation()){
            newlocationdao->getrtmodel()->setFilter(getfilterstring(ui->tabstock_choicetext->text()));
            //newlocationdao->getrtmodel()->select();
            ui->tabstock_table->setModel(newlocationdao->getrtmodel());

            totalnumber = newlocationdao->getrtmodel()->rowCount();
            ui->tabstock_totalnumtext->setText(QString::number(totalnumber));
        }
        else{
            return;
        }
    }else{
        if(newcouplingdao->showcoupling()){
            newcouplingdao->getrtmodel()->setFilter(getfilterstring(ui->tabstock_choicetext->text()));
            //newlocationdao->getrtmodel()->select();
            ui->tabstock_table->setModel(newcouplingdao->getrtmodel());

            totalnumber = newcouplingdao->getrtmodel()->rowCount();
            ui->tabstock_totalnumtext->setText(QString::number(totalnumber));
        }
        else{
            return;
        }
    }
    //get the relevant number of the sql result
    totalpage = (totalnumber%15 == 0)?(totalnumber / 15):(totalnumber / 15 + 1);
    if(totalpage == 0){
        totalpage = 1;
    }
    ui->tabstock_totaltext->setText(QString::number(totalpage));
    currentpage = 1;
    ui->tabstock_currenttext->setText(QString::number(currentpage));

    ui->tabstock_table->sortByColumn(0,Qt::AscendingOrder);
    ui->tabstock_table->hideColumn(0);
    ui->tabstock_table->resizeColumnsToContents();
    ui->tabstock_table->horizontalHeader()->setStretchLastSection(true);

    ui->tabstock_lastbutton->setEnabled(true);
    ui->tabstock_nextbutton->setEnabled(true);
}

QString tabstoragestockwindow::getfilterstring(const QString &choice)
{
    bool queryoption;
    (ui->tabstock_optioncombox->currentIndex() == 1)?queryoption=true:queryoption=false;
    if(choice != ""){
        if(ui->tabstock_tablecombox->currentIndex() == 0){
            switch (ui->tabstock_choicecombox->currentIndex()) {
            case 0:
                return queryoption?QString("location='%1'").arg(choice)
                                  :QString("location like '%%1%'").arg(choice);
                break;
            case 1:
                return queryoption?QString("relTblAl_2.model='%1'").arg(choice)
                                  :QString("relTblAl_2.model like '%%1%'").arg(choice);
                break;
            case 2:
                return queryoption?QString("quantity='%1'").arg(choice)
                                  :QString("quantity like '%%1%'").arg(choice);
                break;
            case 3:
                return queryoption?QString("state='%1'").arg(choice)
                                  :QString("state like '%%1%'").arg(choice);
                break;
            case 4:
                return queryoption?QString("other='%1'").arg(choice)
                                  :QString("other like '%%1%'").arg(choice);
                break;
            default:
                return "";
                break;
            }
        }
        else{
            switch (ui->tabstock_choicecombox->currentIndex()) {
            case 0:
                return queryoption?QString("model='%1'").arg(choice)
                                  :QString("model like '%%1%'").arg(choice);
                break;
            case 1:
                return queryoption?QString("diameter='%1'").arg(choice)
                                  :QString("diameter like '%%1%'").arg(choice);
                break;
            case 2:
                return queryoption?QString("cdiameter='%1'").arg(choice)
                                  :QString("cdiameter like '%%1%'").arg(choice);
                break;
            case 3:
                return queryoption?QString("length='%1'").arg(choice)
                                  :QString("length like '%%1%'").arg(choice);
                break;
            case 4:
                return queryoption?QString("weigh='%1'").arg(choice)
                                  :QString("weigh like '%%1%'").arg(choice);
                break;
            case 5:
                return queryoption?QString("numberperbasket='%1'").arg(choice)
                                  :QString("numberperbasket like '%%1%'").arg(choice);
                break;
            case 6:
                return queryoption?QString("totalweigh='%1'").arg(choice)
                                  :QString("totalweigh like '%%1%'").arg(choice);
                break;
            default:
                return "";
                break;
            }
        }
    }
    else{
        return "";
    }
}

void tabstoragestockwindow::on_tabstock_submitbutton_clicked()
{
    if(flag == 2){
        flag = 3;
        if(ui->tabstock_tablecombox->currentIndex() == 0){
            newlocationdao->getrtmodel()->database().transaction();//begin database transaction
            if(newlocationdao->getrtmodel()->submitAll()){
                newlocationdao->getrtmodel()->database().commit();
                msgBox.setText("提交修改成功！");
                msgBox.exec();
            }
            else{
                newlocationdao->getrtmodel()->database().rollback();
                msgBox.setText(QString("<font>数据库错误：<br/>%1</font>")
                                      .arg(newlocationdao->getrtmodel()->lastError().text()));
                msgBox.exec();
            }
        }
        else{//ui->tabstock_tablecombox->currentIndex() == 1
            newcouplingdao->getrtmodel()->database().transaction();//begin database transaction
            if(newcouplingdao->getrtmodel()->submitAll()){
                newcouplingdao->getrtmodel()->database().commit();
                msgBox.setText("提交修改成功！");
                msgBox.exec();
            }
            else{
                newcouplingdao->getrtmodel()->database().rollback();
                msgBox.setText(QString("<font>数据库错误：<br/>%1</font>")
                                      .arg(newcouplingdao->getrtmodel()->lastError().text()));
                msgBox.exec();
            }
        }
    }
}

void tabstoragestockwindow::on_tabstock_deletebutton_clicked()
{
    if(flag != 0){
        flag = 5;
        QModelIndexList indexlist = ui->tabstock_table->selectionModel()->selectedIndexes();
        if(indexlist.size() != 0){
            QSet<qint32> indexset;
            QModelIndex index;
            qint32 row;
            foreach (index, indexlist) {
                indexset<<index.row();
            }
            if(ui->tabstock_tablecombox->currentIndex() == 0){
                foreach (row, indexset) {
                    newlocationdao->getrtmodel()->removeRow(row);//dont need (currentpage-1)*15 + row;
                }
                msgBox.setText(QString("确认要删除这%1行？").arg(indexset.size()));
                if(msgBox.exec() == QMessageBox::Ok){
                    newlocationdao->getrtmodel()->submitAll();
                }
                else{
                    newlocationdao->getrtmodel()->revertAll();
                }
            }
            else{
                foreach (row, indexset) {
                    newcouplingdao->getrtmodel()->removeRow(row);//dont need (currentpage-1)*15 + row;
                }
                msgBox.setText(QString("确认要删除这%1行？").arg(indexset.size()));
                if(msgBox.exec() == QMessageBox::Ok){
                    newcouplingdao->getrtmodel()->submitAll();
                }
                else{
                    newcouplingdao->getrtmodel()->revertAll();
                }
            }
        }
        else{
            msgBox.setText(QString("您没有选中任何一行！"));
            msgBox.exec();
        }
    }
}

void tabstoragestockwindow::on_tabstock_cancelbutton_clicked()
{
    if(flag == 2){
        flag = 4;
        if(ui->tabstock_tablecombox->currentIndex() == 0){
            newlocationdao->getrtmodel()->revertAll();
        }
        else{
            newcouplingdao->getrtmodel()->revertAll();
        }
    }
}

void tabstoragestockwindow::on_tabstock_lastbutton_clicked()
{
    if(currentpage <= totalpage && currentpage > 1){
        ui->tabstock_currenttext->setText(QString::number(--currentpage));
        //        int currentvalue = ui->tabper_stafftable->verticalScrollBar()->value();
        ui->tabstock_table->verticalScrollBar()->setSliderPosition((currentpage-1)*15);
    }
}

void tabstoragestockwindow::on_tabstock_currenttext_returnPressed()
{
    if(ui->tabstock_currenttext->text().toInt() > totalpage){
        ui->tabstock_currenttext->setText(QString(totalpage));
        currentpage = totalpage;
    }
    if(ui->tabstock_currenttext->text().toInt() < 1){
        ui->tabstock_currenttext->setText("1");
        currentpage = 1;
    }
    currentpage = ui->tabstock_currenttext->text().toInt();
    ui->tabstock_table->verticalScrollBar()->setSliderPosition((currentpage-1)*15);
}

void tabstoragestockwindow::on_tabstock_nextbutton_clicked()
{
    if(currentpage < totalpage && currentpage >= 1){
        ui->tabstock_currenttext->setText(QString::number(++currentpage));
        //        int currentvalue = ui->tabper_stafftable->verticalScrollBar()->value();
        ui->tabstock_table->verticalScrollBar()->setSliderPosition((currentpage-1)*15);
    }
}

void tabstoragestockwindow::on_tabstock_table_clicked(const QModelIndex &)
{
    if(flag != 0){
        flag = 2;
    }
}
