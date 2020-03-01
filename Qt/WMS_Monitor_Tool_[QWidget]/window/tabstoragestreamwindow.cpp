#pragma execution_character_set("utf-8")
#include "tabstoragestreamwindow.h"
#include "ui_tabstoragestreamwindow.h"
#include <QScrollBar>
#include "entity/staff.h"

tabstoragestreamwindow::tabstoragestreamwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabstoragestreamwindow),
    newstreamdao(new storagestreamdao)/*,
    newstrwin(new streamrecordwindow)*/
{
    ui->setupUi(this);
    totalnumber = 0;
    totalpage = 1;
    currentpage = 1;
    flag = 0;

    newstrwin.setFixedSize(300,360);
    newstrwin.setWindowTitle("StorageStream Record");
    newstrwin.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

    ui->tabstream_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tabstream_table->setSortingEnabled(true);
    ui->tabstream_table->setItemDelegate(new QSqlRelationalDelegate(ui->tabstream_table));

    QRegExp regExp("^[0-9]*$");//[1-9][A-Za-z]{[0-9],[a-z]}
    ui->tabstream_currenttext->setValidator(new QRegExpValidator(regExp,this));
    ui->tabstream_currenttext->setText(QString::number(currentpage));
    ui->tabstream_currenttext->setText(QString::number(currentpage));

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,"确定");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");

    connect(this, SIGNAL(judgewhichkind(int)), &newstrwin, SLOT(judgement(int)));
}

tabstoragestreamwindow::~tabstoragestreamwindow()
{
    delete ui;
}

void tabstoragestreamwindow::judgeprivilegeslot(int which)
{
    if(staff::staticrole == 1 || staff::staticrole == 2){
        ui->tabstream_submitbutton->setEnabled(true);
        ui->tabstream_deletebutton->setEnabled(true);
        ui->tabstream_cancelbutton->setEnabled(true);
        ui->tabstream_table->setEditTriggers(QAbstractItemView::DoubleClicked
                                             | QAbstractItemView::EditKeyPressed
                                             | QAbstractItemView::AnyKeyPressed);
    }
    ui->tabstream_tablecombox->setCurrentIndex(which);
}

void tabstoragestreamwindow::on_tabstream_choicecombox_currentIndexChanged(int index)
{
    ui->tabstream_choicetext->setText("");
    if(index == 1){
        ui->tabstream_choicetext->setPlaceholderText("input example:2000-01-01 00:00");
    }
    else{
        ui->tabstream_choicetext->setPlaceholderText("");
    }
    ui->tabstream_lastbutton->setEnabled(false);
    ui->tabstream_nextbutton->setEnabled(false);
}

void tabstoragestreamwindow::on_tabstream_choicetext_textChanged(const QString &)
{
    ui->tabstream_lastbutton->setEnabled(false);
    ui->tabstream_nextbutton->setEnabled(false);
}

void tabstoragestreamwindow::on_tabstream_querybutton_clicked()
{
    flag = 1;
    switch (ui->tabstream_tablecombox->currentIndex()) {
    case 0://storagein
        if(newstreamdao->showstoragein()){
            break;
        }else{
            return;
        }
        break;
    case 1://storageout
        if(newstreamdao->showstorageout()){
            break;
        }else{
            return;
        }
        break;
    case 2://storageinventory
        if(newstreamdao->showstorageinventory()){
            break;
        }else{
            return;
        }
        break;
    default:
        return;
        break;
    }
    newstreamdao->getrtmodel()->setFilter(getfilterstring(ui->tabstream_choicetext->text()));

    //get the relevant number of the sql result
    totalnumber = newstreamdao->getrtmodel()->rowCount();
    ui->tabstream_totalnumtext->setText(QString::number(totalnumber));
    totalpage = (totalnumber%15 == 0)?(totalnumber / 15):(totalnumber / 15 + 1);
    if(totalpage == 0){
        totalpage = 1;
    }
    ui->tabstream_totaltext->setText(QString::number(totalpage));
    currentpage = 1;
    ui->tabstream_currenttext->setText(QString::number(currentpage));

    ui->tabstream_table->setModel(newstreamdao->getrtmodel());

    ui->tabstream_table->sortByColumn(0,Qt::AscendingOrder);
    ui->tabstream_table->resizeColumnsToContents();
    ui->tabstream_table->horizontalHeader()->setStretchLastSection(true);
    ui->tabstream_lastbutton->setEnabled(true);
    ui->tabstream_nextbutton->setEnabled(true);
}

