#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTextBlock>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialcom.h"
#include "seriallog.h"
#include "serialconsole.h"
#include "packagedialog.h"
#include "scriptworker.h"
//#include <QDebug>

static bool sendcmdbylineflag = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new SerialCom),
    m_seriallog(new SerialLog),
    m_console(new SerialConsole(this)),
    pdialog(new PackageDialog(this)),
    m_script(new ScriptWorker(this))
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
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(setPrefix()));
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
    //ui->btnPackage->setEnabled(false);

    // auxiliary funtion
    connect(m_script, SIGNAL(error(const QString&)), ui->statusBar, SLOT(showMessage(const QString&)));
    connect(m_script, SIGNAL(sendcmd(const QString&)), m_serial, SLOT(incomingWriteData(const QString&)));

    // usage tab page
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendCmdbyLine()));
}

MainWindow::~MainWindow()
{
    delete m_serial;
    delete m_seriallog;
    delete m_console;
    delete pdialog;
    delete m_script;
    delete ui;
}

/* #################### serial cfg and info #################### */
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
    ui->actionConnect->setEnabled(en);
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

/* #################### serial communication #################### */
void MainWindow::opencloseSerialPort()
{
    if(0 == QString::compare("Connect", ui->btnCom->text(), Qt::CaseSensitive)){
        setSerialCfgUi(false);
        QTextCursor cursor = m_console->textCursor();
        cursor.movePosition(QTextCursor::End);
        m_console->setTextCursor(cursor);

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
            ui->actionConnect->setText("Disconnect");
            ui->btnCom->setEnabled(true);
            ui->actionConnect->setEnabled(true);
        }else{
            setSerialCfgUi(true);
        }
    }else{ // "Disconenct"
        if (m_serial->connectStatus())
            m_serial->disconnect();

        setSerialCfgUi(true);
        ui->btnCom->setText("Connect");
        ui->actionConnect->setText("Connect");
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

/* #################### serial log cfg #################### */
void MainWindow::setlocation()
{
    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Select Directory"), ".",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lEditLocation->setText(dir);
}

void MainWindow::serialLogRecord()
{
    if(0 == QString::compare("Record", ui->btnLogRecord->text(), Qt::CaseSensitive)){
        ui->rBtnNeedPackage->setEnabled(false);
        ui->btnPackage->setEnabled(false);
        //ui->lEditPrefix->text().isNull()? "Prefix" : ui->lEditPrefix->text()
        if(true == m_seriallog->startRecord(ui->lEditLocation->text() , ui->lEditPrefix->text(), needpackage)){
            QObject::connect(m_serial, SIGNAL(serialReadData(const QString&)), m_seriallog, SLOT(recordingLog(const QString&)));
            ui->btnLogRecord->setText("Stop");
        }else{
            ui->statusBar->showMessage("Start Recording Log Failed!");
        }
    }else{ // "Stop"
        QObject::disconnect(m_serial, SIGNAL(serialReadData(const QString&)), m_seriallog, SLOT(recordingLog(const QString&)));
        m_seriallog->stopRecord();
        ui->btnLogRecord->setText("Record");
        ui->rBtnNeedPackage->setEnabled(true);
        ui->btnPackage->setEnabled(true);
    }
}

void MainWindow::on_rBtnNeedPackage_toggled(bool checked)
{
    needpackage = checked;
}

void MainWindow::on_btnPackage_clicked()
{
    if(ui->rBtnNeedPackage->isChecked())
        pdialog->setpackOption(true);
    else
        pdialog->setpackOption(false);

    pdialog->show();
}

/* #################### auxiliary #################### */
void MainWindow::on_actionConnect_triggered()
{
    this->opencloseSerialPort();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionClear_triggered()
{
    m_console->clear();
}

void MainWindow::on_actionZoomIn_triggered()
{
    m_console->zoomIn();
}

void MainWindow::on_actionZoomOut_triggered()
{
    m_console->zoomOut();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(
                this,
                "About Serial Debug Tool",
                "Nothing");
}

void MainWindow::on_btnClear_clicked()
{
    m_console->clear();
}

void MainWindow::on_btnZoomIn_clicked()
{
    m_console->zoomIn();
}

void MainWindow::on_btnZoomOut_clicked()
{
    m_console->zoomOut();
}

void MainWindow::on_btnPrefix_clicked()
{
    if(prefixflag){
        prefixflag = false;
        ui->btnPrefix->setText("Prefix ON");
    }else{
        prefixflag = true;
        ui->btnPrefix->setText("Prefix OFF");
        if(ui->lineEdit->text().size() == 0)
            ui->lineEdit->setText("iwpriv dbg ");
    }
}

void MainWindow::setPrefix()
{
    ui->lineEdit->clear();
    if(prefixflag)
        ui->lineEdit->setText("iwpriv dbg ");
}

void MainWindow::on_btnScript_clicked()
{
    if(sendcmdbylineflag)
        return;

    m_script->start();

    QString packfiles = QFileDialog::getOpenFileName(
                this,
                "Select script files to execute",
                QDir::currentPath(),
                "Text files (*.txt);;All files (*)");

    m_script->transaction(packfiles, m_serial);
}

/* #################### usage tab page #################### */
void MainWindow::on_btnBasicAdd_clicked()
{
    ui->pTextEditCmdList->appendPlainText(ui->cBoxTimeBasic->currentText() + "#"
                                          + "iwpriv dbg " + ui->cBoxModule->currentText());
}

void MainWindow::on_btnBasicSend_clicked()
{
    if(true == m_serial->connectStatus()){
        QString cmd = "iwpriv dbg " + ui->cBoxModule->currentText() + "\r";
        m_serial->incomingWriteData(cmd);
    }else{
        ui->statusBar->showMessage("No Serial Port is Open!");
    }
}

void MainWindow::on_btnDynamicAdd_clicked()
{
    ui->pTextEditCmdList->appendPlainText(ui->cBoxTimeDynamic->currentText() + "#"
                                          + "iwpriv dbg " + ui->cBoxComp->currentText() + " " + ui->cBoxLevel->currentText());
}

void MainWindow::on_btnDynamicSend_clicked()
{
    if(true == m_serial->connectStatus()){
        QString cmd = "iwpriv dbg " + ui->cBoxComp->currentText() + " " + ui->cBoxLevel->currentText() + "\r";
        m_serial->incomingWriteData(cmd);
    }else{
        ui->statusBar->showMessage("No Serial Port is Open!");
    }
}

void MainWindow::on_btnCmdReset_clicked()
{
    ui->pTextEditCmdList->clear();
}

void inline MainWindow::controlCmdSend(bool en){
    ui->btnCmdSend->setEnabled(en);
    ui->pTextEditCmdList->setEnabled(en);
    ui->btnCmdReset->setEnabled(en);
    ui->btnBasicAdd->setEnabled(en);
    ui->btnDynamicAdd->setEnabled(en);

    if(true == en)
        timer->stop();
}

void MainWindow::on_btnCmdSend_clicked()
{
    if(false == m_serial->connectStatus()){
        ui->statusBar->showMessage("No Serial Port is Open!");
        return;
    }

    if(m_script->isRunning()){
        ui->statusBar->showMessage("Script is Running!");
        return;
    }

    //qDebug() << ui->pTextEditCmdList->document()->lineCount();
    if(ui->pTextEditCmdList->document()->findBlockByLineNumber(0).text().isEmpty()){
        ui->statusBar->showMessage("No Command in the List Here!");
        return;
    }
    controlCmdSend(false);
    timer->start(50);
}

void MainWindow::sendCmdbyLine()
{
    sendcmdbylineflag = true;

    if(false == m_serial->connectStatus()){
        ui->statusBar->showMessage("No Serial Port is Open!");
        controlCmdSend(true);
        return;
    }

    int sec = 0;
    static int count = 0;
    QTextDocument *td = ui->pTextEditCmdList->document();
    QString cmd = td->findBlockByLineNumber(count).text();


    if(!cmd.contains('#')){
        ui->statusBar->showMessage("Command Format Wrong! Correct it!");
        controlCmdSend(true);
        return;
    }

    sec = cmd.section('#', 0, 0).toInt();
    if(sec < 0 || sec > 60){
        ui->statusBar->showMessage("The Time in Command Format is Wrong! Correct it!");
        controlCmdSend(true);
        return;
    }

    m_serial->incomingWriteData(cmd.section('#', 1, 1) + "\r");

    if(++count >= td->lineCount()){
        sendcmdbylineflag = false;
        count = 0;
        controlCmdSend(true);
        return;
    }

    timer->start(sec*1000);
}
