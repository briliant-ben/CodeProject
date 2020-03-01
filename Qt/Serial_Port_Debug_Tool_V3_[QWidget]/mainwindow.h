#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class SerialCom;
class SerialLog;
class SerialConsole;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void cBoxFormatToggle(bool);
    void serialLogRecord();

    // auxiliary
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();

private:
    void setSerialCfgUi(bool);
    Ui::MainWindow      *ui  = nullptr;
    SerialCom      *m_serial = nullptr;
    SerialLog   *m_seriallog = nullptr;
    SerialConsole *m_console = nullptr;
};

#endif // MAINWINDOW_H