QString tabstoragestreamwindow::getfilterstring(const QString &choice)
{
    bool queryoption;
    (ui->tabstream_optioncombox->currentIndex() == 1)?queryoption=true:queryoption=false;
    if(choice != ""){
        switch (ui->tabstream_choicecombox->currentIndex()) {
        case 0:
            switch (ui->tabstream_tablecombox->currentIndex()) {
            case 0://storagein
                return queryoption?QString("idstoragein='%1'").arg(choice)
                                 :QString("idstoragein like '%%1%'").arg(choice);
                break;
            case 1://storageout
                return queryoption?QString("idstorageout='%1'").arg(choice)
                                 :QString("idstorageout like '%%1%'").arg(choice);
                break;
            case 2://stocktake
                return queryoption?QString("idstocktake='%1'").arg(choice)
                                 :QString("idstocktake like '%%1%'").arg(choice);
                break;
            default:
                return "";
                break;
            }
            break;//need!!!
        case 1:
            return queryoption?QString("time='%1'").arg(choice)
                             :QString("time like '%%1%'").arg(choice);
            break;
        case 2:
            return queryoption?QString("relTblAl_2.location='%1'").arg(choice)
                             :QString("relTblAl_2.location like '%%1%'").arg(choice);
            break;
        case 3:
            return queryoption?QString("relTblAl_3.model='%1'").arg(choice)
                             :QString("relTblAl_3.model like '%%1%'").arg(choice);
            break;
        case 4:
            return queryoption?QString("quantity='%1'").arg(choice)
                             :QString("quantity like '%%1%'").arg(choice);
            break;
        case 5:
            return queryoption?QString("state='%1'").arg(choice)
                             :QString("state like '%%1%'").arg(choice);
            break;
        case 6:
            return queryoption?QString("dutypeople='%1'").arg(choice)
                             :QString("dutypeople like '%%1%'").arg(choice);
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

void tabstoragestreamwindow::on_tabstream_inbutton_clicked()
{
    emit judgewhichkind(0);
    newstrwin.show();

}

void tabstoragestreamwindow::on_tabstream_outbutton_clicked()
{
    emit judgewhichkind(1);
    newstrwin.show();
}

void tabstoragestreamwindow::on_tabstream_inventorybutton_clicked()
{
    emit judgewhichkind(2);
    newstrwin.show();
}

void tabstoragestreamwindow::on_tabstream_submitbutton_clicked()
{
    if(flag == 2){
        flag = 3;
        newstreamdao->getrtmodel()->database().transaction();//begin database transaction
        if(newstreamdao->getrtmodel()->submitAll()){
            newstreamdao->getrtmodel()->database().commit();
            msgBox.setText("提交修改成功！");
            msgBox.exec();
        }
        else{
            newstreamdao->getrtmodel()->database().rollback();
            msgBox.setText(QString("<font>数据库错误：<br/>%1</font>")
                                  .arg(newstreamdao->getrtmodel()->lastError().text()));
            msgBox.exec();
        }
    }
}

void tabstoragestreamwindow::on_tabstream_deletebutton_clicked()
{
    if(flag == 2){
        flag = 4;
        newstreamdao->getrtmodel()->revertAll();
    }
}

void tabstoragestreamwindow::on_tabstream_cancelbutton_clicked()
{
    if(flag != 0){
        flag = 5;
        QModelIndexList indexlist = ui->tabstream_table->selectionModel()->selectedIndexes();
        if(indexlist.size() != 0){
            QSet<qint32> indexset;
            QModelIndex index;
            qint32 row;
            foreach (index, indexlist) {
                indexset<<index.row();
            }
            foreach (row, indexset) {
                newstreamdao->getrtmodel()->removeRow(row);//dont need (currentpage-1)*15 + row;
            }
            msgBox.setText(QString("确认要删除这%1行？").arg(indexset.size()));
            if(msgBox.exec() == QMessageBox::Ok){
                newstreamdao->getrtmodel()->submitAll();
            }
            else{
                newstreamdao->getrtmodel()->revertAll();
            }
        }
        else{
            msgBox.setText(QString("您没有选中任何一行！"));
            msgBox.exec();
        }
    }
}

void tabstoragestreamwindow::on_tabstream_table_clicked(const QModelIndex &)
{
    if(flag != 0){
        flag = 2;
    }
}

void tabstoragestreamwindow::on_tabstream_lastbutton_clicked()
{
    if(currentpage <= totalpage && currentpage > 1){
        ui->tabstream_currenttext->setText(QString::number(--currentpage));
        //        int currentvalue = ui->tabper_stafftable->verticalScrollBar()->value();
        ui->tabstream_table->verticalScrollBar()->setSliderPosition((currentpage-1)*15);
    }
}

void tabstoragestreamwindow::on_tabstream_currenttext_returnPressed()
{
    if(ui->tabstream_currenttext->text().toInt() > totalpage){
        ui->tabstream_currenttext->setText(QString(totalpage));
        currentpage = totalpage;
    }
    if(ui->tabstream_currenttext->text().toInt() < 1){
        ui->tabstream_currenttext->setText("1");
        currentpage = 1;
    }
    currentpage = ui->tabstream_currenttext->text().toInt();
    ui->tabstream_table->verticalScrollBar()->setSliderPosition((currentpage-1)*15);
}

void tabstoragestreamwindow::on_tabstream_nextbutton_clicked()
{
    if(currentpage < totalpage && currentpage >= 1){
        ui->tabstream_currenttext->setText(QString::number(++currentpage));
        ui->tabstream_table->verticalScrollBar()->setSliderPosition((currentpage-1)*15);
    }
}
