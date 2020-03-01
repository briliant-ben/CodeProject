#pragma execution_character_set("utf-8")
#include "streamrecordwindow.h"
#include "ui_streamrecordwindow.h"
#include <QMessageBox>

streamrecordwindow::streamrecordwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::streamrecordwindow),
    newstreamdao(new storagestreamdao)
{
    ui->setupUi(this);

    QRegExp regExp1("^[0-9]*$");
    ui->stream_quantitytext->setValidator(new QRegExpValidator(regExp1,this));
}

streamrecordwindow::~streamrecordwindow()
{
    delete ui;
}

void streamrecordwindow::judgement(int which)
{
    switch (which) {
    case 0:
        ui->stream_kindcombox->setCurrentIndex(0);
        ui->stream_modeltext->setEnabled(true);
        ui->stream_statetext->setEnabled(true);
        break;
    case 1:
        ui->stream_kindcombox->setCurrentIndex(1);
        ui->stream_modeltext->setEnabled(false);
        ui->stream_statetext->setEnabled(false);
        break;
    case 2:
        ui->stream_kindcombox->setCurrentIndex(2);
        ui->stream_modeltext->setEnabled(true);
        ui->stream_statetext->setEnabled(true);
        break;
    default:
        break;
    }
    QStringList texts;
    ui->stream_locationcombox->clear();
    ui->stream_locationcombox->addItems(newstreamdao->streamlocation(texts));

    texts.clear();
    ui->stream_modelcombox->clear();
    ui->stream_modelcombox->addItems(newstreamdao->streammodel(texts));

    texts.clear();
    ui->stream_chargemancombox->clear();
    ui->stream_chargemancombox->addItems(newstreamdao->streamchargeman(texts));

    ui->stream_locationtext->setText("");
    ui->stream_modeltext->setText("");
    ui->stream_quantitytext->setText("");
    ui->stream_statetext->setText("");
    ui->stream_chargemantext->setText("");
}

void streamrecordwindow::on_stream_locationcombox_activated(int)
{
    ui->stream_locationtext->setText(ui->stream_locationcombox->currentText());
}

void streamrecordwindow::on_stream_modelcombox_activated(int)
{
    ui->stream_modeltext->setText(ui->stream_modelcombox->currentText());
}

void streamrecordwindow::on_stream_quantitycombox_activated(int)
{
    ui->stream_quantitytext->setText(ui->stream_quantitycombox->currentText());
}

void streamrecordwindow::on_stream_statecombox_activated(int)
{
    ui->stream_statetext->setText(ui->stream_statecombox->currentText());
}

void streamrecordwindow::on_stream_chargemancombox_activated(int)
{
    ui->stream_chargemantext->setText(ui->stream_chargemancombox->currentText());
}

/*
 *error number:
 * 0   ---success!
 * 1   ---coupling not same
 * 2   ---
 * 3   ---
 * 100+---databse error
*/
void streamrecordwindow::on_stream_confirmbutton_clicked()
{
    int result;
    if((ui->stream_locationtext->text() != "")
            &&(ui->stream_modeltext->text() != "")
            &&(ui->stream_quantitytext->text() != "")
            &&(ui->stream_statetext->text() != "")
            &&(ui->stream_chargemantext->text() != "")){
        ui->stream_timelabel2->setText(QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate));

        switch (ui->stream_kindcombox->currentIndex()) {
        case 0://storagein
            result = newstreamdao->storageinrecord(ui->stream_locationtext->text(),
                                                   ui->stream_modeltext->text(),
                                                   ui->stream_quantitytext->text().toInt(),
                                                   ui->stream_statetext->text(),
                                                   ui->stream_chargemantext->text());
            qDebug()<<result;
            switch (result) {
            case 0:
                QMessageBox::information(this, "Information!",QString("入库录入成功！"), QMessageBox::Ok);
                clearcontent();
                break;
            case 1:
                QMessageBox::warning(this, "Warning!",QString("<font>向同一位置入库不同管料！<br/>请确认！</font>"), QMessageBox::Ok);
                break;
            default:
                QMessageBox::warning(this, "Warning!",QString("数据库错误！"), QMessageBox::Ok);
                break;
            }
            break;
        case 1://storageout
            result = newstreamdao->storageoutrecord(ui->stream_locationtext->text(),
                                                    ui->stream_quantitytext->text().toInt(),
                                                    ui->stream_chargemantext->text());
            qDebug()<<result;
            switch (result) {
            case 0:
                QMessageBox::information(this, "Information!",QString("出库录入成功！"), QMessageBox::Ok);
                clearcontent();
                break;
            case 1:
                QMessageBox::warning(this, "Warning!",QString("<font>此位置上没有管料不足！<br/>请确认！</font>"), QMessageBox::Ok);
                break;
            default:
                QMessageBox::warning(this, "Warning!",QString("数据库错误！"), QMessageBox::Ok);
                break;
            }
            break;
        case 2://stocktake
            result = newstreamdao->stocktakerecord(ui->stream_locationtext->text(),
                                                   ui->stream_modeltext->text(),
                                                   ui->stream_quantitytext->text().toInt(),
                                                   ui->stream_statetext->text(),
                                                   ui->stream_chargemantext->text());
            qDebug()<<result;
            switch (result) {
            case 0:
                QMessageBox::information(this, "Information!",QString("盘点录入成功！"), QMessageBox::Ok);
                clearcontent();
                break;
            default:
                QMessageBox::warning(this, "Warning!",QString("数据库错误！"), QMessageBox::Ok);
                break;
            }
            break;
        default:
            break;
        }
    }
    else{
        QMessageBox::warning(this, "Warning!",QString("<font>输入信息不完全！<br/>请确认！</font>"), QMessageBox::Ok);
        ui->stream_locationtext->setFocus();
    }
}

void streamrecordwindow::on_stream_cancelbuttom_clicked()
{
    clearcontent();
}

void streamrecordwindow::clearcontent()
{
    ui->stream_locationtext->setText("");
    ui->stream_modeltext->setText("");
    ui->stream_quantitytext->setText("");
    ui->stream_unitbutton1->setFocus();
    ui->stream_statetext->setText("");
    ui->stream_chargemantext->setText("");

    ui->stream_locationtext->setFocus();
}

void streamrecordwindow::on_stream_kindcombox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->stream_modeltext->setEnabled(true);
        ui->stream_statetext->setEnabled(true);
        break;
    case 1:
        ui->stream_modeltext->setEnabled(false);
        ui->stream_statetext->setEnabled(false);
        break;
    case 2:
        ui->stream_modeltext->setEnabled(true);
        ui->stream_statetext->setEnabled(true);
        break;
    default:
        break;
    }
}
