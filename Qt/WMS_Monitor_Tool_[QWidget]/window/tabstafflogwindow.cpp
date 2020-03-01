#pragma execution_character_set("utf-8")
#include <QFileDialog>
#include <QScrollBar>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include "tabstafflogwindow.h"
#include "ui_tabstafflogwindow.h"
#include "entity/staff.h"
#include "Windows.h"

tabstafflogwindow::tabstafflogwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabstafflogwindow),
    newstafflogdao(new stafflogdao)
{
    ui->setupUi(this);
    totalnumber = 0;
    totalpage = 1;
    currentpage = 1;
    flag = 0;

    ui->tabstalog_choicetext->setPlaceholderText("input example:2000-01-01 00:00");

    ui->tabstalog_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tabstalog_table->setSortingEnabled(true);

    ui->tabstalog_table->setItemDelegate(new QSqlRelationalDelegate(ui->tabstalog_table));

    QRegExp regExp("^[0-9]*$");//[1-9][A-Za-z]{[0-9],[a-z]}
    ui->tabstalog_currenttext->setValidator(new QRegExpValidator(regExp,this));
    ui->tabstalog_currenttext->setText(QString::number(currentpage));
    ui->tabstalog_totalnumtext->setText(QString::number(currentpage));

    msgBox.setFont(QFont("等线", 11, QFont::Normal));
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,"确定");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");
}

tabstafflogwindow::~tabstafflogwindow()
{
    delete ui;
}

void tabstafflogwindow::judgeprivilegeslot(){
    if(staff::staticrole == 1){
        ui->tabstalog_clearbutton->setEnabled(true);
        ui->tabstalog_exportbutton->setEnabled(true);
        ui->tabstalog_printbutton->setEnabled(true);
        ui->tabstalog_table->setEditTriggers(QAbstractItemView::DoubleClicked
                                             | QAbstractItemView::EditKeyPressed
                                             | QAbstractItemView::AnyKeyPressed);
    }
}

void tabstafflogwindow::on_tabstalog_combox_currentIndexChanged(int index)
{
    ui->tabstalog_choicetext->setText("");
    if(index == 0){
        ui->tabstalog_choicetext->setPlaceholderText("input example:2000-01-01 00:00");
    }
    else{
        ui->tabstalog_choicetext->setPlaceholderText("");
    }
}

void tabstafflogwindow::on_tabstalog_choicetext_textChanged(const QString &)
{
    ui->tabstalog_lastbutton->setEnabled(false);
    ui->tabstalog_nextbutton->setEnabled(false);
}

void tabstafflogwindow::on_tabstalog_querybutton_clicked()
{
    flag = 1;
    if(newstafflogdao->showstafflog()){
        filterstring = getfilterstring(ui->tabstalog_choicetext->text());
        newstafflogdao->getrtmodel()->setFilter(filterstring);

        newstafflogdao->getrtmodel()->select();//need????

        //get the relevant number of the sql result
        totalnumber = newstafflogdao->getrtmodel()->rowCount();
        ui->tabstalog_totalnumtext->setText(QString::number(totalnumber));
        totalpage = (totalnumber%16 == 0)?(totalnumber / 16):(totalnumber / 16 + 1);
        if(totalpage == 0){
            totalpage = 1;
        }
        ui->tabstalog_totaltext->setText(QString::number(totalpage));
        currentpage = 1;
        ui->tabstalog_currenttext->setText(QString::number(currentpage));

        ui->tabstalog_table->setModel(newstafflogdao->getrtmodel());
    }
    else{
        return;
    }
    ui->tabstalog_table->sortByColumn(0,Qt::AscendingOrder);
    ui->tabstalog_table->resizeColumnsToContents();
    ui->tabstalog_table->horizontalHeader()->setStretchLastSection(true);
    ui->tabstalog_lastbutton->setEnabled(true);
    ui->tabstalog_nextbutton->setEnabled(true);
}

