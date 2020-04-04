#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class PackageDialog;
class SerialCom;
class SerialLog;
class SerialConsole;
class ScriptWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void inline controlCmdSend(bool);

signals:

private slots:
    // serial cfg and info
    void resetSerialCfgUi();
    void updateSerialInfo(int);

    // serial communication
    void opencloseSerialPort();
    void sendSerialMsg();

    // serial log cfg & control
    void setlocation();
    void serialLogRecord();
    void on_rBtnNeedPackage_toggled(bool checked);
    void on_btnPackage_clicked();

    // auxiliary
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionConnect_triggered();
    void on_actionClear_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_btnClear_clicked();
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnPrefix_clicked();
    void setPrefix();
    void on_btnScript_clicked();

    // usage tab page
    void on_btnBasicAdd_clicked();
    void on_btnBasicSend_clicked();
    void on_btnDynamicAdd_clicked();
    void on_btnDynamicSend_clicked();
    void on_btnCmdReset_clicked();
    void on_btnCmdSend_clicked();
    void sendCmdbyLine();

private:
    void setSerialCfgUi(bool);
    bool prefixflag          = false;
    bool needpackage         = false;
    Ui::MainWindow      *ui  = nullptr;
    SerialCom      *m_serial = nullptr;
    SerialLog   *m_seriallog = nullptr;
    SerialConsole *m_console = nullptr;
    PackageDialog   *pdialog = nullptr;
    QTimer            *timer = nullptr;
    ScriptWorker   *m_script = nullptr;
};

#endif // MAINWINDOW_H
