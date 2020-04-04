#include <QDir>
#include <QFileDialog>
#include "packagedialog.h"
#include "ui_packagedialog.h"
#include "seriallog.h"
#include "JlCompress.h"
//#include <QDebug>

PackageDialog::PackageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageDialog)
{
    this->setModal(true);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    ui->setupUi(this);

    this->setWindowTitle("Package Serial Log Files");
}

PackageDialog::~PackageDialog()
{
    delete ui;
}

void PackageDialog::setpackOption(bool isdefault)
{
    if(isdefault){
        ui->rBtnDefault->setChecked(true);
        ui->gBoxCusOption->setEnabled(false);
    }else{
        ui->rBtnCustomize->setChecked(true);
        ui->gBoxCusOption->setEnabled(true);
    }
}

void PackageDialog::on_rBtnDefault_clicked()
{
    ui->gBoxCusOption->setEnabled(false);
    ui->labelInfo->clear();
}

void PackageDialog::on_rBtnCustomize_clicked()
{
    ui->gBoxCusOption->setEnabled(true);
    ui->labelInfo->clear();
}

void PackageDialog::on_btnSelect_clicked()
{
    ui->labelInfo->clear();
    packfiles = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            QDir::currentPath(),
                            "Text files (*.txt);;All files (*)");
    QString temp;
    for (int i = 0; i < packfiles.size(); ++i){
        //qDebug() << packfiles.at(i).toLocal8Bit().constData() << endl;
        temp.append(packfiles.at(i));
    }
    ui->lEditSelect->setText(temp);
}

void PackageDialog::on_btnTargetPath_clicked()
{
    ui->labelInfo->clear();
    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Select Directory"), ".",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lEditTargetPath->setText(dir);
}

void PackageDialog::on_btnReset_clicked()
{
    ui->lEditSelect->clear();
    ui->lEditTargetPath->clear();
    ui->lEditCompressName->clear();
    ui->labelInfo->clear();
}

void PackageDialog::on_btnOK_clicked()
{
    if(ui->rBtnDefault->isChecked()){
        QDir packpath = QDir(SerialLog::preLogPath);
        if(!packpath.exists()){
            ui->labelInfo->setText("Default Package Path is Gone!");
            return;
        }
        if(QFile(SerialLog::preLogPath + ".zip").exists()){
            ui->labelInfo->setText("Package Exist Already!");
            return;
        }
        if(!JlCompress::compressDir(SerialLog::preLogPath + ".zip", SerialLog::preLogPath)){
            ui->labelInfo->setText("Package Directory Failed!");
            return;
        }
    }else{
        if(ui->lEditSelect->text().isEmpty() || ui->lEditTargetPath->text().isEmpty() || ui->lEditCompressName->text().isEmpty()){
            ui->labelInfo->setText("Please Fullfill Your Options!");
            return;
        }
        QString abspathfile = ui->lEditTargetPath->text() + "\\" + ui->lEditCompressName->text() + ".zip";
        if(QFile(abspathfile).exists()){
            ui->labelInfo->setText("Package Exist Already!");
            return;
        }
        if(!JlCompress::compressFiles(abspathfile, packfiles)){
            ui->labelInfo->setText("Package Log Files Failed!");
            return;
        }
    }
    ui->labelInfo->setText("Package Directory OK!");
}

void PackageDialog::on_btnCancel_clicked()
{
    this->close();
}


void PackageDialog::on_PackageDialog_finished(int)
{
    ui->lEditSelect->clear();
    ui->lEditTargetPath->clear();
    ui->lEditCompressName->clear();
}