QString tabstafflogwindow::getfilterstring(const QString &choice)
{
    if(choice != ""){
        switch (ui->tabstalog_combox->currentIndex()) {
        case 0:
            return QString("time like '%%1%'").arg(choice);//means search the record include the string %1
            break;
        case 1:
            return QString("relTblAl_2.number like '%%1%'").arg(choice);
            break;
        case 2:
            return QString("relTblAl_3.name like '%%1%'").arg(choice);
            break;
        case 3:
            return QString("content like '%%1%'").arg(choice);
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

void tabstafflogwindow::on_tabstalog_clearbutton_clicked(bool checked)
{
    if(flag != 0){
        //        flag = 2;
        if(checked){
            msgBox.setText("确认要清空人员日志表？");
            if(msgBox.exec() == QMessageBox::Ok){
                newstafflogdao->clearstafflog(0);//delete
                qDebug()<<"clear table!";
            }
        }
        else{
            msgBox.setText("确认要重置人员日志表？");
            if(msgBox.exec() == QMessageBox::Ok){
                newstafflogdao->clearstafflog(1);//truncate
                qDebug()<<"truncate table!";
            }
        }
    }
}

void tabstafflogwindow::on_tabstalog_exportbutton_clicked()
{
    if(flag != 0){
        //        flag = 3;
        msgBox.setText("确认要导出人员日志表？");
        if(msgBox.exec() == QMessageBox::Ok){
            QString filename = QFileDialog::getSaveFileName(this, "文件另存为", QDir::currentPath(), "Text files (*.txt)");
            //QCoreApplication::applicationDirPath()    QDir::currentPath()
            if(filename.isEmpty()){
                msgBox.setText("文件名不能为空！");
                msgBox.exec();
                return;
            }
            if(newstafflogdao->exportstafflogtotxt(filename)){
                msgBox.setText("导出人员日志表成功！");
                msgBox.exec();
            }
            else{
                msgBox.setText("导出人员日志表失败！");
                msgBox.exec();
            }
        }
    }
}

void tabstafflogwindow::on_tabstalog_printbutton_clicked()
{
    if(flag != 0){
        //        flag = 4;
        msgBox.setText("确认要打印人员日志表？");
        if(msgBox.exec() == QMessageBox::Ok){
            QString filename = QFileDialog::getSaveFileName(this, "选择文件保存位置", QDir::currentPath(), "Excel files (*.xls)");
            if(filename.isEmpty()){
                msgBox.setText("文件名不能为空！");
                msgBox.exec();
                return;
            }
            if(newstafflogdao->exportstafflogtoexcel(filename)){
                msgBox.setText("人员日志表EXCEL生成！确认打印？");
                if(msgBox.exec() == QMessageBox::Ok){
                    QPrinter printer;
                    /*
                    if (QFileInfo(filename).suffix().isEmpty())
                        filename.append(".pdf");
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setOutputFileName(filename);
                    */

                    QPrintDialog printdialog(&printer, this);
                    if(printdialog.exec() == QDialog::Accepted){
                        if( printer.printerName().size() == 0){
                            qDebug()<<"printerName is null";
                            return;
                        }
                        qDebug()<<printer.printerName();
                        int ret = 0;
                        ret = (int)ShellExecuteW(NULL,
                                                 QString("print").toStdWString().c_str(),
                                                 filename.toStdWString().c_str(),
                                                 NULL,
                                                 NULL,
                                                 SW_SHOWNORMAL);
                        // if return number bigger than 31 indicate succ
                        if (ret > SE_ERR_NOASSOC)
                            return;
                         qDebug()<<"print file failed!";
                    }
                }
            }
            else{
                msgBox.setText("人员日志表EXCEL生成失败！");
                msgBox.exec();
            }
        }
    }
}

void tabstafflogwindow::on_tabstalog_lastbutton_clicked()
{
    if(currentpage <= totalpage && currentpage > 1){
        ui->tabstalog_currenttext->setText(QString::number(--currentpage));
        //        int currentvalue = ui->tabper_stafftable->verticalScrollBar()->value();
        ui->tabstalog_table->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
    }
}

void tabstafflogwindow::on_tabstalog_currenttext_returnPressed()
{
    if(ui->tabstalog_currenttext->text().toInt() > totalpage){
        ui->tabstalog_currenttext->setText(QString(totalpage));
        currentpage = totalpage;
    }
    if(ui->tabstalog_currenttext->text().toInt() < 1){
        ui->tabstalog_currenttext->setText("1");
        currentpage = 1;
    }
    currentpage = ui->tabstalog_currenttext->text().toInt();
    ui->tabstalog_table->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
}

void tabstafflogwindow::on_tabstalog_nextbutton_clicked()
{
    if(currentpage < totalpage && currentpage >= 1){
        ui->tabstalog_currenttext->setText(QString::number(++currentpage));
        ui->tabstalog_table->verticalScrollBar()->setSliderPosition((currentpage-1)*16);
    }
}

//bool tabstafflogwindow::printFile(QString filename)
//{
//    // create a printer
//    QPrinter printer;
//    //QString printerName = printer.printerName();
//    // no default printer or no file return false
//    //if( printerName.size() == 0 || filename.size() == 0)
//    //    return false;
//    //QFileInfo fi(filename);
//    //if(!fi.exists())
//    //    return false;
//    int ret = 0;
//    ret = (int)ShellExecuteW(NULL,
//                             QString("print").toStdWString().c_str(),
//                             filename.toStdWString().c_str(),
//                             NULL,
//                             NULL,
//                             SW_HIDE);
//    // if return number bigger than 31 indicate succ
//    if (ret > SE_ERR_NOASSOC)
//        return true;
//    return false;
//}
