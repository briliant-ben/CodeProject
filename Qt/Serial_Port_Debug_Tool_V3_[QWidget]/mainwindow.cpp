#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialcom.h"
#include "seriallog.h"
#include "serialconsole.h"
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new SerialCom),
    m_seriallog(new SerialLog),
    m_console(new SerialConsole)
{
    // ui
    ui->setupUi(this);
    m_console->setReadOnly(true);
    ui->layoutConsole->addWidget(m_console);

    // serial cfg and info
    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(resetSerialCfgUi()));
    ui->cBoxSerialPort->insertItems(0, m_serial->getPortNames());
    ui->textBrowSerialInfo->setText(m_serial->getPortInfo(ui->cBoxSerialPort->currentText()));
    connect(ui->cBoxSerialPort, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSerialInfo(int)));

    // serial communication
    connect(ui->btnCom, SIGNAL(clicked()), this, SLOT(opencloseSerialPort()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(sendSerialMsg()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->lineEdit, SLOT(clear()));
    connect(m_serial, SIGNAL(serialReadData(const QString&)), m_console, SLOT(putData(const QString&)));
    connect(m_console, SIGNAL(getData(const QString&)), m_serial, SLOT(incomingWriteData(const QString&)));

    // serial status
    connect(m_serial, SIGNAL(serialstatus(const QString&)), ui->statusBar, SLOT(showMessage(const QString &)));

    // serial log file cfg & control
    ui->lEditPrefix->setEnabled(false);
    ui->btnLogRecord->setEnabled(false);
    ui->lEditLocation->setText(m_seriallog->getDefaultLogPath());
    connect(ui->btnLocation, SIGNAL(clicked()), this, SLOT(setlocation()));
    connect(ui->btnLogRecord, SIGNAL(clicked()), this, SLOT(serialLogRecord()));

    // auxiliary funtion

    // temp
    ui->cBoxFormat->setEnabled(false);
    ui->btnPackage->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete m_serial;
    delete m_seriallog;
    delete m_console;
    delete ui;
}

// serial cfg and info
void MainWindow::setSerialCfgUi(bool en)
{
    ui->cBoxSerialPort->setEnabled(en);
    ui->cBoxSpeed->setEnabled(en);
    ui->cBoxDataBits->setEnabled(en);
    ui->cBoxStopBits->setEnabled(en);
    ui->cBoxParity->setEnabled(en);
    ui->cBoxFlowControl->setEnabled(en);
    ui->btnReset->setEnabled(en);
    ui->btnCom->setEnabled(en);
    ui->lEditPrefix->setEnabled(!en);
    ui->btnLogRecord->setEnabled(!en);
}

void MainWindow::resetSerialCfgUi()
{
    ui->cBoxSerialPort->setCurrentIndex(0);
    ui->cBoxSpeed->setCurrentIndex(7);
    ui->cBoxDataBits->setCurrentIndex(3);
    ui->cBoxStopBits->setCurrentIndex(0);
    ui->cBoxParity->setCurrentIndex(0);
    ui->cBoxFlowControl->setCurrentIndex(0);
}

void MainWindow::updateSerialInfo(int)
{
    ui->textBrowSerialInfo->setText(m_serial->getPortInfo(ui->cBoxSerialPort->currentText()));
}

// serial communication
void MainWindow::opencloseSerialPort()
{
    if(0 == QString::compare("Connect", ui->btnCom->text(), Qt::CaseSensitive)){
        setSerialCfgUi(false);

        SerialConfig config;
        config.portname = ui->cBoxSerialPort->currentText();
        config.speed = ui->cBoxSpeed->currentText().toInt();
        config.databits = ui->cBoxDataBits->currentText().toInt();
        config.stopbits = ui->cBoxStopBits->currentText().toInt();
        config.parity = ui->cBoxParity->currentIndex();
        config.flowcontrol = ui->cBoxFlowControl->currentIndex();

        if(true == m_serial->connect(config)){
            m_console->setReadOnly(false);
            ui->btnCom->setText("Disconnect");
            ui->btnCom->setEnabled(true);
        }else{
            setSerialCfgUi(true);
        }
    }else{ // "Disconenct"
        if (m_serial->connectStatus())
            m_serial->disconnect();

        setSerialCfgUi(true);
        ui->btnCom->setText("Connect");
        m_console->setReadOnly(true);
        m_console->appendPlainText(
                    QString("\n Connection Closed. \n At time: ")
                    .append(QDateTime::currentDateTime().toString("hh:mm:ss")).append("\n"));
    }
}

void MainWindow::sendSerialMsg()
{
    if(true == m_serial->connectStatus()){
        QString cmd = ui->lineEdit->text() + "\r";
        m_serial->incomingWriteData(cmd); // m_console->putData(cmd);
    }else{
        ui->statusBar->showMessage("No Serial Port is Open!");
    }
}

// serial log cfg
void MainWindow::setlocation()
{
    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Select Directory"), ".",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lEditLocation->setText(dir);
}

void MainWindow::cBoxFormatToggle(bool en)
{
    ui->cBoxFormat->setEnabled(en);
}

void MainWindow::serialLogRecord()
{
    if(0 == QString::compare("Record", ui->btnLogRecord->text(), Qt::CaseSensitive)){
        if(true == m_seriallog->startRecord(ui->lEditLocation->text() , ui->lEditPrefix->text().isNull()? "Prefix" : ui->lEditPrefix->text())){
            QObject::connect(m_serial, SIGNAL(serialReadData(const QString&)), m_seriallog, SLOT(recordingLog(const QString&)));
            ui->btnLogRecord->setText("Stop");
        }else{
            ui->statusBar->showMessage("Start Recording Log Failed!");
        }
    }else{ // "Stop"
        QObject::disconnect(m_serial, SIGNAL(serialReadData(const QString&)), m_seriallog, SLOT(recordingLog(const QString&)));
        m_seriallog->stopRecord();
        ui->btnLogRecord->setText("Record");
    }
}

// auxiliary
void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(
                this,
                "About RealTek WLAN Debug Tool",
                "<center><font><b><h3>RealTek WLAN Debug Tool V1.0</h3></b>" \
                "Development IDE: Qt5.12.3" \
                "<br/>Built On: Febrnary 29 2020 14:35" \
                "<br/>Author: benling_xu@realsil.com.cn" \
                "<br/>Copyright@RealTek 1987-2020 All rights reserved" \
                "<br/>The program is provided AS IS with NO WARRANTY OF ANY KIND," \
                "<br/>INCLUDING THE WARRANTY OF DESIGN,MERCHANTABILITY AND " \
                "<br/>FITNESS FOR A PARTICULAR PURPOSE. </font></center>");
}
