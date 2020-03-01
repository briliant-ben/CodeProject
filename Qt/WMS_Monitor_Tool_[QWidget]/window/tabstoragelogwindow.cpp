#pragma execution_character_set("utf-8")
#include <QFileDialog>
#include <QScrollBar>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include "tabstoragelogwindow.h"
#include "ui_tabstoragelogwindow.h"
#include "entity/staff.h"
#include "Windows.h"

tabstoragelogwindow::tabstoragelogwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabstoragelogwindow),
    newstreamdao(new storagestreamdao)
{
    ui->setupUi(this);
    totalnumber = 0;
    totalpage = 1;
    currentpage = 1;
    flag = 0;

    ui->tabstolog_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tabstolog_table->setSortingEnabled(true);
    ui->tabstolog_table->setItemDelegate(new QSqlRelationalDelegate(ui->tabstolog_table));

    QRegExp regExp("^[0-9]*$");//[1-9][A-Za-z]{[0-9],[a-z]}
    ui->tabstolog_currenttext->setValidator(new QRegExpValidator(regExp,this));
    ui->tabstolog_currenttext->setText(QString::number(currentpage));
    ui->tabstolog_totalnumtext->setText(QString::number(currentpage));

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,"确定");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");
}

tabstoragelogwindow::~tabstoragelogwindow()
{
    delete ui;
}

void tabstoragelogwindow::judgeprivilegeslot(){
    if(staff::staticrole == 1){
        ui->tabstolog_clearbutton->setEnabled(true);
        ui->tabstolog_exportbutton->setEnabled(true);
        ui->tabstolog_printbutton->setEnabled(true);
        ui->tabstolog_table->setEditTriggers(QAbstractItemView::DoubleClicked
                                             | QAbstractItemView::EditKeyPressed
                                             | QAbstractItemView::AnyKeyPressed);
    }
}

void tabstoragelogwindow::on_tabstolog_choicecombox_currentIndexChanged(int)
{
    ui->tabstolog_lastbutton->setEnabled(false);
    ui->tabstolog_nextbutton->setEnabled(false);
}

void tabstoragelogwindow::on_tabstolog_choicetext_textChanged(const QString &)
{
    ui->tabstolog_lastbutton->setEnabled(false);
    ui->tabstolog_nextbutton->setEnabled(false);
}

void tabstoragelogwindow::on_tabstolog_querybutton_clicked()
{
    flag = 1;
    if(newstreamdao->showstoragelog(ui->tabstolog_tablecombox->currentIndex())){
        filterstring = getfilterstring(ui->tabstolog_choicetext->text());
        newstreamdao->getrtmodel()->setFilter(filterstring);

        //get the relevant number of the sql result
        totalnumber = newstreamdao->getrtmodel()->rowCount();
        ui->tabstolog_totalnumtext->setText(QString::number(totalnumber));
        totalpage = (totalnumber%16 == 0)?(totalnumber / 16):(totalnumber / 16 + 1);
        if(totalpage == 0){
            totalpage = 1;
        }
        ui->tabstolog_totaltext->setText(QString::number(totalpage));
        currentpage = 1;
        ui->tabstolog_currenttext->setText(QString::number(currentpage));

        ui->tabstolog_table->setModel(newstreamdao->getrtmodel());
    }else{
        return;
    }
    ui->tabstolog_table->sortByColumn(0,Qt::AscendingOrder);
    ui->tabstolog_table->resizeColumnsToContents();
    ui->tabstolog_table->horizontalHeader()->setStretchLastSection(true);
    ui->tabstolog_lastbutton->setEnabled(true);
    ui->tabstolog_nextbutton->setEnabled(true);
}

QString tabstoragelogwindow::getfilterstring(const QString &choice)
{
    if(choice != ""){
        switch (ui->tabstolog_choicecombox->currentIndex()) {
        case 0:
            return QString("people like '%%1%'").arg(choice);//means search the record include the string %1
            break;
        case 1:
            return QString("date_time like '%%1%'").arg(choice);
            break;
        case 2:
            return QString("modelnumber like '%%1%'").arg(choice);
            break;
        case 3:
            return QString("totalnumber like '%%1%'").arg(choice);
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

void tabstoragelogwindow::on_tabstolog_clearbutton_clicked(bool checked)
{
    if(flag != 0){
        //        flag = 2;
        switch (ui->tabstolog_tablecombox->currentIndex()) {
        case 0:
            if(checked){
                msgBox.setText("确认要清空入库日志表？");
                if(msgBox.exec() == QMessageBox::Ok){
                    newstreamdao->clearstoragelog(00);//delete
                }
            }
            else{
                msgBox.setText("确认要重置入库日志表？");
                if(msgBox.exec() == QMessageBox::Ok){
                    newstreamdao->clearstoragelog(01);//truncate
                }
            }
            break;
        case 1:
            if(checked){
                msgBox.setText("确认要清空出库日志表？");
                if(msgBox.exec() == QMessageBox::Ok){
                    newstreamdao->clearstoragelog(10);//delete
                }
            }
            else{
                msgBox.setText("确认要重置出库日志表？");
                if(msgBox.exec() == QMessageBox::Ok){
                    newstreamdao->clearstoragelog(11);//truncate
                }
            }
            break;
        case 2:
            if(checked){
                msgBox.setText("确认要清空盘点日志表？");
                if(msgBox.exec() == QMessageBox::Ok){
                    newstreamdao->clearstoragelog(20);//delete
                }
            }
            else{
                msgBox.setText("确认要重置盘点日志表？");
                if(msgBox.exec() == QMessageBox::Ok){
                    newstreamdao->clearstoragelog(21);//truncate
                }
            }
            break;
        default:
            break;
        }
    }
}

void tabstoragelogwindow::on_tabstolog_exportbutton_clicked()
{
    if(flag != 0){
        //        flag = 3;
        switch (ui->tabstolog_tablecombox->currentIndex()) {
        case 0:
            msgBox.setText("确认要导出仓储入库日志表？");
            break;
        case 1:
            msgBox.setText("确认要导出仓储出库日志表？");
            break;
        case 2:
            msgBox.setText("确认要导出仓储盘点日志表？");
            break;
        default:
            break;
        }
        if(msgBox.exec() == QMessageBox::Ok){
            QString filename = QFileDialog::getSaveFileName(this, "文件另存为", QDir::currentPath(), "Text files (*.txt)");
            //QCoreApplication::applicationDirPath()    QDir::currentPath()
            if(filename.isEmpty()){
                msgBox.setText("文件名不能为空！");
                msgBox.exec();
                return;
            }
            if(newstreamdao->exportstoragelogtotxt(filename,ui->tabstolog_tablecombox->currentIndex())){
                msgBox.setText("导出日志表成功！");
                msgBox.exec();
            }
            else{
                msgBox.setText("导出日志表失败！");
                msgBox.exec();
            }
        }
    }
}

void tabstoragelogwindow::on_tabstolog_printbutton_clicked()
{
    if(flag != 0){
        //        flag = 4;
    }
}

void tabstoragelogwindow::on_tabstolog_lastbutton_clicked()
{
    if(currentpage <= totalpage && currentpage > 1){
        ui->tabstolog_currenttext->setText(QString::number(--currentpage));
        ui->tabstolog_table->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
    }
}

void tabstoragelogwindow::on_tabstolog_currenttext_returnPressed()
{
    if(ui->tabstolog_currenttext->text().toInt() > totalpage){
        ui->tabstolog_currenttext->setText(QString(totalpage));
        currentpage = totalpage;
    }
    if(ui->tabstolog_currenttext->text().toInt() < 1){
        ui->tabstolog_currenttext->setText("1");
        currentpage = 1;
    }
    currentpage = ui->tabstolog_currenttext->text().toInt();
    ui->tabstolog_table->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
}

void tabstoragelogwindow::on_tabstolog_nextbutton_clicked()
{
    if(currentpage < totalpage && currentpage >= 1){
        ui->tabstolog_currenttext->setText(QString::number(++currentpage));
        ui->tabstolog_table->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
    }
}

void tabstoragelogwindow::on_tabstolog_table_clicked(const QModelIndex &)
{

}
